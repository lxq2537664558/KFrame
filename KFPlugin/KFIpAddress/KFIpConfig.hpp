﻿#ifndef __KF_IP_ADDRESS_CONFIG_H__
#define __KF_IP_ADDRESS_CONFIG_H__

#include "KFZConfig/KFConfig.h"

namespace KFrame
{
    /////////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////////
    class KFIpConfig : public KFConfig, public KFInstance< KFIpConfig >
    {
    public:
        KFIpConfig()
        {
            _file_name = "ip";
        }

        bool LoadConfig( const std::string& filename, const std::string& filepath, uint32 loadmask );

        // 查找连接
        const KFIpAddress* FindIpAddress( const std::string& appname, const std::string& apptype, const std::string& appid );
        void FindIpAddress( const std::string& appname, const std::string& apptype, const std::string& appid, IpAddressList& outlist );

        // 查找vpn ip
        const std::string& FindVPNIpAddress( const std::string& appname, const std::string& apptype, uint32 zoneid );
    public:
        // 配置的连接地址
        std::unordered_map< uint64, KFIpAddress > _ip_address_list;

        // 认证地址
        std::string _auth_url;

        // log地址
        std::string _log_url;

        // vpn 地址
        std::unordered_map< uint32, std::string > _vpn_list;
    };
}

#endif