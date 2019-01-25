﻿#ifndef __KF_MAIL_CLIENT_MODULE_H__
#define __KF_MAIL_CLIENT_MODULE_H__

/************************************************************************
//    @Module			:    邮件功能模块
//    @Author           :    __凌_痕__
//    @QQ				:    7969936
//    @Mail			    :    lori227@qq.com
//    @Date             :    2018-2-1
************************************************************************/

#include "KFrame.h"
#include "KFProtocol/KFProtocol.h"
#include "KFMailClientInterface.h"
#include "KFTimer/KFTimerInterface.h"
#include "KFConfig/KFConfigInterface.h"
#include "KFPlayer/KFPlayerInterface.h"
#include "KFKernel/KFKernelInterface.h"
#include "KFMessage/KFMessageInterface.h"
#include "KFDisplay/KFDisplayInterface.h"
#include "KFRouteClient/KFRouteClientInterface.h"

namespace KFrame
{
    class KFMailSetting;
    class KFMailClientModule : public KFMailClientInterface
    {
    public:
        KFMailClientModule() = default;
        ~KFMailClientModule() = default;

        // 初始化
        virtual void InitModule();

        // 刷新
        virtual void BeforeRun();

        // 关闭
        virtual void BeforeShut();
        ////////////////////////////////////////////////////////////////////////////////
        ////////////////////////////////////////////////////////////////////////////////
        /////////////////////////////////////////////////////////////////////////////////////////
        // 发送全局邮件
        virtual bool SendMail( uint32 configid, const KFElements* kfelements = nullptr );

        // 系统给某人发送邮件
        virtual bool SendMail( uint64 recvid, uint32 configid, const KFElements* kfelements = nullptr );

        // 某人给某人发送邮件
        virtual bool SendMail( KFEntity* player, uint64 recvid, uint32 configid, const KFElements* kfelements = nullptr );

    protected:

        // 客户端请求查询邮件
        __KF_MESSAGE_FUNCTION__( HandleQueryMailReq );

        // 新邮件通知
        __KF_MESSAGE_FUNCTION__( HandleNoticeNewMailReq );

        // 处理查询邮件回馈
        __KF_MESSAGE_FUNCTION__( HandleQueryMailAck );

        // 查看邮件
        __KF_MESSAGE_FUNCTION__( HandleViewMailReq );

        // 领取邮件奖励
        __KF_MESSAGE_FUNCTION__( HandleReceiveMailReq );

        // 处理删除邮件请求
        __KF_MESSAGE_FUNCTION__( HandleDeleteMailReq );

        // 处理邮件状态重置反馈
        __KF_MESSAGE_FUNCTION__( HandleUpdateMailStatusAck );

        // 定时查询邮件变化
        __KF_TIMER_FUNCTION__( OnTimerQueryMail );

    protected:
        // 进入游戏查询邮件信息
        void OnEnterQueryMail( KFEntity* player );

        // 离开回调
        void OnLeaveQueryMail( KFEntity* player );

        // 新玩家首次登陆处理
        void OnNewPlayerMail( KFEntity* player );

        //////////////////////////////////////////////////////////////////////////////////////
        // 发送消息到邮件
        bool SendMessageToMail( uint64 playerid, uint32 msgid, ::google::protobuf::Message* message );

        // 发送查询邮件消息
        void SendQueryMailMessage( KFEntity* player );

        // 判断邮件过期
        bool CheckMailTimeOut( KFData* kfmail );

        // 更新状态到邮件
        void UpdateFlagToMail( KFEntity* player, KFData* kfmail, uint32 status );

        // 领取邮件奖励
        void ReceiveMailReward( KFEntity* player, uint64 id );

        // 序列化邮件
        KFData* ParsePBMailToData( const KFMsg::PBMail* pbmail, const KFDataSetting* kfsetting );

        // 格式化邮件内容
        MapString& FormatMailData( KFEntity* sender, const KFMailSetting* kfsetting, const KFElements* kfelements );

        // 发送添加邮件
        bool SendAddMailToShard( uint64 sendid, uint32 flag, uint64 recvid, const MapString& maildata );
    };
}

#endif