﻿#ifndef __NET_CLIENT_H__
#define __NET_CLIENT_H__

#include "KFrame.h"
#include "uv.h"
#include "KFNetSetting.h"
#include "KFNetConnector.h"

namespace KFrame
{
    class KFNetClientServices;
    class KFNetClient : public KFNetConnector
    {
    public:
        KFNetClient() = default;
        virtual ~KFNetClient() = default;

        ////////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////////
        // 初始化服务
        void StartClient( KFNetClientServices* netservices, const KFNetSetting& netsetting );

        // 关闭服务
        void CloseClient();

        // 开始连接
        virtual void StartSession();

        // 关闭逻辑
        virtual void CloseSession();

        // 断开事件
        virtual void OnDisconnect( int32 code, const char* function, uint32 line );

    private:
        // 启动连接定时器
        void StartConnectTimer( uint32 time );

        // 连接定时器回调
        static void OnTimerConnectCallBack( uv_timer_t* handle );

        // 尝试连接
        void TryConnect();
        static void OnConnectCallBack( uv_connect_t* handle, int status );

        // 连接失败
        void ConnectFailed( int32 status );

        // 连接成功
        void ConnectSuccess( uv_stream_t* );

        // 关闭回调
        static void OnShutDownCallBack( uv_handle_t* handle );

    public:
        // 网络配置
        KFNetSetting _net_setting;

    private:
        // 客户端服务
        uv_tcp_t _uv_client;

        // 连接句柄
        uv_connect_t _uv_connect;

        // 连接定时器
        uv_timer_t _uv_connect_timer;

    };
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif