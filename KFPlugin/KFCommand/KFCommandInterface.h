﻿#ifndef __KF_COMMAND_INTERFACE_H__
#define __KF_COMMAND_INTERFACE_H__

#include "KFrame.h"

namespace KFrame
{
    typedef std::function< void( KFEntity*, const StringVector& ) > KFCommandFunction;

    class KFCommandInterface : public KFModule
    {
    public:
        // 注册调试函数
        template< class T >
        void RegisterFunction( const std::string& command, T* object, void ( T::*handle )( KFEntity*, const StringVector& ) )
        {
            KFCommandFunction function = std::bind( handle, object, std::placeholders::_1, std::placeholders::_2 );
            BindFunction( command, function );
        }

        // 卸载调试函数
        virtual void UnRegisterFunction( const std::string& command ) = 0;

    protected:
        // 绑定调试函数
        virtual void BindFunction( const std::string& command, KFCommandFunction& function ) = 0;
    };

    /////////////////////////////////////////////////////////////////////////////////////////////////
    __KF_INTERFACE__( _kf_command, KFCommandInterface );
    /////////////////////////////////////////////////////////////////////////////////////////////////

#define __KF_COMMAND_FUNCTION__( function ) \
    void function( KFEntity* player, const StringVector& params )

#define  __REGISTER_COMMAND_FUNCTION__( command, function ) \
    _kf_command->RegisterFunction( command, this, function )

#define  __UN_COMMAND_FUNCTION__( command ) \
    _kf_command->UnRegisterFunction( command )
}



#endif