﻿#ifndef __KF_WEI_XIN__H__
#define __KF_WEI_XIN__H__

#include "KFChannel.h"

namespace KFrame
{
    class KFWeiXin : public KFChannel
    {
    public:
        KFWeiXin() = default;
        virtual ~KFWeiXin() = default;

        // 登录请求
        std::string RequestLogin( KFJson& json, const KFChannelSetting* kfsetting );

        // 充值请求
        std::string RequestPay( KFJson& json, const KFChannelSetting* kfsetting );
    };
}


#endif
