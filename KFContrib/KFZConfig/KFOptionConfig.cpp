﻿#include "KFOptionConfig.hpp"

namespace KFrame
{
    KFOptionSetting* KFOptionConfig::CreateSetting( KFNode& xmlnode )
    {
        auto service = xmlnode.GetUInt32( "Service", true );
        auto channel = xmlnode.GetUInt32( "Channel", true );
        auto ok = KFGlobal::Instance()->CheckChannelService( channel, service );
        if ( !ok )
        {
            return nullptr;
        }

        return _settings.Create( 0u );
    }

    void KFOptionConfig::ReadSetting( KFNode& xmlnode, KFOptionSetting* kfsetting )
    {
        auto name = xmlnode.GetString( "Name" );
        auto key = xmlnode.GetString( "Key", true );
        auto value = xmlnode.GetString( "Value" );
        {
            auto kfoption = _option_list.Create( OptionKey( name, key ) );
            kfoption->_str_value = value;
            kfoption->_uint32_value = KFUtility::ToValue<uint32>( value );
            kfoption->_double_value = KFUtility::ToValue<double>( value );
        }
    }

    const KFOptionSetting* KFOptionConfig::FindOption( const std::string& name, const std::string& key ) const
    {
        auto kfoption = _option_list.Find( OptionKey( name, key ) );
        if ( kfoption == nullptr )
        {
            static KFOptionSetting _option;
            kfoption = &_option;
        }

        return kfoption;
    }
}