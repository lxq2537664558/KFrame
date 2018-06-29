﻿#ifndef __KF_LOGIN_LOGIN_CONFIG_H__
#define __KF_LOGIN_LOGIN_CONFIG_H__

#include "KFrame.h"
#include "KFConfig/KFConfigInterface.h"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////
    class KFLoginLoginConfig : public KFConfig, public KFSingleton< KFLoginLoginConfig >
    {
    public:
        KFLoginLoginConfig();
        ~KFLoginLoginConfig();

        bool LoadConfig( const char* file );

    public:

        // 世界服务器类型
        uint32 _world_server_type;

        // Gate服务器类型
        uint32 _gate_server_type;
    };

    //////////////////////////////////////////////////////////////////////////////////////////////////
    static auto* _kf_login_login_config = KFLoginLoginConfig::Instance();
    //////////////////////////////////////////////////////////////////////////////////////////////////
}

#endif