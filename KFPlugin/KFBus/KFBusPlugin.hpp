﻿#ifndef __KF_BUS_PLUGIN_H__
#define __KF_BUS_PLUGIN_H__
#include "KFrame.h"

namespace KFrame
{
    class KFBusPlugin : public KFPlugin
    {
    public:
        // 注册
        virtual void Install();

        // 卸载
        virtual void UnInstall();

        // 加载
        virtual void LoadModule();

        // 配置
        virtual void AddConfig();
    };
}


#endif