﻿#include "KFEntityEx.hpp"
#include "KFComponentEx.hpp"
#include "KFKernelModule.hpp"
#include "KFDataFactory.hpp"
#include "KFProtocol/KFProtocol.h"
//////////////////////////////////////////////////////////////////////////

namespace KFrame
{
    KFEntityEx::KFEntityEx()
    {
        _is_inited = false;
        _kf_component = nullptr;
        _have_add_pb_object = false;
        _have_remove_pb_object = false;
        _have_update_pb_object = false;
    }

    KFEntityEx::~KFEntityEx()
    {
    }

    // 是否初始化完成
    bool KFEntityEx::IsInited()
    {
        return _is_inited;
    }

    void KFEntityEx::SetInited()
    {
        _is_inited = true;
    }

    bool KFEntityEx::IsNew()
    {
        return _is_new;
    }

    void KFEntityEx::SetNew( bool isnew )
    {
        _is_new = isnew;
    }

    void KFEntityEx::InitData( KFComponentEx* kfcomponent )
    {
        _kf_component = kfcomponent;
        KFDataFactory::InitData( this, _kf_component->_data_setting->_class_setting, _kf_component->_data_setting );
    }

    KFData* KFEntityEx::CreateData( const std::string& dataname )
    {
        auto kfdata = Find( dataname );
        if ( kfdata == nullptr )
        {
            return nullptr;
        }

        return KFDataFactory::CreateData( kfdata->_data_setting );
    }

    KFData* KFEntityEx::CreateData( const std::string& dataname, uint64 key )
    {
        auto kfdata = CreateData( dataname );
        if ( kfdata == nullptr )
        {
            return nullptr;
        }

        kfdata->SetKeyID( key );
        return kfdata;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////////
    void KFEntityEx::UpdateData( KFData* kfdata, const std::string& value )
    {
        kfdata->Set<std::string>( value );
        if ( kfdata->_data_type == KFDataDefine::Type_Array )
        {
            for ( uint32 i = KFDataDefine::Array_Index; i < kfdata->Size(); ++i )
            {
                auto kfchild = kfdata->Find( i );
                if ( kfchild != nullptr )
                {
                    auto newvalue = kfchild->Get<uint64>();
                    _kf_component->UpdateDataCallBack( this, i, kfchild, i, KFEnum::Set, newvalue, 0u, newvalue, true );
                }
            }
        }
        else if ( kfdata->_data_type == KFDataDefine::Type_String )
        {
            // 属性更新回调
            _kf_component->UpdateDataCallBack( this, kfdata, value, true );
        }
    }

    void KFEntityEx::UpdateData( KFData* kfparent, const std::string& dataname, const std::string& value )
    {
        auto kfdata = kfparent->Find( dataname );
        if ( kfdata == nullptr )
        {
            return;
        }

        UpdateData( kfdata, value );
    }

    void KFEntityEx::UpdateData( const std::string& dataname, const std::string& value )
    {
        auto kfdata = Find( dataname );
        if ( kfdata == nullptr )
        {
            return;
        }

        UpdateData( kfdata, value );
    }


    void KFEntityEx::UpdateData( const std::string& parentname, const std::string& dataname, const std::string& value )
    {
        auto kfdata = Find( parentname, dataname );
        if ( kfdata == nullptr )
        {
            return;
        }

        UpdateData( kfdata, value );
    }

    void KFEntityEx::UpdateData( const std::string& parentname, uint64 key, const std::string& dataname, const std::string& value )
    {
        auto kfdata = Find( parentname, key );
        if ( kfdata == nullptr )
        {
            return;
        }

        UpdateData( kfdata, value );
    }

    uint64 KFEntityEx::UpdateData( const std::string& dataname, uint32 operate, uint64 value )
    {
        auto kfdata = Find( dataname );
        if ( kfdata == nullptr )
        {
            return _invalid_int;
        }

        return UpdateData( _invalid_int, kfdata, operate, value );
    }

    uint64 KFEntityEx::UpdateData( const std::string& parentname, const std::string& dataname, uint32 operate, uint64 value )
    {
        auto kfdata = Find( parentname, dataname );
        if ( kfdata == nullptr )
        {
            return _invalid_int;
        }

        return UpdateData( _invalid_int, kfdata, operate, value );
    }

    uint64 KFEntityEx::UpdateData( const std::string& parentname, uint64 key, const std::string& dataname, uint32 operate, uint64 value )
    {
        auto kfparent = Find( parentname );
        if ( kfparent == nullptr )
        {
            return false;
        }

        return UpdateData( kfparent, key, dataname, operate, value );
    }

    uint64 KFEntityEx::UpdateData( KFData* kfparent, const std::string& dataname, uint32 operate, uint64 value )
    {
        auto kfdata = kfparent->Find( dataname );
        if ( kfdata == nullptr )
        {
            return _invalid_int;
        }

        return UpdateData( kfparent->GetKeyID(), kfdata, operate, value );
    }

    uint64 KFEntityEx::UpdateData( KFData* kfparent, uint64 key, const std::string& dataname, uint32 operate, uint64 value )
    {
        // 不存在, 创建
        auto kfobject = kfparent->Find( key );
        if ( kfobject == nullptr )
        {
            kfobject = KFDataFactory::CreateData( kfparent->_data_setting );
            value = kfobject->Operate( dataname, operate, value );
            AddData( kfparent, key, kfobject );
            return value;
        }

        // 存在就更新
        auto kfdata = kfobject->Find( dataname );
        if ( kfdata == nullptr )
        {
            return _invalid_int;
        }

        return UpdateData( key, kfdata, operate, value );
    }

    uint64 KFEntityEx::UpdateData( KFData* kfdata, uint32 operate, uint64 value )
    {
        return UpdateData( _invalid_int, kfdata, operate, value );
    }

    uint64 KFEntityEx::UpdateData( uint64 key, KFData* kfdata, const std::string& dataname, uint32 operate, uint64 value )
    {
        auto kfchild = kfdata->Find( dataname );
        if ( kfchild == nullptr )
        {
            return 0u;
        }

        return UpdateData( key, kfchild, operate, value );
    }

    uint64 KFEntityEx::UpdateData( uint64 key, KFData* kfdata, uint32 operate, uint64 value )
    {
        auto oldvalue = kfdata->Get< uint64 >();
        auto newvalue = kfdata->Operate( operate, value );
        if ( oldvalue != newvalue )
        {
            // 属性更新回调
            _kf_component->UpdateDataCallBack( this, key, kfdata, _invalid_int, operate, value, oldvalue, newvalue, true );
        }

        return newvalue;
    }

    uint64 KFEntityEx::UpdateData( const std::string& dataname, uint64 index, uint32 operate, uint64 value )
    {
        auto kfdata = Find( dataname );
        if ( kfdata == nullptr )
        {
            return 0u;
        }

        return UpdateData( index, kfdata, index, operate, value );
    }

    uint64 KFEntityEx::UpdateData( KFData* kfdata, uint64 index, uint32 operate, uint64 value )
    {
        return UpdateData( index, kfdata, index, operate, value );
    }

    uint64 KFEntityEx::UpdateData( uint64 key, KFData* kfdata, uint64 index, uint32 operate, uint64 value )
    {
        auto kfchild = kfdata->Find( index );
        if ( kfchild == nullptr )
        {
            return _invalid_int;
        }

        auto oldvalue = kfchild->Get< uint64 >();
        auto newvalue = kfchild->Operate( operate, value );
        if ( oldvalue != newvalue )
        {
            // 属性更新回调
            _kf_component->UpdateDataCallBack( this, key, kfchild, index, operate, value, oldvalue, newvalue, true );
        }

        return newvalue;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFEntityEx::AddData( const std::string& parentname, uint64 key, KFData* kfdata, bool callback )
    {
        auto kfparent = Find( parentname );
        if ( kfparent == nullptr )
        {
            return false;
        }

        return AddData( kfparent, key, kfdata, callback );
    }

    bool KFEntityEx::AddData( KFData* kfparent, uint64 key, KFData* kfdata, bool callback )
    {
        bool result = kfparent->Add( key, kfdata );
        if ( result )
        {
            // 添加属性回调
            _kf_component->AddDataCallBack( this, kfparent, key, kfdata, callback );
        }

        return result;
    }

    bool KFEntityEx::AddData( KFData* kfparent, KFData* kfdata, bool callback )
    {
        auto key = kfdata->GetKeyID();
        return AddData( kfparent, key, kfdata, callback );
    }

    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFEntityEx::RemoveData( const std::string& parentname, uint64 key, bool callback )
    {
        auto kfparent = Find( parentname );
        if ( kfparent == nullptr )
        {
            return false;
        }

        return RemoveData( kfparent, key, callback );
    }

    bool KFEntityEx::RemoveData( KFData* kfparent, uint64 key, bool callback )
    {
        auto kfdata = kfparent->Find( key );
        if ( kfdata == nullptr )
        {
            return false;
        }

        // 属性删除回调
        _kf_component->RemoveDataCallBack( this, kfparent, key, kfdata, callback );
        return kfparent->Remove( key );
    }

    bool KFEntityEx::CleanData( const std::string& parentname, bool callback )
    {
        auto kfparent = Find( parentname );
        if ( kfparent == nullptr )
        {
            return false;
        }

        return CleanData( kfparent, callback );
    }

    bool KFEntityEx::CleanData( KFData* kfparent, bool callback )
    {
        ListUInt64 keys;
        for ( auto kfdata = kfparent->First(); kfdata != nullptr; kfdata = kfparent->Next() )
        {
            keys.push_back( kfdata->GetKeyID() );
        }

        for ( auto key : keys )
        {
            RemoveData( kfparent, key, callback );
        }

        return true;
    }

    bool KFEntityEx::RemoveData( KFData* kfparent, const std::string& dataname, bool callback )
    {
        auto kfdata = kfparent->Find( dataname );
        if ( kfdata == nullptr )
        {
            return false;
        }

        _kf_component->RemoveDataCallBack( this, kfparent, kfdata->GetKeyID(), kfdata, callback );
        return kfparent->Remove( dataname );
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    KFData* KFEntityEx::MoveData( const std::string& sourcename, uint64 key, const std::string& targetname )
    {
        auto sourcedata = Find( sourcename );
        auto targetdata = Find( targetname );
        if ( sourcedata == nullptr )
        {
            return nullptr;
        }

        return MoveData( sourcedata, key, targetdata );
    }

    KFData* KFEntityEx::MoveData( KFData* sourcedata, uint64 key, KFData* targetdata )
    {
        auto kfdata = sourcedata->Move( key );
        if ( kfdata == nullptr )
        {
            return nullptr;
        }
        _kf_component->RemoveDataCallBack( this, sourcedata, key, kfdata, false );

        if ( targetdata != nullptr )
        {
            targetdata->Add( key, kfdata );
            _kf_component->AddDataCallBack( this, targetdata, key, kfdata, false );
        }

        return kfdata;
    }

    KFData* KFEntityEx::MoveData( KFData* sourcedata, const std::string& dataname, const std::string& targetname )
    {
        auto targetdata = Find( targetname );
        if ( targetdata == nullptr )
        {
            return nullptr;
        }

        return MoveData( sourcedata, dataname, targetdata );
    }

    KFData* KFEntityEx::MoveData( KFData* sourcedata, const std::string& dataname, KFData* targetdata )
    {
        // 移除属性
        auto kfdata = sourcedata->Move( dataname, true );
        if ( kfdata == nullptr )
        {
            return nullptr;
        }
        _kf_component->RemoveDataCallBack( this, sourcedata, 0u, kfdata, false );

        // 添加属性
        auto uuid = kfdata->GetKeyID();
        targetdata->Add( uuid, kfdata );
        _kf_component->AddDataCallBack( this, targetdata, uuid, kfdata, false );

        return kfdata;
    }

    KFData* KFEntityEx::MoveData( KFData* sourcedata, uint64 key, KFData* targetdata, const std::string& dataname )
    {
        // 移除属性
        auto kfdata = sourcedata->Move( key );
        if ( kfdata == nullptr )
        {
            return nullptr;
        }
        _kf_component->RemoveDataCallBack( this, sourcedata, key, kfdata, false );

        // 添加属性
        targetdata->Add( dataname, kfdata );
        SyncUpdateData( kfdata, key );

        return kfdata;
    }

    KFData* KFEntityEx::MoveData( KFData* sourcedata, const std::string& sourcename, KFData* targetdata, const std::string& targetname )
    {
        // 移除属性
        auto kfdata = sourcedata->Move( sourcename, true );
        if ( kfdata == nullptr )
        {
            return nullptr;
        }
        _kf_component->RemoveDataCallBack( this, sourcedata, 0u, kfdata, false );

        // 添加属性
        targetdata->Add( targetname, kfdata );
        SyncUpdateData( kfdata, 0u );
        return kfdata;
    }

    uint64 KFEntityEx::MoveData( KFData* kfparent, const std::string& dataname, uint32 operate, uint64 value )
    {
        auto kfdata = kfparent->Find( dataname );
        if ( kfdata == nullptr )
        {
            return _invalid_int;
        }

        return MoveData( kfparent->GetKeyID(), kfdata, operate, value );
    }

    uint64 KFEntityEx::MoveData( uint64 key, KFData* kfdata, uint32 operate, uint64 value )
    {
        auto oldvalue = kfdata->Get< uint64 >();
        auto newvalue = kfdata->Operate( operate, value );
        if ( oldvalue != newvalue )
        {
            // 属性更新回调
            _kf_component->UpdateDataCallBack( this, key, kfdata, _invalid_int, operate, value, oldvalue, newvalue, false );
        }

        return newvalue;
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    void KFEntityEx::AddShowElement( uint32 showtype, const KFElement* kfelement, KFData* kfdata, const char* function, uint32 line )
    {
        // 打印日志
        if ( showtype == KFDataDefine::Show_Element )
        {
            AddElementToShow( kfelement, false );
            __LOG_INFO_FUNCTION__( function, line, "add={}", kfelement->ToString() );
        }
        else if ( showtype == KFDataDefine::Show_Data )
        {
            AddDataToShow( kfdata, false );
            __LOG_INFO_FUNCTION__( function, line, "add={{\"{}\":{}}}", kfelement->_data_name, kfdata->ToString() );
        }
    }

    KFMsg::PBShowData* KFEntityEx::CreateShowData( const std::string& name, uint64 value, bool find )
    {
        if ( find )
        {
            for ( auto i = 0; i < _pb_show_element.pbdata_size(); ++i )
            {
                auto pbdata = _pb_show_element.mutable_pbdata( i );
                if ( pbdata->name() != name )
                {
                    continue;
                }

                auto kfdatasetting = _kf_component->_data_setting->_class_setting->FindSetting( name );
                if ( kfdatasetting == nullptr )
                {
                    continue;
                }

                // 如果是record/object 判断value是否相同
                if ( kfdatasetting->_type == KFDataDefine::Type_Record || kfdatasetting->_type == KFDataDefine::Type_Object )
                {
                    if ( pbdata->value() != value )
                    {
                        continue;
                    }
                }
                else
                {
                    pbdata->set_value( pbdata->value() + value );
                }

                return pbdata;
            }
        }

        _have_show_client = true;
        _kf_component->AddSyncEntity( this );

        auto pbdata = _pb_show_element.add_pbdata();
        pbdata->set_name( name );
        pbdata->set_value( value );
        return pbdata;
    }

    void KFEntityEx::AddElementToShow( const KFElement* kfelement, bool find )
    {
        if ( _pb_show_element.modulename().empty() )
        {
            return;
        }

        if ( kfelement->IsValue() )
        {
            auto kfelementvalue = reinterpret_cast< const KFElementValue* >( kfelement );
            if ( kfelementvalue->_value->IsNeedShow() )
            {
                CreateShowData( kfelementvalue->_data_name, kfelementvalue->_value->GetUseValue(), find );
            }
        }
        else if ( kfelement->IsObject() )
        {
            auto kfelementobject = reinterpret_cast< const KFElementObject* >( kfelement );
            if ( kfelementobject->IsNeedShow() )
            {
                auto pbshowdata = CreateShowData( kfelementobject->_data_name, kfelementobject->_config_id, find );
                ( *pbshowdata->mutable_pbuint64() )[ __STRING__( id ) ] = kfelementobject->_config_id;
                for ( auto& iter : kfelementobject->_values._objects )
                {
                    auto kfvalue = iter.second;
                    if ( kfvalue->IsNeedShow() )
                    {
                        ( *pbshowdata->mutable_pbuint64() )[ iter.first ] = kfvalue->GetUseValue();
                    }
                }
            }
        }
    }

    void KFEntityEx::AddDataToShow( const std::string& name, uint64 value, bool find )
    {
        if ( _pb_show_element.modulename().empty() )
        {
            return;
        }

        CreateShowData( name, value, find );
    }

    void KFEntityEx::AddDataToShow( const std::string& modulename, const std::string& name, uint64 value, bool find )
    {
        if ( value == 0u )
        {
            return;
        }

        _pb_show_element.set_modulename( modulename );
        AddDataToShow( name, value, find );
    }

    void KFEntityEx::AddDataToShow( const std::string& name, uint64 value, KeyValue& values, bool find )
    {
        if ( _pb_show_element.modulename().empty() )
        {
            return;
        }

        auto pbshowdata = CreateShowData( name, value, find );
        for ( auto& iter : values )
        {
            ( *pbshowdata->mutable_pbuint64() )[ iter.first ] += iter.second;
        }
    }

    void KFEntityEx::AddDataToShow( const std::string& modulename, const std::string& name, uint64 value, KeyValue& values, bool find )
    {
        _pb_show_element.set_modulename( modulename );
        AddDataToShow( name, value, values, find );
    }

    void KFEntityEx::AddDataToShow( KFData* kfdata, bool find )
    {
        if ( _pb_show_element.modulename().empty() ||
                !kfdata->_data_setting->HaveMask( KFDataDefine::Mask_Show ) )
        {
            return;
        }

        switch ( kfdata->_data_type )
        {
        case KFDataDefine::Type_Int32:
        case KFDataDefine::Type_UInt32:
        case KFDataDefine::Type_Int64:
        case KFDataDefine::Type_UInt64:
        {
            CreateShowData( kfdata->_data_setting->_name, kfdata->Get(), find );
            break;
        }
        case KFDataDefine::Type_Object:
        case KFDataDefine::Type_Record:
        {
            auto configid = kfdata->Get( kfdata->_data_setting->_config_key_name );
            auto pbshowdata = CreateShowData( kfdata->_data_setting->_name, configid, find );
            for ( auto kfchild = kfdata->First(); kfchild != nullptr; kfchild = kfdata->Next() )
            {
                if ( !kfchild->_data_setting->HaveMask( KFDataDefine::Mask_Show ) ||
                        !kfchild->IsValid() )
                {
                    continue;
                }

                ( *pbshowdata->mutable_pbuint64() )[ kfchild->_data_setting->_name ] = kfchild->Get();
            }
            break;
        }
        }
    }

    void KFEntityEx::AddDataToShow( const std::string& modulename, KFData* kfdata, bool find )
    {
        _pb_show_element.set_modulename( modulename );
        AddDataToShow( kfdata, find );
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    const std::string& KFEntityEx::CheckAddElement( const KFElements* kfelements, const char* function, uint32 line, float multiple /* = 1.0f */ )
    {
        for ( auto kfelement : kfelements->_element_list )
        {
            auto ok = CheckAddElement( kfelement, function, line, multiple );
            if ( !ok )
            {
                return kfelement->_data_name;
            }
        }

        return _invalid_string;
    }

    bool KFEntityEx::CheckAddElement( const KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        auto kfdata = Find( kfelement->_data_name );
        if ( kfdata == nullptr )
        {
            __LOG_ERROR_FUNCTION__( function, line, "can't find data=[{}]! ", kfelement->_data_name );
            return false;
        }

        // 如果有注册函数, 执行注册函数
        auto kffunction = _kf_component->_check_add_element_function.Find( kfdata->_data_setting->_logic_name );
        if ( kffunction != nullptr )
        {
            return kffunction->_function( this, kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
        }

        // 找不到处理函数, 用基础函数来处理
        return !kfdata->IsFull();
    }

    void KFEntityEx::AddElement( const KFElements* kfelements, const std::string& modulename, const char* function, uint32 line, float multiple )
    {
        if ( !kfelements->_element_list.empty() )
        {
            _pb_show_element.set_modulename( modulename );
        }

        AddElement( kfelements, function, line, multiple );
    }


    void KFEntityEx::AddElement( const KFElements* kfelements, const char* function, uint32 line, float multiple )
    {
        if ( kfelements->_element_list.empty() )
        {
            return __LOG_ERROR_FUNCTION__( function, line, "{}=[{}] element=[{}] is empty!", _kf_component->_component_name, GetKeyID(), kfelements->_str_element );
        }

        __LOG_INFO_FUNCTION__( function, line, "{}=[{}] multiple=[{:0.2f}] elements={}!", _kf_component->_component_name, GetKeyID(), multiple, kfelements->_str_element );
        for ( auto kfelement : kfelements->_element_list )
        {
            AddElement( kfelement, function, line, multiple );
        }
    }


    // 添加元数据
    void KFEntityEx::AddElement( const KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        auto kfdata = Find( kfelement->_data_name );
        if ( kfdata == nullptr )
        {
            return __LOG_ERROR_FUNCTION__( function, line, "can't find data=[{}]! ", kfelement->_data_name );
        }

        KFData* showdata = nullptr;
        uint32 showtype = KFDataDefine::Show_None;
        const_cast< KFElement* >( kfelement )->_data_setting = kfdata->_data_setting;

        // 如果有注册的特殊处理函数
        auto kffunction = _kf_component->_add_element_function.Find( kfdata->_data_setting->_logic_name );
        if ( kffunction != nullptr )
        {
            std::tie( showtype, showdata ) = kffunction->_function( this, kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
        }
        else
        {
            // 没有注册的函数
            switch ( kfdata->_data_type )
            {
            case KFDataDefine::Type_Object:
                std::tie( showtype, showdata ) = AddObjectElement( kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
                break;
            case KFDataDefine::Type_Record:
                std::tie( showtype, showdata ) = AddRecordElement( kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
                break;
            default:
                std::tie( showtype, showdata ) = AddNormalElement( kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
                break;
            }
        }

        if ( showtype != KFDataDefine::Show_None )
        {
            AddShowElement( showtype, kfelement, showdata, __FUNC_LINE__ );
        }
    }

    std::tuple<uint32, KFData*> KFEntityEx::AddNormalElement( KFData* kfdata, KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        if ( !kfelement->IsValue() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not value!", kfelement->_data_name );
            return std::make_tuple( KFDataDefine::Show_None, nullptr );
        }

        auto kfelementvalue = reinterpret_cast< KFElementValue* >( kfelement );
        switch ( kfelementvalue->_value->_type )
        {
        case KFDataDefine::Type_UInt32:
        {
            auto value = kfelementvalue->_value->CalcUseValue( kfdata->_data_setting, multiple );
            UpdateData( kfdata, kfelementvalue->_operate, value );
        }
        break;
        case KFDataDefine::Type_String:
        {
            UpdateData( kfdata, kfelementvalue->_value->GetValue() );
        }
        break;
        default:
            break;
        }

        return std::make_tuple( KFDataDefine::Show_Element, kfdata );
    }

    void KFEntityEx::UpdateElementToData( KFElementObject* kfelement, KFData* kfdata, float multiple /* = 1.0f */  )
    {
        for ( auto& iter : kfelement->_values._objects )
        {
            auto kfchild = kfdata->Find( iter.first );
            if ( kfchild == nullptr ||
                    kfchild->_data_setting->_name == kfdata->_data_setting->_key_name ||
                    kfchild->_data_setting->_name == kfdata->_data_setting->_config_key_name )
            {
                continue;
            }

            auto kfvalue = iter.second;
            switch ( kfvalue->_type )
            {
            case KFDataDefine::Type_UInt32:
            {
                auto value = kfvalue->CalcUseValue( kfchild->_data_setting, multiple );
                UpdateData( 0, kfchild, kfelement->_operate, value );
            }
            break;
            case KFDataDefine::Type_String:
            {
                UpdateData( kfchild, kfvalue->GetValue() );
            }
            break;
            case KFDataDefine::Type_Object:
            {
                auto kfobjvalue = static_cast< KFObjValue* >( kfvalue );
                UpdateElementToData( kfobjvalue->_element, kfchild, multiple );
            }
            break;
            default:
                break;
            }
        }
    }

    void KFEntityEx::SetElementToData( KFElementObject* kfelement, KFData* kfdata, float multiple /* = 1.0f */ )
    {
        for ( auto& iter : kfelement->_values._objects )
        {
            auto kfchild = kfdata->Find( iter.first );
            if ( kfchild == nullptr )
            {
                continue;
            }

            auto kfvalue = iter.second;
            switch ( kfvalue->_type )
            {
            case KFDataDefine::Type_UInt32:
            {
                auto value = kfvalue->CalcUseValue( kfchild->_data_setting, multiple );
                kfchild->Set( value );
            }
            break;
            case KFDataDefine::Type_String:
            {
                kfchild->Set( kfvalue->GetValue() );
            }
            break;
            case KFDataDefine::Type_Object:
            {
                auto kfobjvalue = static_cast< KFObjValue* >( kfvalue );
                SetElementToData( kfobjvalue->_element, kfchild, multiple );
            }
            break;
            default:
                break;
            }
        }
    }

    std::tuple<uint32, KFData*> KFEntityEx::AddObjectElement( KFData* kfparent, KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        if ( !kfelement->IsObject() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", kfelement->_data_name );
            return std::make_tuple( KFDataDefine::Show_None, nullptr );
        }

        UpdateElementToData( reinterpret_cast< KFElementObject* >( kfelement ), kfparent, multiple );
        return std::make_tuple( KFDataDefine::Show_Element, kfparent );
    }

    std::tuple<uint32, KFData*> KFEntityEx::AddRecordElement( KFData* kfparent, KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        if ( !kfelement->IsObject() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", kfelement->_data_name );
            return std::make_tuple( KFDataDefine::Show_None, nullptr );
        }

        auto kfelementobject = reinterpret_cast< KFElementObject* >( kfelement );
        if ( kfelementobject->_config_id == _invalid_int )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] no id!", kfelement->_data_name );
            return std::make_tuple( KFDataDefine::Show_None, nullptr );
        }

        auto kfchild = kfparent->Find( kfelementobject->_config_id );
        if ( kfchild == nullptr )
        {
            // 不存在, 创建一个, 并更新属性
            kfchild = KFDataFactory::CreateData( kfparent->_data_setting );
            SetElementToData( kfelementobject, kfchild, multiple );
            AddData( kfparent, kfelementobject->_config_id, kfchild );
        }
        else
        {
            // 存在直接更新属性
            UpdateElementToData( kfelementobject, kfchild, multiple );
        }

        return std::make_tuple( KFDataDefine::Show_Element, kfchild );
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 判断元数据是否满足条件
    const std::string& KFEntityEx::CheckRemoveElement( const KFElements* kfelements, const char* function, uint32 line, float multiple /* = 1.0f */ )
    {
        for ( auto kfelement : kfelements->_element_list )
        {
            auto ok = CheckRemoveElement( kfelement, function, line, multiple );
            if ( !ok )
            {
                return kfelement->_data_name;
            }
        }

        return _invalid_string;
    }

    bool KFEntityEx::CheckRemoveElement( const KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        auto kfdata = Find( kfelement->_data_name );
        if ( kfdata == nullptr )
        {
            __LOG_ERROR_FUNCTION__( function, line, "can't find data=[{}]! ", kfelement->_data_name );
            return false;
        }

        // 如果有注册函数, 执行注册函数
        auto kffunction = _kf_component->_check_remove_element_function.Find( kfdata->_data_setting->_logic_name );
        if ( kffunction != nullptr )
        {
            return kffunction->_function( this, kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
        }

        // 找不到处理函数, 用基础函数来处理
        switch ( kfdata->_data_type )
        {
        case KFDataDefine::Type_Record:
            return CheckRecordElement( kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
            break;
        case KFDataDefine::Type_Object:
            return CheckObjectElement( kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
            break;
        default:
            return CheckNormalElement( kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
            break;
        }

        return false;
    }

    bool KFEntityEx::CheckNormalElement( KFData* kfdata, KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        if ( !kfelement->IsValue() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not value!", kfelement->_data_name );
            return false;
        }

        auto kfelementvalue = reinterpret_cast< KFElementValue* >( kfelement );
        if ( !kfelementvalue->_value->IsType( KFDataDefine::Type_UInt32 ) )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] is not int!", kfelement->_data_name );
            return false;
        }

        auto datavalue = kfdata->Get();
        auto elementvalue = kfelementvalue->_value->CalcUseValue( kfdata->_data_setting, multiple );
        return datavalue >= elementvalue;
    }

    bool KFEntityEx::CheckObjectElement( KFData* kfparent, KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        if ( !kfelement->IsObject() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", kfelement->_data_name );
            return false;
        }

        auto kfelementobject = reinterpret_cast< KFElementObject* >( kfelement );
        for ( auto& iter : kfelementobject->_values._objects )
        {
            auto& name = iter.first;
            auto kfvalue = iter.second;
            if ( !kfvalue->IsType( KFDataDefine::Type_UInt32 ) )
            {
                __LOG_ERROR_FUNCTION__( function, line, "element=[{}] is not int!", name );
                return false;
            }

            auto kfchild = kfparent->Find( name );
            if ( kfchild == nullptr )
            {
                return false;
            }

            auto datavalue = kfchild->Get() ;
            auto elementvalue = kfvalue->CalcUseValue( kfchild->_data_setting, multiple );
            if ( datavalue < elementvalue )
            {
                return false;
            }
        }

        return true;
    }

    bool KFEntityEx::CheckRecordElement( KFData* kfparent, KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        if ( !kfelement->IsObject() )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", kfelement->_data_name );
            return false;
        }

        auto kfelementobject = reinterpret_cast< KFElementObject* >( kfelement );
        if ( kfelementobject->_config_id == _invalid_int )
        {
            __LOG_ERROR_FUNCTION__( function, line, "element=[{}] no id!", kfelement->_data_name );
            return false;
        }

        auto kfdata = kfparent->Find( kfelementobject->_config_id );
        if ( kfdata == nullptr )
        {
            return false;
        }

        return CheckObjectElement( kfdata, kfelement, function, line, multiple );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
    void KFEntityEx::RemoveElement( const KFElements* kfelements, const char* function, uint32 line, float multiple /* = 1.0f */ )
    {
        if ( !kfelements->IsEmpty() )
        {
            __LOG_INFO_FUNCTION__( function, line, "{}={} remove elements=[{}]!", _kf_component->_component_name, GetKeyID(), kfelements->_str_element );
        }

        for ( auto kfelement : kfelements->_element_list )
        {
            RemoveElement( kfelement, function, line, multiple );
        }
    }

    // 删除元数据
    void KFEntityEx::RemoveElement( const KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        auto kfdata = Find( kfelement->_data_name );
        if ( kfdata == nullptr )
        {
            return __LOG_ERROR_FUNCTION__( function, line, "can't find data=[{}]! ", kfelement->_data_name );
        }

        // 如果有注册函数, 执行注册函数
        auto kffunction = _kf_component->_remove_element_function.Find( kfdata->_data_setting->_logic_name );
        if ( kffunction != nullptr )
        {
            return kffunction->_function( this, kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
        }

        // 找不到处理函数, 用基础函数来处理
        switch ( kfdata->_data_type )
        {
        case KFDataDefine::Type_Record:
            RemoveRecordElement( kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
            break;
        case KFDataDefine::Type_Object:
            RemoveObjectElement( kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
            break;
        default:
            RemoveNormalElement( kfdata, const_cast< KFElement* >( kfelement ), function, line, multiple );
            break;
        }
    }

    void KFEntityEx::RemoveNormalElement( KFData* kfdata, KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        if ( !kfelement->IsValue() )
        {
            return __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not value!", kfelement->_data_name );
        }

        auto kfelementvalue = reinterpret_cast< KFElementValue* >( kfelement );
        if ( !kfelementvalue->_value->IsType( KFDataDefine::Type_UInt32 ) )
        {
            return __LOG_ERROR_FUNCTION__( function, line, "element=[{}] is not int!", kfelement->_data_name );
        }

        auto value = kfelementvalue->_value->CalcUseValue( kfdata->_data_setting, multiple );
        UpdateData( kfdata, KFEnum::Dec, value );
    }

    void KFEntityEx::RemoveObjectElement( KFData* kfparent, KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        if ( !kfelement->IsObject() )
        {
            return __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", kfelement->_data_name );
        }

        auto kfelementobject = reinterpret_cast< KFElementObject* >( kfelement );
        for ( auto& iter : kfelementobject->_values._objects )
        {
            auto& name = iter.first;
            auto kfvalue = iter.second;
            if ( !kfvalue->IsType( KFDataDefine::Type_UInt32 ) )
            {
                __LOG_ERROR_FUNCTION__( function, line, "element=[{}] is not int!", name );
                continue;
            }

            UpdateData( kfparent, name, KFEnum::Dec, kfvalue->GetUseValue() );
        }
    }

    void KFEntityEx::RemoveRecordElement( KFData* kfparent, KFElement* kfelement, const char* function, uint32 line, float multiple )
    {
        if ( !kfelement->IsObject() )
        {
            return __LOG_ERROR_FUNCTION__( function, line, "element=[{}] not object!", kfelement->_data_name );
        }

        auto kfelementobject = reinterpret_cast< KFElementObject* >( kfelement );
        if ( kfelementobject->_config_id == _invalid_int )
        {
            return __LOG_ERROR_FUNCTION__( function, line, "element=[{}] no id!", kfelement->_data_name );
        }

        auto kfdata = kfparent->Find( kfelementobject->_config_id );
        if ( kfdata == nullptr )
        {
            return __LOG_ERROR_FUNCTION__( function, line, "element=[{}] can't find id=[{}]!", kfelementobject->_data_name, kfelementobject->_config_id );
        }

        for ( auto& iter : kfelementobject->_values._objects )
        {
            auto& name = iter.first;
            auto kfvalue = iter.second;
            if ( !kfvalue->IsType( KFDataDefine::Type_UInt32 ) )
            {
                __LOG_ERROR_FUNCTION__( function, line, "element=[{}] is not int!", name );
                continue;
            }

            UpdateData( kfdata, name, KFEnum::Dec, kfvalue->GetUseValue() );
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
#define __PREPARE_SYNC__( function )\
    if ( function == nullptr ||\
            !IsInited() || !kfdata->IsNeedSyncToClient() )\
    {\
        return;\
    }\
    std::list< KFData* > datahierarchy;\
    datahierarchy.push_front( kfdata );\
    auto kfparent = kfdata->GetParent();\
    while ( kfparent != nullptr )\
    {\
        if ( !kfparent->IsNeedSyncToClient() )\
        {\
            return;\
        }\
        datahierarchy.push_front( kfparent );\
        kfparent = kfparent->GetParent();\
    }\
    datahierarchy.pop_front();\
    if ( datahierarchy.empty() )\
    {\
        return;\
    }\

#define __FIND_PROTO_OBJECT__\
    auto savedata = datahierarchy.front();\
    datahierarchy.pop_front();\
    if ( savedata->_data_type == KFDataDefine::Type_Object )\
    {\
        pbobject = &( ( *pbobject->mutable_pbobject() )[ savedata->_data_setting->_name ] );\
    }\
    else if ( savedata->_data_type == KFDataDefine::Type_Record )\
    {\
        auto pbrecord = &( ( *pbobject->mutable_pbrecord() )[ savedata->_data_setting->_name ] );\
        savedata = datahierarchy.front();\
        datahierarchy.pop_front(); \
        pbobject = &( ( *pbrecord->mutable_pbobject() )[ savedata->GetKeyID() ] ); \
    }\

    void KFEntityEx::SyncAddData( KFData* kfdata, uint64 key )
    {
        __PREPARE_SYNC__( _kf_component->_entity_sync_add_function );
        auto pbobject = &_add_pb_object;
        do
        {
            __FIND_PROTO_OBJECT__;
            if ( savedata == kfdata )
            {
                KFKernelModule::Instance()->SaveToObject( savedata, pbobject, KFDataDefine::Mask_Client );
            }
        } while ( !datahierarchy.empty() );

        // 设置有添加属性
        _have_add_pb_object = true;
        _kf_component->AddSyncEntity( this );
    }

    void KFEntityEx::SyncRemoveData( KFData* kfdata, uint64 key )
    {
        __PREPARE_SYNC__( _kf_component->_entity_sync_remove_function );
        auto pbobject = &_remove_pb_object;
        do
        {
            __FIND_PROTO_OBJECT__;
        } while ( !datahierarchy.empty() );

        _have_remove_pb_object = true;
        _kf_component->AddSyncEntity( this );
    }

    void KFEntityEx::SyncUpdateData( KFData* kfdata, uint64 key )
    {
        __PREPARE_SYNC__( _kf_component->_entity_sync_update_function );
        auto pbobject = &_update_pb_object;
        do
        {
            __FIND_PROTO_OBJECT__;
            if ( savedata->_data_type == KFDataDefine::Type_Array )
            {
                auto pbarray = &( ( *pbobject->mutable_pbarray() )[ savedata->_data_setting->_name ] );
                savedata = datahierarchy.front();
                datahierarchy.pop_front();

                ( *pbarray->mutable_pbuint64() )[ key ] = savedata->Get<int64>();
            }
            else
            {
                if ( savedata == kfdata )
                {
                    AddSyncUpdateDataToPBObject( savedata, pbobject );
                }
            }
        } while ( !datahierarchy.empty() );

        // 设置有添加属性
        _have_update_pb_object = true;
        _kf_component->AddSyncEntity( this );
    }

    void KFEntityEx::AddSyncUpdateDataToPBObject( KFData* kfdata, KFMsg::PBObject* pbobject )
    {
        auto datasetting = kfdata->_data_setting;
        switch ( kfdata->_data_type )
        {
        case KFDataDefine::Type_Int32:
            ( *pbobject->mutable_pbint32() )[ datasetting->_name ] = kfdata->Get< int32 >();
            break;
        case KFDataDefine::Type_UInt32:
            ( *pbobject->mutable_pbuint32() )[ datasetting->_name ] = kfdata->Get< uint32 >();
            break;
        case KFDataDefine::Type_Int64:
            ( *pbobject->mutable_pbint64() )[ datasetting->_name ] = kfdata->Get< int64 >();
            break;
        case KFDataDefine::Type_UInt64:
            ( *pbobject->mutable_pbuint64() )[ datasetting->_name ] = kfdata->Get< uint64 >();
            break;
        case KFDataDefine::Type_Double:
            ( *pbobject->mutable_pbdouble() )[ datasetting->_name ] = kfdata->Get< double >();
            break;
        case KFDataDefine::Type_String:
            ( *pbobject->mutable_pbstring() )[ datasetting->_name ] = kfdata->Get< std::string >();
            break;
        case KFDataDefine::Type_Object:
            KFKernelModule::Instance()->SaveToObject( kfdata, pbobject, KFDataDefine::Mask_Client );
            break;
        }
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
    void KFEntityEx::SyncEntityToClient()
    {
        // 同步删除
        SyncRemoveDataToClient();

        // 同步添加
        SyncAddDataToClient();

        // 同步更新
        SyncUpdateDataToClient();

        // 同步显示奖励
        SendShowElementToClient();
    }

    void KFEntityEx::SyncAddDataToClient()
    {
        if ( !_have_add_pb_object )
        {
            return;
        }

        _have_add_pb_object = false;
        _kf_component->_entity_sync_add_function( this, _add_pb_object );
        _add_pb_object.Clear();
    }

    void KFEntityEx::SyncUpdateDataToClient()
    {
        if ( !_have_update_pb_object )
        {
            return;
        }

        _have_update_pb_object = false;
        _kf_component->_entity_sync_update_function( this, _update_pb_object );
        _update_pb_object.Clear();
    }

    void KFEntityEx::SyncRemoveDataToClient()
    {
        if ( !_have_remove_pb_object )
        {
            return;
        }

        _have_remove_pb_object = false;
        _kf_component->_entity_sync_remove_function( this, _remove_pb_object );
        _remove_pb_object.Clear();
    }

    void KFEntityEx::SendShowElementToClient()
    {
        if ( !_have_show_client )
        {
            return;
        }

        _have_show_client = false;
        _kf_component->_show_element_function( this, _pb_show_element );
        _pb_show_element.Clear();
    }
    /////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////
    uint64 KFEntityEx::GetConfigValue( const std::string& name, uint64 id, uint64 maxvalue )
    {
        auto kffunction = _kf_component->_get_config_value_function.Find( name );
        if ( kffunction != nullptr )
        {
            return kffunction->_function( this, id, maxvalue );
        }

        auto kfobject = Find( name, id );
        if ( kfobject == nullptr )
        {
            return 0u;
        }

        return kfobject->Get<uint64>( kfobject->_data_setting->_value_key_name );
    }

    uint32 KFEntityEx::GetStatus()
    {
        return Get<uint32>( __STRING__( basic ), __STRING__( status ) );
    }

    void KFEntityEx::SetStatus( uint32 status )
    {
        UpdateData( __STRING__( basic ), __STRING__( status ), KFEnum::Set, status );
    }
}