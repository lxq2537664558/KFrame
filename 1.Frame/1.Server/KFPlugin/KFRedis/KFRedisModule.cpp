﻿#include "KFRedisModule.hpp"
#include "KFRedisConfig.hpp"

namespace KFrame
{
    void KFRedisModule::InitModule()
    {
        __KF_ADD_CONFIG__( _kf_redis_config, false );
    }

    void KFRedisModule::ShutDown()
    {
        {
            KFLocker lock( _mt_mutex );
            for ( auto& iter : _redis_logic._objects )
            {
                iter.second->ShutDown();
            }
        }

        __KF_REMOVE_CONFIG__( _kf_redis_config );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    KFRedisDriver* KFRedisModule::Create( const std::string& module, uint32 logicid /* = 0 */ )
    {
        auto kfredistype = _kf_redis_config->FindRedisType( module, logicid );
        if ( kfredistype == nullptr )
        {
            __LOG_ERROR__( "[{}:{}] can't find redis type!", module, logicid );
            return nullptr;
        }

        auto kfredislogic = FindRedisLogic( kfredistype->_id );
        if ( kfredislogic != nullptr )
        {
            return kfredislogic;
        }

        kfredislogic = __KF_NEW__( KFRedisLogic );
        kfredislogic->Initialize( kfredistype );

        InsertRedisLogic( kfredistype->_id, kfredislogic );
        return kfredislogic;
    }

    KFRedisLogic* KFRedisModule::FindRedisLogic( uint32 id )
    {
        auto threadid = KFThread::GetThreadID();
        auto key = RedisKey( threadid, id );

        KFLocker lock( _mt_mutex );
        return _redis_logic.Find( key );
    }

    void KFRedisModule::InsertRedisLogic( uint32 id, KFRedisLogic* kfredislogic )
    {
        auto threadid = KFThread::GetThreadID();
        auto key = RedisKey( threadid, id );

        KFLocker lock( _mt_mutex );
        _redis_logic.Insert( key, kfredislogic );
    }
}