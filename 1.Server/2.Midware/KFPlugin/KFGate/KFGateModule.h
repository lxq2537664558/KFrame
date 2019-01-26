﻿#ifndef __KF_GATE_MODULE_H__
#define __KF_GATE_MODULE_H__

/************************************************************************
//    @Module			:    网关功能模块
//    @Author           :    __凌_痕__
//    @QQ				:    7969936
//    @Mail			    :    lori227@qq.com
//    @Date             :    2017-11-1
************************************************************************/

#include "KFRole.h"
#include "KFGateInterface.h"
#include "KFZone/KFZoneInterface.h"
#include "KFTimer/KFTimerInterface.h"
#include "KFDisplay/KFDisplayInterface.h"
#include "KFMessage/KFMessageInterface.h"
#include "KFIpAddress/KFIpAddressInterface.h"
#include "KFTcpServer/KFTcpServerInterface.h"
#include "KFTcpClient/KFTcpClientInterface.h"
#include "KFHttpClient/KFHttpClientInterface.h"

namespace KFrame
{
    class KFGateModule : public KFGateInterface
    {
    public:
        KFGateModule() = default;
        ~KFGateModule() = default;

        // 刷新
        virtual void BeforeRun();

        // 关闭
        virtual void BeforeShut();

    protected:
        // 连接成功
        __KF_CLIENT_CONNECT_FUNCTION__( OnClientConnectionLogin );

        // 断开连接
        __KF_CLIENT_LOST_FUNCTION__( OnClientLostLogin );

        // 玩家掉线
        __KF_SERVER_LOST_FUNCTION__( OnPlayerDisconnection );

        // 发送消息到客户端
        __KF_TRANSMIT_MESSAGE_FUNCTION__( SendToClient );

        // 发送消息到游戏服务器
        __KF_TRANSMIT_MESSAGE_FUNCTION__( SendMessageToGame );

        // 更新在线玩家数量
        __KF_TIMER_FUNCTION__( OnTimerUpdateOnlineToAuth );
    protected:
        // 登录验证
        __KF_MESSAGE_FUNCTION__( HandleLoginVerifyReq );

        // 验证结果
        __KF_MESSAGE_FUNCTION__( HandleLoginVerifyAck );

        // 处理消息广播
        __KF_MESSAGE_FUNCTION__( HandleBroadcastMessageReq );

        // 踢出玩家
        __KF_MESSAGE_FUNCTION__( HandleKickGatePlayerReq );

        // 处理登录回馈
        __KF_MESSAGE_FUNCTION__( HandleLoginGameAck );

        // 登出游戏
        __KF_MESSAGE_FUNCTION__( HandleLoginOutReq );

    protected:
        // 发送登录失败消息
        void SendLoginFailedMessage( uint64 sessionid, uint32 result, uint64 bantime );

    private:
        // login服务器列表
        KFConHash _kf_login_conhash;

        // 玩家列表
        KFMap< uint64, uint64, KFRole > _kf_role_list;
    };
}

#endif