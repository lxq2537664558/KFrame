﻿#include "KFRankShardPlugin.hpp"
#include "KFRankShardModule.hpp"
#include "KFConfig/KFConfigInterface.h"
//////////////////////////////////////////////////////////////////////////

namespace KFrame
{
    void KFRankShardPlugin::Install()
    {
        __REGISTER_MODULE__( KFRankShard );
    }

    void KFRankShardPlugin::UnInstall()
    {
        __UN_MODULE__( KFRankShard );
    }

    void KFRankShardPlugin::LoadModule()
    {
        __FIND_MODULE__( _kf_redis, KFRedisInterface );
        __FIND_MODULE__( _kf_config, KFConfigInterface );
        __FIND_MODULE__( _kf_message, KFMessageInterface );
        __FIND_MODULE__( _kf_route, KFRouteClientInterface );
    }

    void KFRankShardPlugin::AddConfig()
    {
        __KF_ADD_CONFIG__( KFRankConfig );
    }
}