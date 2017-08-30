/*
 * SocketAddress.h
 *
 *  Created on: 30 Aug 2017
 *      Author: faizh
 */

#ifndef NETWORK_SOCKETADDRESS_H_
#define NETWORK_SOCKETADDRESS_H_

#include <sys/socket.h>
#include <netinet/in.h>
#include <memory>

//this class wraps the basic socket data types (e.g. sockaddr, sockaddr_in, sin_addr)
//and provides custom object oriented functions for type-safety.
class SocketAddress
{
public:
	SocketAddress( uint32_t inAddress, uint16_t inPort );
	SocketAddress( const sockaddr& inSockAddr );
	SocketAddress();

	bool operator==( const SocketAddress& inOther ) const;

	uint32_t GetSize() const;

private:
//	friend class UDPSocket;
//	friend class TCPSocket;

	sockaddr mSockAddr;
#if _WIN32
	uint32_t&				GetIP4Ref()					{ return *reinterpret_cast< uint32_t* >( &GetAsSockAddrIn()->sin_addr.S_un.S_addr ); }
	const uint32_t&			GetIP4Ref()			const	{ return *reinterpret_cast< const uint32_t* >( &GetAsSockAddrIn()->sin_addr.S_un.S_addr ); }
#else
	uint32_t&				GetIP4Ref()					{ return GetAsSockAddrIn()->sin_addr.s_addr; }
	const uint32_t&			GetIP4Ref()			const	{ return GetAsSockAddrIn()->sin_addr.s_addr; }
#endif

	sockaddr_in*			GetAsSockAddrIn()			{ return reinterpret_cast< sockaddr_in* >( &mSockAddr ); }
	const	sockaddr_in*	GetAsSockAddrIn()	const	{ return reinterpret_cast< const sockaddr_in* >( &mSockAddr ); }

};

typedef std::shared_ptr< SocketAddress > SocketAddressPtr;

#endif /* NETWORK_SOCKETADDRESS_H_ */
