﻿#include "KFRelationShardPlugin.hpp"
#include "KFRelationShardModule.hpp"
#include "KFConfig/KFConfigInterface.h"
//////////////////////////////////////////////////////////////////////////

namespace KFrame
{
    void KFRelationShardPlugin::Install()
    {
        __REGISTER_MODULE__( KFRelationShard );
    }

    void KFRelationShardPlugin::UnInstall()
    {
        __UN_MODULE__( KFRelationShard );
    }

    void KFRelationShardPlugin::LoadModule()
    {
        __FIND_MODULE__( _kf_redis, KFRedisInterface );
        __FIND_MODULE__( _kf_config, KFConfigInterface );
        __FIND_MODULE__( _kf_message, KFMessageInterface );
        __FIND_MODULE__( _kf_display, KFDisplayInterface );
        __FIND_MODULE__( _kf_route, KFRouteClientInterface );
    }

    void KFRelationShardPlugin::AddConfig()
    {
        __KF_ADD_CONFIG__( KFRelationConfig );
    }

}