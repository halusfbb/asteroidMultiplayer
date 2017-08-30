/*
 * SocketAddress.cpp
 *
 *  Created on: 30 Aug 2017
 *      Author: faizh
 */

#include "SocketAddress.h"
#include <string.h>

SocketAddress::SocketAddress( uint32_t inAddress, uint16_t inPort )
{
	GetAsSockAddrIn()->sin_family = AF_INET;
	GetIP4Ref() = htonl( inAddress );
	GetAsSockAddrIn()->sin_port = htons( inPort );
}

SocketAddress::SocketAddress( const sockaddr& inSockAddr )
{
	memcpy( &mSockAddr, &inSockAddr, sizeof( sockaddr ) );
}

SocketAddress::SocketAddress()
{
	GetAsSockAddrIn()->sin_family = AF_INET;
	GetIP4Ref() = INADDR_ANY;
	GetAsSockAddrIn()->sin_port = 0;
}

bool SocketAddress::operator==( const SocketAddress& inOther ) const
{
	return ( mSockAddr.sa_family == AF_INET &&
			 GetAsSockAddrIn()->sin_port == inOther.GetAsSockAddrIn()->sin_port ) &&
			 ( GetIP4Ref() == inOther.GetIP4Ref() );
}

uint32_t SocketAddress::GetSize() const
{
	return sizeof( sockaddr );
}
