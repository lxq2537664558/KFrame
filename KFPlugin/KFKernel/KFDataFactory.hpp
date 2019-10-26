﻿#ifndef __KF_DATA_FACTORY_H__
#define __KF_DATA_FACTORY_H__

#include "KFCore/KFData.h"

namespace KFrame
{
    class KFDataFactory
    {
    public:
        // 创建
        static KFData* Create( uint32 type );
        static KFData* Create( const std::string& type );

        // 释放资源
        static void Release( KFData* kfdata );

        // 创建一个属性
        static KFData* CreateData( const KFDataSetting* datasetting );
        static KFData* CreateData( const std::string& classname, const std::string& dataname );

        // 初始化对象
        static void InitData( KFData* kfdata, const KFClassSetting* classsetting, const KFDataSetting* datasetting );

        // 初始化数组
        static void InitArray( KFData* kfarray, uint32 size );

        // 添加数组元素
        static KFData* AddArray( KFData* kfarray );

    };
}

#endif