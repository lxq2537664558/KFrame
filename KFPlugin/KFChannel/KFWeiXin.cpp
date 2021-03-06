﻿#include "KFWeiXin.hpp"
#include "KFProtocol/KFProtocol.h"
#include "KFRedis/KFRedisInterface.h"
#include "KFHttpClient/KFHttpClientInterface.h"
#include "KFHttpServer/KFHttpServerInterface.h"

namespace KFrame
{
#define __AUTH_REDIS_DRIVER__ _kf_redis->Create( __STRING__( auth ) )

    std::string KFWeiXin::RequestLogin( KFJson& json, const KFChannelSetting* kfsetting )
    {
        auto machinecode = __JSON_GET_STRING__( json, __STRING__( machine ) );
        auto weixincode = __JSON_GET_STRING__( json, __STRING__( code ) );

        std::string openid = "";
        std::string accesstoken = "";

        if ( !weixincode.empty() )
        {
            // 去请求access_token
            auto urldata = __FORMAT__( "{}/sns/oauth2/access_token?appid={}&secret={}&code={}&grant_type=authorization_code",
                                       kfsetting->_login_url, kfsetting->_app_id, kfsetting->_app_key, weixincode );

            auto accessdata = _kf_http_client->STGet( urldata, _invalid_string );
            if ( accessdata.empty() )
            {
                return _kf_http_server->SendCode( KFMsg::WeiXinError );
            }

            __JSON_PARSE_STRING__( accessjson, accessdata );

            // 如果出错, 返回错误码
            if ( __JSON_HAS_MEMBER__( accessjson, __STRING__( errcode ) ) )
            {
                return _kf_http_server->SendResponse( accessjson, KFMsg::WeiXinCodeError );
            }

            accesstoken = __JSON_GET_STRING__( accessjson, __STRING__( access_token ) );
            openid = __JSON_GET_STRING__( accessjson, __STRING__( openid ) );
            auto refreshtoken = __JSON_GET_STRING__( accessjson, __STRING__( refresh_token ) );
            auto expirestime = __JSON_GET_UINT32__( accessjson, __STRING__( expires_in ) );
            auto scope = __JSON_GET_STRING__( accessjson, __STRING__( scope ) );

            // 保存access_token
            auto redisdriver = __AUTH_REDIS_DRIVER__;
            redisdriver->Append( "hmset {}:{} {} {} {} {} {} {}",
                                 __STRING__( access_token ), machinecode, __STRING__( access_token ), accesstoken,
                                 __STRING__( openid ), openid, __STRING__( scope ), scope );
            redisdriver->Append( "expire {}:{} {}", __STRING__( access_token ), machinecode, expirestime - 200 );
            redisdriver->Append( "hset {}:{} {} {}", __STRING__( refresh_token ), machinecode, __STRING__( refresh_token ), accesstoken );
            redisdriver->Append( "expire {}:{} {}", __STRING__( refresh_token ), machinecode, 2590000 );
            redisdriver->Pipeline();
        }
        else
        {
            // 机器码获得账号的access_token
            auto redisdriver = __AUTH_REDIS_DRIVER__;
            auto weixindata = redisdriver->QueryMap( "hgetall {}:{}", __STRING__( access_token ), machinecode );
            if ( !weixindata->IsOk() )
            {
                return _kf_http_server->SendCode( KFMsg::AuthDatabaseBusy );
            }

            if ( !weixindata->_value.empty() )
            {
                openid = weixindata->_value[ __STRING__( openid ) ];
                accesstoken = weixindata->_value[ __STRING__( access_token ) ];
            }
            else
            {
                // 获得refresh_token
                auto refreshtoken = redisdriver->QueryString( "hget {}:{} {}", __STRING__( refresh_token ), machinecode, __STRING__( refresh_token ) );
                if ( !refreshtoken->IsOk() )
                {
                    return _kf_http_server->SendCode( KFMsg::AuthDatabaseBusy );
                }

                if ( refreshtoken->_value.empty() )
                {
                    return _kf_http_server->SendCode( KFMsg::WeiXinTokenTimeout );
                }

                // 刷新access_token
                auto urldata = __FORMAT__( "{}/sns/oauth2/refresh_token?grant_type=refresh_token&appid={}&refresh_token={}",
                                           kfsetting->_login_url, kfsetting->_app_id, refreshtoken->_value );

                auto accessdata = _kf_http_client->STGet( urldata, _invalid_string );
                if ( accessdata.empty() )
                {
                    return _kf_http_server->SendCode( KFMsg::WeiXinError );
                }

                __JSON_PARSE_STRING__( accessjson, accessdata );
                if ( __JSON_HAS_MEMBER__( accessjson, __STRING__( errcode ) ) )
                {
                    return _kf_http_server->SendResponse( accessjson, KFMsg::WeiXinTokenError );
                }

                accesstoken = __JSON_GET_STRING__( accessjson, __STRING__( access_token ) );
                openid = __JSON_GET_STRING__( accessjson, __STRING__( openid ) );
                auto expirestime = __JSON_GET_UINT32__( accessjson, __STRING__( expires_in ) );
                auto scope = __JSON_GET_STRING__( accessjson, __STRING__( scope ) );

                // 保存access_token
                redisdriver->Append( "hmset {}:{} {} {}", __STRING__( access_token ), machinecode, __STRING__( access_token ), accesstoken );
                redisdriver->Append( "expire {}:{} {}", __STRING__( access_token ), machinecode, expirestime - 200 );
                redisdriver->Pipeline();
            }
        }

        // 获取用户资料
        auto urldata = __FORMAT__( "{}/sns/userinfo?access_token={}&openid={}", kfsetting->_login_url, accesstoken, openid );
        auto userdata = _kf_http_client->STGet( urldata, _invalid_string );
        if ( userdata.empty() )
        {
            return _kf_http_server->SendCode( KFMsg::WeiXinError );
        }

        __JSON_PARSE_STRING__( userjson, userdata );
        if ( __JSON_HAS_MEMBER__( userjson, __STRING__( errcode ) ) )
        {
            return _kf_http_server->SendResponse( userjson, KFMsg::WeiXinUserError );
        }

        //auto openid = __JSON_GET_STRING__( userjson, __STRING__( openid ) );

        __JSON_OBJECT_DOCUMENT__( response );
        __JSON_SET_VALUE__( response, __STRING__( account ), openid );
        __JSON_SET_VALUE__( response, __STRING__( channel ), kfsetting->_id );

        //KFJson kfextend;
        //kfextend.SetValue( __STRING__( name ), userjson.GetString( __STRING__( nickname ) ) );
        //kfextend.SetValue( __STRING__( sex ), userjson.GetInt32( __STRING__( sex ) ) );
        //kfextend.SetValue( __STRING__( icon ), userjson.GetString( __STRING__( headimgurl ) ) );
        //response.SetValue( __STRING__( extend ), kfextend );

        return _kf_http_server->SendResponse( response );
    }

    std::string KFWeiXin::RequestPay( const std::string& data, const KFChannelSetting* kfsetting )
    {
        return _invalid_string;
    }
}