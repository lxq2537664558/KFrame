﻿#include "KFMongoLogic.hpp"
#include "KFMongoModule.hpp"

namespace KFrame
{
    ////////////////////////////////////////////////////////////////////////////////////////
    KFMongoLogic::KFMongoLogic()
    {
        _read_execute = __KF_NEW__( KFMongoReadExecute );
        _write_execute = __KF_NEW__( KFMongoWriteExecute );
    }

    KFMongoLogic::~KFMongoLogic()
    {
        __KF_DELETE__( KFMongoReadExecute, _read_execute );
        __KF_DELETE__( KFMongoWriteExecute, _write_execute );
    }

    void KFMongoLogic::ShutDown()
    {
        _read_execute->ShutDown();
        _write_execute->ShutDown();
    }

    void KFMongoLogic::Initialize( KFMongoType* kfmongotype )
    {
        {
            auto kfmongolist = kfmongotype->FindMongoList( KFDatabaseEnum::Read );
            if ( kfmongolist != nullptr )
            {
                auto kfsetting = kfmongolist->FindSetting();
                if ( kfsetting != nullptr )
                {
                    _read_execute->InitMongo( kfsetting );
                }
            }
        }

        {
            auto kfmongolist = kfmongotype->FindMongoList( KFDatabaseEnum::Write );
            if ( kfmongolist != nullptr )
            {
                auto kfsetting = kfmongolist->FindSetting();
                if ( kfsetting != nullptr )
                {
                    _write_execute->InitMongo( kfsetting );
                }
            }
        }
    }

    //////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////
    bool KFMongoLogic::CreateIndex( const std::string& table, const std::string& indexname, bool unique, uint32 ttl )
    {
        MongoIndexType values;
        values[ indexname ] = MongoKeyword::_asc;
        return CreateIndex( table, indexname, values, unique, ttl );
    }

    bool KFMongoLogic::CreateIndex( const std::string& table, const std::string& indexname, const MongoIndexType& values, bool unique /* = false */, uint32 ttl /* = 0u */ )
    {
        // 如果是过期时间
        if ( indexname == MongoKeyword::_expire && ttl == 0u )
        {
            ttl = 1u;
        }

        auto ok1 = _write_execute->CreateIndex( table, indexname, values, unique, ttl );
        auto ok2 = _read_execute->CreateIndex( table, indexname, values, unique, ttl );
        return ok1 & ok2;
    }
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFMongoLogic::Expire( const std::string& table, uint64 key, uint64 validtime )
    {
        auto expiretime = KFGlobal::Instance()->_real_time + validtime;
        return _write_execute->ExpireAt( table, key, expiretime );
    }

    bool KFMongoLogic::Expire( const std::string& table, const std::string& key, uint64 validtime )
    {
        auto expiretime = KFGlobal::Instance()->_real_time + validtime;
        return _write_execute->ExpireAt( table, key, expiretime );
    }

    // 具体时间点
    bool KFMongoLogic::ExpireAt( const std::string& table, uint64 key, uint64 expiretime )
    {
        return _write_execute->ExpireAt( table, key, expiretime );
    }

    bool KFMongoLogic::ExpireAt( const std::string& table, const std::string& key, uint64 expiretime )
    {
        return _write_execute->ExpireAt( table, key, expiretime );
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    KFResult< uint64 >::UniqueType KFMongoLogic::Count( const std::string& table )
    {
        return _read_execute->Count( table );
    }

    KFResult< uint64 >::UniqueType KFMongoLogic::Count( const std::string& table, const std::string& field, uint64 key )
    {
        return _read_execute->Count( table, field, key );
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFMongoLogic::Insert( const std::string& table, const KFDBValue& dbvalue )
    {
        auto uuid = static_cast< KFMongoModule* >( _kf_mongo )->MakeUUID();
        const_cast< KFDBValue& >( dbvalue ).AddValue( MongoKeyword::_id, uuid );
        return _write_execute->Insert( table, dbvalue );
    }
    ////////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFMongoLogic::Insert( const std::string& table, uint64 key, const KFDBValue& dbvalue )
    {
        return _write_execute->Update( table, key, dbvalue );
    }

    bool KFMongoLogic::Insert( const std::string& table, const std::string& key, const KFDBValue& dbvalue )
    {
        return _write_execute->Update( table, key, dbvalue );
    }

    bool KFMongoLogic::Insert( const std::string& table, const KFDBValue& dbvalue, const KFMongoSelector& kfseletor )
    {
        return _write_execute->Update( table, dbvalue, kfseletor );
    }

    bool KFMongoLogic::Insert( const std::string& table, const std::string& field, uint64 value, const KFMongoSelector& kfseletor )
    {
        KFDBValue dbvalue;
        dbvalue.AddValue( field, value );
        return _write_execute->Update( table, dbvalue, kfseletor );
    }

    bool KFMongoLogic::Insert( const std::string& table, const std::string& field, const std::string& value, const KFMongoSelector& kfseletor )
    {
        KFDBValue dbvalue;
        dbvalue.AddValue( field, value );
        return _write_execute->Update( table, dbvalue, kfseletor );
    }

    bool KFMongoLogic::Insert( const std::string& table, uint64 key, const std::string& field, uint64 value )
    {
        return _write_execute->Update( table, MongoKeyword::_id, key, field, value );
    }

    bool KFMongoLogic::Insert( const std::string& table, uint64 key, const std::string& field, const std::string& value )
    {
        return _write_execute->Update( table, MongoKeyword::_id, key, field, value );
    }

    bool KFMongoLogic::Insert( const std::string& table, const std::string& key, const std::string& field, uint64 value )
    {
        return _write_execute->Update( table, MongoKeyword::_id, key, field, value );
    }

    bool KFMongoLogic::Insert( const std::string& table, const std::string& key, const std::string& field, const std::string& value )
    {
        return _write_execute->Update( table, MongoKeyword::_id, key, field, value );
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFMongoLogic::Delete( const std::string& table )
    {
        return _write_execute->Delete( table );
    }

    bool KFMongoLogic::Delete( const std::string& table, uint64 key )
    {
        return _write_execute->Delete( table, MongoKeyword::_id, key );
    }

    bool KFMongoLogic::Delete( const std::string& table, const std::string& key )
    {
        return _write_execute->Delete( table, MongoKeyword::_id, key );
    }

    bool KFMongoLogic::Delete( const std::string& table, const std::string& keyname, uint64 keyvalue )
    {
        return _write_execute->Delete( table, keyname, keyvalue );
    }

    bool KFMongoLogic::Delete( const std::string& table, const std::string& keyname, const std::string& keyvalue )
    {
        return _write_execute->Delete( table, keyname, keyvalue );
    }

    bool KFMongoLogic::Delete( const std::string& table, const KFMongoSelector& kfseletor )
    {
        return _write_execute->Delete( table, kfseletor );
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFMongoLogic::Push( const std::string& table, uint64 key, const std::string& field, uint64 value )
    {
        UInt64List values;
        values.push_back( value );
        return _write_execute->Push( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Push( const std::string& table, uint64 key, const std::string& field, const std::string& value )
    {
        StringList values;
        values.push_back( value );
        return _write_execute->Push( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Push( const std::string& table, const std::string& key, const std::string& field, uint64 value )
    {
        UInt64List values;
        values.push_back( value );
        return _write_execute->Push( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Push( const std::string& table, const std::string& key, const std::string& field, const std::string& value )
    {
        StringList values;
        values.push_back( value );
        return _write_execute->Push( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Push( const std::string& table, uint64 key, const std::string& field, const UInt64List& values )
    {
        return _write_execute->Push( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Push( const std::string& table, const std::string& key, const std::string& field, const UInt64List& values )
    {
        return _write_execute->Push( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Push( const std::string& table, uint64 key, const std::string& field, const StringList& values )
    {
        return _write_execute->Push( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Push( const std::string& table, const std::string& key, const std::string& field, const StringList& values )
    {
        return _write_execute->Push( table, MongoKeyword::_id, key, field, values );
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    bool KFMongoLogic::Pull( const std::string& table, uint64 key, const std::string& field, uint64 value )
    {
        UInt64List values;
        values.push_back( value );
        return _write_execute->Pull( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Pull( const std::string& table, uint64 key, const std::string& field, const std::string& value )
    {
        StringList values;
        values.push_back( value );
        return _write_execute->Pull( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Pull( const std::string& table, const std::string& key, const std::string& field, uint64 value )
    {
        UInt64List values;
        values.push_back( value );
        return _write_execute->Pull( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Pull( const std::string& table, const std::string& key, const std::string& field, const std::string& value )
    {
        StringList values;
        values.push_back( value );
        return _write_execute->Pull( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Pull( const std::string& table, uint64 key, const std::string& field, UInt64List& values )
    {
        return _write_execute->Pull( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Pull( const std::string& table, const std::string& key, const std::string& field, UInt64List& values )
    {
        return _write_execute->Pull( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Pull( const std::string& table, uint64 key, const std::string& field, StringList& values )
    {
        return _write_execute->Pull( table, MongoKeyword::_id, key, field, values );
    }

    bool KFMongoLogic::Pull( const std::string& table, const std::string& key, const std::string& field, StringList& values )
    {
        return _write_execute->Pull( table, MongoKeyword::_id, key, field, values );
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////////
    KFResult< uint64 >::UniqueType KFMongoLogic::QueryUInt64( const std::string& table, uint64 key, const std::string& field )
    {
        return _read_execute->QueryValue< uint64, Poco::UInt64, Poco::UInt64>( table, key, field );
    }

    KFResult< uint64 >::UniqueType KFMongoLogic::QueryUInt64( const std::string& table, const std::string& key, const std::string& field )
    {
        return _read_execute->QueryValue<uint64, std::string, Poco::UInt64>( table, key, field );
    }

    KFResult< std::string >::UniqueType KFMongoLogic::QueryString( const std::string& table, uint64 key, const std::string& field )
    {
        return _read_execute->QueryValue<std::string, Poco::UInt64, std::string>( table, key, field );
    }

    KFResult< std::string >::UniqueType KFMongoLogic::QueryString( const std::string& table, const std::string& key, const std::string& field )
    {
        return _read_execute->QueryValue<std::string, std::string, std::string>( table, key, field );
    }

    KFResult< UInt64List >::UniqueType KFMongoLogic::QueryListUInt64( const std::string& table, uint64 key, const std::string& field )
    {
        return _read_execute->QueryList<UInt64List, Poco::UInt64, Poco::UInt64>( table, key, field );
    }

    KFResult< UInt64List >::UniqueType KFMongoLogic::QueryListUInt64( const std::string& table, const std::string& key, const std::string& field )
    {
        return _read_execute->QueryList<UInt64List, std::string, Poco::UInt64>( table, key, field );
    }

    KFResult< StringList >::UniqueType KFMongoLogic::QueryListString( const std::string& table, uint64 key, const std::string& field )
    {
        return _read_execute->QueryList<StringList, Poco::UInt64, std::string>( table, key, field );
    }

    KFResult< StringList >::UniqueType KFMongoLogic::QueryListString( const std::string& table, const std::string& key, const std::string& field )
    {
        return _read_execute->QueryList<StringList, std::string, std::string>( table, key, field );
    }

    KFResult< KFDBValue >::UniqueType KFMongoLogic::QueryRecord( const std::string& table, uint64 key )
    {
        static StringList _fields;
        return _read_execute->QueryRecord( table, key, _fields );
    }

    KFResult< KFDBValue >::UniqueType KFMongoLogic::QueryRecord( const std::string& table, const std::string& key )
    {
        static StringList _fields;
        return _read_execute->QueryRecord( table, key, _fields );
    }

    KFResult< KFDBValue >::UniqueType KFMongoLogic::QueryRecord( const std::string& table, uint64 key, const StringList& fields )
    {
        return _read_execute->QueryRecord( table, key, fields );
    }

    KFResult< KFDBValue >::UniqueType KFMongoLogic::QueryRecord( const std::string& table, const std::string& key, const StringList& fields )
    {
        return _read_execute->QueryRecord( table, key, fields );
    }
    //////////////////////////////////////////////////////////////////////////////////////////////////
    KFResult< std::list< KFDBValue > >::UniqueType KFMongoLogic::QueryListRecord( const std::string& table, const KFMongoSelector& kfseletor )
    {
        return _read_execute->QueryListRecord( table, kfseletor );
    }
}