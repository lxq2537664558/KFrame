﻿#include "KFHttpData.h"
#include "KFHttpClient.h"
#include "KFHttpsClient.h"

namespace KFrame
{
    KFHttpData::KFHttpData()
    {
        _type = 0;
        _http = nullptr;
        _function = nullptr;
    }

    KFHttpData::~KFHttpData()
    {
        __KF_DELETE__( KFHttp, _http );
    }

    void KFHttpData::Request()
    {
        _result = _http->RunHttp( _type, _url, _data );
    }

    void KFHttpData::Response()
    {
        if ( _function != nullptr )
        {
            try
            {
                _function( _data, _result, _args );
            }
            catch ( ... )
            {
                __LOG_ERROR__( "http response exception! result=[{}]", _result );
            }
        }
    }
}