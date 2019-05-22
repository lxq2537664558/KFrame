﻿#include "KFCompoundConfig.hpp"

namespace KFrame
{
    bool KFCompoundConfig::LoadConfig()
    {
        KFXml kfxml( _file );
        auto config = kfxml.RootNode();
        auto setting = config.FindNode( "Setting" );
        while ( setting.IsValid() )
        {

            auto id = setting.GetUInt32( "Id" );
            auto kfsetting = _compound_setting.Create( id );

            kfsetting->_id = id;
            kfsetting->_key = setting.GetUInt32( "DataKey" );
            kfsetting->_data_name = setting.GetString( "DataName" );

            auto strcompounddata = setting.GetString( "CompoundData" );
            kfsetting->_compound_data.Parse( strcompounddata, __FUNC_LINE__ );

            auto strcostdata = setting.GetString( "CostData" );
            kfsetting->_cost_data.Parse( strcostdata, __FUNC_LINE__ );

            setting.NextNode();
        }
        //////////////////////////////////////////////////////////////////

        return true;
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////
    const KFCompoundSetting* KFCompoundConfig::FindCompoundSetting( uint32 id )
    {
        return _compound_setting.Find( id );
    }
}