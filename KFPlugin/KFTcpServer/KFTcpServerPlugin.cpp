﻿#include "KFTcpServerPlugin.hpp"
#include "KFTcpServerModule.hpp"
#include "KFConfig/KFConfigInterface.h"
//////////////////////////////////////////////////////////////////////////
namespace KFrame
{
    void KFTcpServerPlugin::Install()
    {
        __REGISTER_MODULE__( KFTcpServer );
    }

    void KFTcpServerPlugin::UnInstall()
    {
        __UN_MODULE__( KFTcpServer );
    }

    void KFTcpServerPlugin::LoadModule()
    {
        __FIND_MODULE__( _kf_config, KFConfigInterface );
        __FIND_MODULE__( _kf_message, KFMessageInterface );
        __FIND_MODULE__( _kf_ip_address, KFIpAddressInterface );
    }

    void KFTcpServerPlugin::AddConfig()
    {
        __KF_ADD_CONFIG__( KFTcpServerConfig );
    }
}