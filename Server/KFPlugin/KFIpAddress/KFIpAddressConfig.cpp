﻿#include "KFIpAddressConfig.h"

namespace KFrame
{
    ////////////////////////////////////////////////////////////////////////////////////////////////
    KFIpAddressConfig::KFIpAddressConfig()
    {
    }

    KFIpAddressConfig::~KFIpAddressConfig()
    {

    }

    const std::string& KFIpAddressConfig::FindPlatformAddress( uint32 id )
    {
        auto platformid = _platform_hash.FindHashNode( id );
        auto iter = _platform_address.find( platformid );
        if ( iter == _platform_address.end() )
        {
            return _invalid_str;
        }

        return iter->second;
    }

    const KFIpAddress* KFIpAddressConfig::FindIpAddress( const std::string& appname, const std::string& apptype, uint32 appid )
    {
        for ( auto& kfaddress : _ip_address_list )
        {
            if ( kfaddress._app_name == appname &&
                    kfaddress._app_type == apptype &&
                    ( appid == _invalid_int || kfaddress._app_id == appid ) )
            {
                return &kfaddress;
            }
        }

        return nullptr;
    }

    void KFIpAddressConfig::FindIpAddress( const std::string& appname, const std::string& apptype, uint32 appid, IpAddressList& outlist )
    {
        for ( auto& kfaddress : _ip_address_list )
        {
            if ( appname != _globbing_str && appname != kfaddress._app_name  )
            {
                continue;
            }

            if ( apptype != _globbing_str && apptype != kfaddress._app_type )
            {
                continue;
            }

            if ( appid != _invalid_int && appid != kfaddress._app_id )
            {
                continue;
            }

            outlist.insert( &kfaddress );
        }
    }

    void KFIpAddressConfig::SetZoneIpAddress( uint32 zoneid, uint32 appid, const std::string& ip )
    {
        auto kfaddress = FindIpAddress( KFField::_zone, KFField::_master, _invalid_int );
        if ( kfaddress == nullptr )
        {
            return;
        }

        auto* kfzoneaddress = const_cast< KFIpAddress* >( kfaddress );

        kfzoneaddress->_ip = ip;
        kfzoneaddress->_app_id = appid;
    }

    bool KFIpAddressConfig::LoadConfig( const char* file )
    {
        _ip_address_list.clear();
        _platform_address.clear();
        _platform_hash.ClearHashNode();

        try
        {
            KFXml kfxml( file );
            auto config = kfxml.RootNode();
            //////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////
            auto tcpnode = config.FindNode( "TcpServer" );
            if ( tcpnode.IsValid() )
            {
                auto servernode = tcpnode.FindNode( "Server" );
                while ( servernode.IsValid() )
                {
                    KFIpAddress kfaddress;
                    kfaddress._app_name = servernode.GetString( "AppName" );
                    kfaddress._app_type = servernode.GetString( "AppType" );
                    kfaddress._app_id = servernode.GetUInt32( "AppId" );
                    kfaddress._ip = servernode.GetString( "Ip" );
                    kfaddress._port_type = servernode.GetUInt32( "Type" );
                    kfaddress._port = servernode.GetUInt32( "Port" );
                    _ip_address_list.push_back( kfaddress );

                    servernode.NextNode();
                }
            }
            //////////////////////////////////////////////////////////////////
            auto httpnode = config.FindNode( "HttpServer" );
            if ( httpnode.IsValid() )
            {
                uint32 platformid = 0;
                auto platform = httpnode.FindNode( "Platform" );
                while ( platform.IsValid() )
                {
                    auto address = platform.GetString( "Address" );

                    ++platformid;
                    _platform_address[ platformid ] = address;
                    _platform_hash.AddHashNode( "platform", platformid, 100 );

                    platform.NextNode();
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////////////////////////
        }
        catch ( ... )
        {
            return false;
        }

        return true;
    }
}