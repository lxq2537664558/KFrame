﻿#ifndef __KF_MONGO_READ_EXECUTE_H__
#define __KF_MONGO_READ_EXECUTE_H__

#include "KFMongoExecute.hpp"

namespace KFrame
{
    class KFMongoReadExecute : public KFMongoExecute
    {
    public:
        KFMongoReadExecute() = default;
        virtual ~KFMongoReadExecute() = default;

        // 查询数量
        KFResult< uint64 >::UniqueType Count( const std::string& table );
        KFResult< uint64 >::UniqueType Count( const std::string& table, const std::string& field, uint64 key );
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 查询数值
        template< typename ReturnType, typename KeyType, typename ValueType >
        typename KFResult<ReturnType>::UniqueType QueryValue( const std::string& table, const KeyType& key, const std::string& field )
        {
            auto fullname = __FORMAT__( "{}.{}", _database, table );
            QueryRequest request( fullname, QueryRequest::QUERY_DEFAULT );

            // 查询条件
            request.selector().add( MongoKeyword::_id, key );

            // 查询字段
            request.returnFieldSelector().add( field, 1 );

            // 数量
            request.setNumberToReturn( 1 );

            typename __NEW_RESULT__( ReturnType );
            ResponseMessage response;
            auto ok = SendRequest( request, response );
            if ( ok )
            {
                if ( response.documents().size() > 0 )
                {
                    Poco::MongoDB::Document::Ptr doc = response.documents()[ 0 ];
                    try
                    {
                        kfresult->_value = doc->get<ValueType>( field );
                    }
                    catch ( Poco::Exception& )
                    {
                        __LOG_DEBUG__( "table=[{}] key=[{}] field=[{}] not exist", table, key, field );
                    }
                }
            }
            else
            {
                kfresult->SetResult( KFEnum::Error );
            }

            return kfresult;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 查询数值列表
        template< class ReturnType, class KeyType, class ValueType >
        typename KFResult< ReturnType >::UniqueType QueryList( const std::string& table, const KeyType& key, const std::string& field )
        {
            auto fullname = __FORMAT__( "{}.{}", _database, table );
            QueryRequest request( fullname, QueryRequest::QUERY_DEFAULT );

            // 查询条件
            request.selector().add( MongoKeyword::_id, key );

            // 查询字段
            request.returnFieldSelector().add( field, 1 );

            typename __NEW_RESULT__( ReturnType );
            ResponseMessage response;
            auto ok = SendRequest( request, response );
            if ( ok )
            {
                if ( response.documents().size() > 0 )
                {
                    Poco::MongoDB::Document::Ptr doc = response.documents()[ 0 ];
                    try
                    {
                        auto elements = doc->get< Array::Ptr >( field )->getSet();
                        for ( auto iter = elements->begin(); iter != elements->end(); ++iter )
                        {
                            auto concrete = dynamic_cast< const ConcreteElement<ValueType>* >( ( *iter ).get() );
                            kfresult->_value.push_back( concrete->value() );
                        }
                    }
                    catch ( Poco::Exception& )
                    {
                        __LOG_DEBUG__( "table=[{}] key=[{}] field=[{}] not exist", table, key, field );
                    }
                }
            }
            else
            {
                kfresult->SetResult( KFEnum::Error );
            }

            return kfresult;
        }
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // 查询集合
        template< class KeyType >
        typename KFResult< KFDBValue >::UniqueType QueryRecord( const std::string& table, const KeyType& key, const StringList& fields )
        {
            auto fullname = __FORMAT__( "{}.{}", _database, table );
            QueryRequest request( fullname, QueryRequest::QUERY_DEFAULT );

            // 查询条件
            request.selector().add( MongoKeyword::_id, key );

            if ( !fields.empty() )
            {
                auto& returnfields = request.returnFieldSelector();
                for ( auto& field : fields )
                {
                    returnfields.add( field, 1 );
                }
            }

            __NEW_RESULT__( KFDBValue );
            ResponseMessage response;
            auto ok = SendRequest( request, response );
            if ( ok )
            {
                if ( response.documents().size() > 0 )
                {
                    Poco::MongoDB::Document::Ptr doc = response.documents()[ 0 ];
                    try
                    {
                        auto elements = doc->getSet();
                        for ( auto iter = elements->begin(); iter != elements->end(); ++iter )
                        {
                            auto& name = ( *iter )->name();
                            if ( name == MongoKeyword::_expire )
                            {
                                continue;
                            }

                            auto type = ( *iter )->type();
                            if ( type == ElementTraits<Poco::Int64>::TypeId )
                            {
                                auto concrete = dynamic_cast< const ConcreteElement<Poco::Int64>* >( ( *iter ).get() );
                                if ( concrete != nullptr )
                                {
                                    kfresult->_value.AddValue( name, concrete->value() );
                                }
                            }
                            else if ( type == ElementTraits<std::string>::TypeId )
                            {
                                auto concrete = dynamic_cast< const ConcreteElement<std::string>* >( ( *iter ).get() );
                                if ( concrete != nullptr )
                                {
                                    kfresult->_value.AddValue( name, concrete->value() );
                                }
                            }
                        }
                    }
                    catch ( Poco::Exception& )
                    {
                    }
                }
            }
            else
            {
                kfresult->SetResult( KFEnum::Error );
            }

            return kfresult;
        }

        // 查询结合
        KFResult< std::list< KFDBValue > >::UniqueType QueryListRecord( const std::string& table, const KFMongoSelector& kfseletor );
    };
}

#endif
