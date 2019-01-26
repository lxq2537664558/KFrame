﻿#ifndef __KF_FIELD_H__
#define __KF_FIELD_H__

namespace KFrame
{
#define __STRING_DEFINE__( name )  static std::string _##name = #name;
#define __KF_STRING__( name )  KFField::_##name

    namespace KFField
    {
        // frame
        __STRING_DEFINE__( id );
        __STRING_DEFINE__( master );
        __STRING_DEFINE__( proxy );
        __STRING_DEFINE__( shard );
        __STRING_DEFINE__( route );
        __STRING_DEFINE__( ip );
        __STRING_DEFINE__( port );
        __STRING_DEFINE__( daemon );
        __STRING_DEFINE__( appname );
        __STRING_DEFINE__( apptype );
        __STRING_DEFINE__( appid );
        __STRING_DEFINE__( service );
        __STRING_DEFINE__( log );
        __STRING_DEFINE__( address );

        // midware
        __STRING_DEFINE__( zoneregister );
        __STRING_DEFINE__( zoneupdate );
        __STRING_DEFINE__( zonelist );
        __STRING_DEFINE__( zoneip );
        __STRING_DEFINE__( zone );
        __STRING_DEFINE__( zoneurl );
        __STRING_DEFINE__( zoneid );
        __STRING_DEFINE__( zonelogicid );
        __STRING_DEFINE__( auth );
        __STRING_DEFINE__( verify );
        __STRING_DEFINE__( activation );
        __STRING_DEFINE__( onlinedata );
        __STRING_DEFINE__( ban );
        __STRING_DEFINE__( banip );
        __STRING_DEFINE__( banplayerid );
        __STRING_DEFINE__( banaccountid );
        __STRING_DEFINE__( bantime );
        __STRING_DEFINE__( unban );
        __STRING_DEFINE__( queryban );
        __STRING_DEFINE__( queryaccount );
        __STRING_DEFINE__( extend );
        __STRING_DEFINE__( account );
        __STRING_DEFINE__( accountid );
        __STRING_DEFINE__( player );
        __STRING_DEFINE__( playerid );
        __STRING_DEFINE__( name );
        __STRING_DEFINE__( user );
        __STRING_DEFINE__( playeridcreate );
        __STRING_DEFINE__( url );
        __STRING_DEFINE__( tokenexpiretime );
        __STRING_DEFINE__( token );
        __STRING_DEFINE__( openid );
        __STRING_DEFINE__( channel );
        __STRING_DEFINE__( channeldata );
        __STRING_DEFINE__( count );
        __STRING_DEFINE__( code );
        __STRING_DEFINE__( verifyactivationcode );
        __STRING_DEFINE__( public );
        __STRING_DEFINE__( login );
        __STRING_DEFINE__( openactivation );
        __STRING_DEFINE__( activationcode );
        __STRING_DEFINE__( online );
        __STRING_DEFINE__( kickonline );
        __STRING_DEFINE__( accountlist );
        __STRING_DEFINE__( accountmake );


    }
}

#endif
