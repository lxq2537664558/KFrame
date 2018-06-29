﻿#ifndef __KF_DOCUMENT_H__
#define __KF_DOCUMENT_H__

#include "KFNode.h"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
    class KFXml
    {
    public:
        KFXml( const char* file );
        ~KFXml();

        // 查找节点
        KFNode RootNode();
        KFNode FindNode( const char* key );

        const char* GetFileName() const;

    protected:
        // 解析文件
        void Parse( const char* file );

    private:
        void* _document;
        void* _data;
        std::string _file;
    };
}

#endif
