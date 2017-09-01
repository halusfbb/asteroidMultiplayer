/*
 * SocketAddress.cpp
 *
 *  Created on: 30 Aug 2017
 *      Author: faizh
 */

#include "SocketAddress.h"
#include <arpa/inet.h>
#include "StringUtil.h"

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

string SocketAddress::ToString() const
{
	const sockaddr_in* s = GetAsSockAddrIn();
	char destinationBuffer[ 128 ];
#ifdef _WIN32
	InetNtop( s->sin_family, const_cast< in_addr* >( &s->sin_addr ), destinationBuffer, sizeof( destinationBuffer ) );
#else
	char* destinationBufferChar = inet_ntoa( s->sin_addr );
	memcpy(destinationBuffer, destinationBufferChar, 128);
#endif
	return StringUtils::Sprintf( "%s:%d",
								destinationBuffer,
								ntohs( s->sin_port ) );
}
