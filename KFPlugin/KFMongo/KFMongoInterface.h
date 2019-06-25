﻿#ifndef __KF_MONGO_INTERFACE_H__
#define __KF_MONGO_INTERFACE_H__

#include "KFrame.h"

namespace KFrame
{
    class KFMongoDriver
    {
    public:

    };

    /////////////////////////////////////////////////////////////////////////////////////////
    class KFMongoInterface : public KFModule
    {
    public:
        // 创建Execute
        virtual KFMongoDriver* Create( const std::string& module, uint32 logicid = 0 ) = 0;

    };

    ///////////////////////////////////////////////////////////////////////////////////////////////
    __KF_INTERFACE__( _kf_mongo, KFMongoInterface );
    ///////////////////////////////////////////////////////////////////////////////////////////////
}

#endif