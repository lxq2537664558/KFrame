﻿#include "KFBusConfig.h"

namespace KFrame
{

    bool KFBusConfig::IsValidConnection( const std::string& appname, const std::string& apptype, uint32 appid,
                                         const std::string& connectname, const std::string& connecttype, uint32 connectid )
    {
        for ( auto& kfconnection : _bus_connection )
        {
            if ( kfconnection._app_name != _globbing_str && kfconnection._app_name != appname )
            {
                continue;
            }

            if ( kfconnection._app_type != _globbing_str && kfconnection._app_type != apptype )
            {
                continue;
            }

            if ( kfconnection._app_id != _invalid_int && kfconnection._app_id != appid )
            {
                continue;
            }

            // 判断连接目标信息
            if ( kfconnection._connect_name != _globbing_str && kfconnection._connect_name != connectname )
            {
                continue;
            }

            if ( kfconnection._connect_type != _globbing_str && kfconnection._connect_type != connecttype )
            {
                continue;
            }

            if ( kfconnection._connect_id != _invalid_int && kfconnection._connect_id != connectid )
            {
                continue;
            }

            return true;
        }

        return false;
    }

    void KFBusConfig::FindConnection( const std::string& appname, const std::string& apptype, uint32 appid, std::set<KFConnection*>& outlist )
    {
        outlist.clear();

        for ( auto& kfconnection : _bus_connection )
        {
            if ( kfconnection._app_name != _globbing_str && kfconnection._app_name != appname )
            {
                continue;
            }

            if ( kfconnection._app_type != _globbing_str && kfconnection._app_type != apptype )
            {
                continue;
            }

            if ( kfconnection._app_id != _invalid_int && kfconnection._app_id != appid )
            {
                continue;
            }


            outlist.insert( &kfconnection );
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFBusConfig::LoadConfig( const char* file )
    {
        _bus_connection.clear();
        try
        {
            KFXml kfxml( file );
            auto config = kfxml.RootNode();
            //////////////////////////////////////////////////////////////////
            //////////////////////////////////////////////////////////////////
            auto busnode = config.FindNode( "Bus" );
            if ( busnode.IsValid() )
            {
                auto connectionnode = busnode.FindNode( "Connection" );
                while ( connectionnode.IsValid() )
                {
                    KFConnection kfconnection;

                    kfconnection._app_name = connectionnode.GetString( "AppName" );
                    kfconnection._app_type = connectionnode.GetString( "AppType" );
                    kfconnection._app_id = connectionnode.GetUInt32( "AppId" );


                    kfconnection._connect_name = connectionnode.GetString( "ConnectName" );
                    kfconnection._connect_type = connectionnode.GetString( "ConnectType" );
                    kfconnection._connect_id = connectionnode.GetUInt32( "ConnectId" );
                    _bus_connection.push_back( kfconnection );

                    connectionnode.NextNode();
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