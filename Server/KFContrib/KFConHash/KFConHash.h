﻿#ifndef __KF_CONHASH_H__
#define __KF_CONHASH_H__

#include "KFInclude.h"
namespace KFrame
{
    class KFHashLogic;
    /////////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////////
    // 一致性hash算法
    class KFConHash
    {
    public:
        KFConHash();
        ~KFConHash();

        // 添加Hash节点
        void AddHashNode( const std::string& name, uint32 id, uint32 virtualcount );

        // 删除Hash节点
        bool RemoveHashNode( uint32 id );

        // 查抄Hash节点
        uint32 FindHashNode( uint64 objectid, bool cache = false );
        uint32 FindHashNode( const std::string& data, bool cache = false );
        uint32 FindHashNode( const std::string& data, uint64 objectid, bool cache = false );

        // 获得所有节点
        void GetAllHashNode( std::list< uint32 >& nodes );

        // 是否存在节点
        bool HaveHashNode( uint32 id );

        // 节点数量
        uint32 GetHashNodeCount();
    private:
        // Hash 逻辑
        KFHashLogic* _hash_logic;
    };
}

#endif
