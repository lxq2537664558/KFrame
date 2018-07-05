﻿#include "KFTcpClientModule.h"
#include "KFProtocol/KFProtocol.h"

namespace KFrame
{
    KFTcpClientModule::KFTcpClientModule()
    {
        _kf_client_engine = nullptr;
        _kf_transmit_function = nullptr;
    }

    KFTcpClientModule::~KFTcpClientModule()
    {
        __KF_DELETE__( _kf_client_engine );
    }

    void KFTcpClientModule::InitModule()
    {
        _kf_client_engine = __KF_NEW__( KFNetClientEngine );
    }

    void KFTcpClientModule::BeforeRun()
    {
        __REGISTER_RUN_FUNCTION__( &KFTcpClientModule::Run );

        _kf_client_engine->InitEngine( 10000 );

        _kf_client_engine->BindNetFunction( this, &KFTcpClientModule::HandleNetMessage );
        _kf_client_engine->BindConnectFunction( this, &KFTcpClientModule::OnClientConnected );
        _kf_client_engine->BindDisconnectFunction( this, &KFTcpClientModule::OnClientDisconnect );

        ///////////////////////////////////////////////////////////////////////////////////////////////////////
        __REGISTER_MESSAGE__( KFMsg::S2S_REGISTER_TO_SERVER_ACK, &KFTcpClientModule::HandleRegisterAck );
    }

    void KFTcpClientModule::ShutDown()
    {
        __UNREGISTER_RUN_FUNCTION__();
        ////////////////////////////////////////////////////////////////////////////
        __UNREGISTER_MESSAGE__( KFMsg::S2S_REGISTER_TO_SERVER_ACK );
        _kf_client_engine->ShutEngine();
    }

    void KFTcpClientModule::Run()
    {
        // 网络事件
        _kf_client_engine->RunEngine( KFGlobal::Instance()->_game_time );
    }
    /////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////
    // 连接成功
    __KF_CLIENT_CONNECT_FUNCTION__( KFTcpClientModule::OnClientConnected )
    {
        // 把自己注册到服务器
        KFMsg::RegisterToServerReq req;
        auto listendata = req.mutable_listen();

        auto kfglobal = KFGlobal::Instance();

        listendata->set_appid( kfglobal->_app_id );
        listendata->set_apptype( kfglobal->_app_type );
        listendata->set_appname( kfglobal->_app_name );
        listendata->set_ip( kfglobal->_interanet_ip );
        listendata->set_port( kfglobal->_listen_port );

        auto strdata = req.SerializeAsString();
        SendNetMessage( serverid, KFMsg::S2S_REGISTER_TO_SERVER_REQ, strdata.data(), strdata.size() );
    }

    // 连接断开
    __KF_CLIENT_LOST_FUNCTION__( KFTcpClientModule::OnClientDisconnect )
    {
        CallClientLostFunction( serverid, servername, servertype );
    }

    void KFTcpClientModule::SendNetMessage( uint32 msgid, google::protobuf::Message* message )
    {
        auto strdata = message->SerializeAsString();
        _kf_client_engine->SendNetMessage( msgid, strdata.data(), strdata.size() );
    }

    bool KFTcpClientModule::SendNetMessage( uint32 serverid, uint32 msgid, google::protobuf::Message* message )
    {
        auto strdata = message->SerializeAsString();
        return _kf_client_engine->SendNetMessage( serverid, msgid, strdata.data(), strdata.size() );
    }

    bool KFTcpClientModule::SendNetMessage( uint32 serverid, uint32 objectid, uint32 msgid, google::protobuf::Message* message )
    {
        auto strdata = message->SerializeAsString();
        return _kf_client_engine->SendNetMessage( serverid, objectid, msgid, strdata.data(), strdata.size() );
    }

    void KFTcpClientModule::SendNetMessage( uint32 msgid, const char* data, uint32 length )
    {
        _kf_client_engine->SendNetMessage( msgid, data, length );
    }

    bool KFTcpClientModule::SendNetMessage( uint32 serverid, uint32 msgid, const char* data, uint32 length )
    {
        return _kf_client_engine->SendNetMessage( serverid, msgid, data, length );
    }

    bool KFTcpClientModule::SendNetMessage( uint32 serverid, uint32 objectid, uint32 msgid, const char* data, uint32 length )
    {
        return _kf_client_engine->SendNetMessage( serverid, objectid, msgid, data, length );
    }

    // 给某一类型服务器发送消息
    void KFTcpClientModule::SendMessageToType( const std::string& servertype, uint32 msgid, google::protobuf::Message* message )
    {
        auto strdata = message->SerializeAsString();
        SendMessageToType( servertype, msgid, strdata.data(), strdata.size() );
    }

    void KFTcpClientModule::SendMessageToType( const std::string& servertype, uint32 msgid, const char* data, uint32 length )
    {
        _kf_client_engine->SendMessageToType( servertype, msgid, data, length );
    }

    void KFTcpClientModule::SendMessageToName( const std::string& servername, uint32 msgid, google::protobuf::Message* message )
    {
        auto strdata = message->SerializeAsString();
        SendMessageToName( servername, msgid, strdata.data(), strdata.size() );
    }

    void KFTcpClientModule::SendMessageToName( const std::string& servername, uint32 msgid, const char* data, uint32 length )
    {
        _kf_client_engine->SendMessageToName( servername, msgid, data, length );
    }

    void KFTcpClientModule::SendMessageToServer( const std::string& servername, const std::string& servertype, uint32 msgid, google::protobuf::Message* message )
    {
        auto strdata = message->SerializeAsString();
        SendMessageToServer( servername, servertype, msgid, strdata.data(), strdata.size() );
    }

    void KFTcpClientModule::SendMessageToServer( const std::string& servername, const std::string& servertype, uint32 msgid, const char* data, uint32 length )
    {
        _kf_client_engine->SendMessageToServer( servername, servertype, msgid, data, length );
    }

    void KFTcpClientModule::HandleNetMessage( const KFGuid& guid, uint32 msgid, const char* data, uint32 length )
    {
        bool handleresult = _kf_message->CallFunction( guid, msgid, data, length );
        if ( handleresult )
        {
            return;
        }

        if ( _kf_transmit_function != nullptr )
        {
            auto ok = _kf_transmit_function( guid, msgid, data, length );
            if ( !ok )
            {
                KFLogger::LogNet( KFLogger::Error, "[%s] tcp client transmit msgid[%u] failed!",
                                  __FUNCTION__, msgid );
            }
        }
        else
        {
            KFLogger::LogSystem( KFLogger::Error, "msgid[%u] can't find function!", msgid );
        }
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void KFTcpClientModule::StartClient( const std::string& name, const std::string& type, uint32 id, const std::string& ip, uint32 port )
    {
        if ( IsSelfConnection( name, type, id ) )
        {
            return;
        }

        _kf_client_engine->StartClient( name, type, id, ip, port );
    }

    bool KFTcpClientModule::IsSelfConnection( const std::string& name, const std::string& type, uint32 id )
    {
        auto kfglobal = KFGlobal::Instance();

        if ( name == kfglobal->_app_name &&
                type == kfglobal->_app_type &&
                id == kfglobal->_app_id )
        {
            return true;
        }

        return false;
    }

    void KFTcpClientModule::CloseClient( uint32 serverid )
    {
        _kf_client_engine->CloseClient( serverid );
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////
    void KFTcpClientModule::AddConnectionFunction( const char* name, KFClientConnectionFunction& function )
    {
        auto kffunction = _kf_connection_function.Create( name );
        kffunction->_function = function;
    }

    void KFTcpClientModule::RemoveConnectionFunction( const char* name )
    {
        _kf_connection_function.Remove( name );
    }

    void KFTcpClientModule::CallClientConnectionFunction( uint32 serverid, const std::string& servername, const std::string& servertype )
    {
        for ( auto& iter : _kf_connection_function._objects )
        {
            auto kffunction = iter.second;
            kffunction->_function( serverid, servername, servertype );
        }
    }

    void KFTcpClientModule::AddLostFunction( const char* name, KFClientLostFunction& function )
    {
        auto kffunction = _kf_lost_function.Create( name );
        kffunction->_function = function;
    }

    void KFTcpClientModule::RemoveLostFunction( const char* name )
    {
        _kf_lost_function.Remove( name );
    }

    void KFTcpClientModule::CallClientLostFunction( uint32 serverid, const std::string& servername, const std::string& servertype )
    {
        for ( auto& iter : _kf_lost_function._objects )
        {
            auto kffunction = iter.second;
            kffunction->_function( serverid, servername, servertype );
        }
    }

    void KFTcpClientModule::RemoveTransmitFunction( const char* name )
    {
        _kf_transmit_function = nullptr;
    }

    void KFTcpClientModule::AddTransmitFunction( const char* name, KFTransmitFunction& function )
    {
        _kf_transmit_function = function;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    // 注册回馈
    __KF_MESSAGE_FUNCTION__( KFTcpClientModule::HandleRegisterAck )
    {
        __PROTO_PARSE__( KFMsg::RegisterToServerAck );

        auto servertype = kfmsg.apptype();
        auto serverid = kfmsg.appid();
        auto& servername = kfmsg.appname();

        // 处理回调函数
        CallClientConnectionFunction( serverid, servername, servertype );

        auto* kfclient = _kf_client_engine->FindClient( serverid );
        if ( kfclient != nullptr )
        {
            auto kfsetting = &kfclient->_net_setting;

            KFLogger::LogSystem( KFLogger::Info, "[%s:%s:%u|%s:%u] connect ok!",
                                 servername.c_str(), servertype.c_str(), serverid, kfsetting->_ip.c_str(), kfsetting->_port );
        }
    }
}