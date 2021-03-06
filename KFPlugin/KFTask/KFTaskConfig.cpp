﻿#include "KFTaskConfig.hpp"

namespace KFrame
{
    void KFTaskConfig::ClearSetting()
    {
        _task_types.clear();
        KFConfigT< KFTaskSetting >::ClearSetting();
    }

    void KFTaskConfig::ReadSetting( KFNode& xmlnode, KFTaskSetting* kfsetting )
    {
        kfsetting->_parent_name = xmlnode.GetString( "ParentName" );
        kfsetting->_data_name = xmlnode.GetString( "DataName" );
        kfsetting->_data_key = xmlnode.GetUInt32( "DataKey" );
        kfsetting->_need_receive = xmlnode.GetBoolen( "Receive" );
        kfsetting->_handle_type = xmlnode.GetUInt32( "HandleType" );

        auto strstarttime = xmlnode.GetString( "StartTime" );
        if ( !strstarttime.empty() )
        {
            kfsetting->_start_hour = KFUtility::SplitValue< uint32 >( strstarttime, ":" );
            kfsetting->_start_minute = KFUtility::SplitValue< uint32 >( strstarttime, ":" );
        }

        auto strendtime = xmlnode.GetString( "EndTime" );
        if ( !strendtime.empty() )
        {
            kfsetting->_start_hour = KFUtility::SplitValue< uint32 >( strendtime, ":" );
            kfsetting->_start_minute = KFUtility::SplitValue< uint32 >( strendtime, ":" );
        }

        kfsetting->_trigger_type = xmlnode.GetUInt32( "TriggerType" );
        kfsetting->_trigger_value = xmlnode.GetUInt32( "TriggerValue" );
        kfsetting->_operate = xmlnode.GetUInt32( "Operate" );
        kfsetting->_use_type = xmlnode.GetUInt32( "UseType" );
        kfsetting->_use_value = xmlnode.GetUInt32( "UseValue" );
        kfsetting->_done_type = xmlnode.GetUInt32( "DoneType" );
        kfsetting->_done_value = xmlnode.GetUInt32( "DoneValue" );

        kfsetting->_next_id = xmlnode.GetUInt32( "NextId" );
        kfsetting->_next_value = xmlnode.GetUInt32( "NextValue" );

        auto strlimits = xmlnode.GetString( "Limits " );
        if ( !strlimits.empty() )
        {
            kfsetting->_limits.Parse( strlimits, __FUNC_LINE__ );
        }

        auto strrewards = xmlnode.GetString( "Rewards" );
        if ( !strrewards.empty() )
        {
            kfsetting->_rewards.Parse( strrewards, __FUNC_LINE__ );
        }

        AddTaskType( kfsetting );
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFTaskSetting::CheckCanUpdate( uint64 key, uint64 operate ) const
    {
        if ( _data_key != 0 && _data_key != key )
        {
            return false;
        }

        if ( _trigger_type != 0 && _trigger_type != operate )
        {
            return false;
        }

        // 判断是否在时间范围内
        if ( _start_hour != 0 && _start_minute != 0 )
        {
            if ( !KFDate::CheckPassTime( 0, 0, 0, _start_hour, _start_minute ) )
            {
                return false;
            }
        }

        if ( _end_hour != 0 && _end_minute != 0 )
        {
            if ( KFDate::CheckPassTime( 0, 0, 0, _end_hour, _end_minute ) )
            {
                return false;
            }
        }

        return true;
    }

    uint64 KFTaskSetting::CheckTriggerValue( uint64 operatevalue, uint64 nowvalue ) const
    {
        if ( _use_type == KFEnum::UseFinal )
        {
            operatevalue = nowvalue;
        }

        if ( operatevalue < _trigger_value )
        {
            return 0u;
        }

        if ( _use_value != 0u )
        {
            operatevalue = _use_value;
        }

        return operatevalue;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    void KFTaskTypes::AddTaskType( KFTaskSetting* setting )
    {
        auto iter = _task_type.find( setting->_data_name );
        if ( iter == _task_type.end() )
        {
            iter = _task_type.insert( std::make_pair( setting->_data_name, KFTaskType() ) ).first;
        }

        iter->second.AddTaskType( setting );
    }

    const KFTaskType* KFTaskTypes::FindTaskType( const std::string& dataname ) const
    {
        auto iter = _task_type.find( dataname );
        if ( iter == _task_type.end() )
        {
            return nullptr;
        }

        return &iter->second;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////////////////
    void KFTaskConfig::AddTaskType( KFTaskSetting* kfsetting )
    {
        if ( kfsetting->_parent_name.empty() || kfsetting->_data_name.empty() )
        {
            return;
        }

        auto iter = _task_types.find( kfsetting->_parent_name );
        if ( iter == _task_types.end() )
        {
            iter = _task_types.insert( std::make_pair( kfsetting->_parent_name, KFTaskTypes() ) ).first;
        }

        iter->second.AddTaskType( kfsetting );
    }

    const KFTaskType* KFTaskConfig::FindTypeTaskList( const std::string& parentname, const std::string& dataname ) const
    {
        auto iter = _task_types.find( parentname );
        if ( iter == _task_types.end() )
        {
            return nullptr;
        }

        return iter->second.FindTaskType( dataname );
    }

}

