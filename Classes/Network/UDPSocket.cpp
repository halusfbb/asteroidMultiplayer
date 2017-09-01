/*
 * UDPSocket.cpp
 *
 *  Created on: 1 Sep 2017
 *      Author: faizh
 */

#include "UDPSocket.h"
#include "SocketUtil.h"
#include <errno.h>
#include <unistd.h>
#include "cocos2d.h"

int UDPSocket::Bind( const SocketAddress& inBindAddress )
{
	int error = bind( mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize() );
	if( error != 0 )
	{
		SocketUtil::ReportError( "UDPSocket::Bind" );
		return SocketUtil::GetLastError();
	}

#ifdef _WIN32
	return NO_ERROR;
#else
	return 0;
#endif
}

int UDPSocket::SendTo( const void* inToSend, int inLength, const SocketAddress& inToAddress )
{
	int byteSentCount = sendto( mSocket,
							   static_cast< const char* >( inToSend ),
							   inLength,
							   0, &inToAddress.mSockAddr, inToAddress.GetSize() );

	//am not sure if this case needs to be handled. applying an assert here to catch if such cases can occurs
	CCASSERT(byteSentCount == inLength, "UDPSocket::sendTo bytes sent is less than requested length");

	if( byteSentCount <= 0 )
	{
		//we'll return error as negative number to indicate less than requested amount of bytes sent...
		SocketUtil::ReportError( "UDPSocket::SendTo" );
		return -SocketUtil::GetLastError();
	}
	else
	{
		return byteSentCount;
	}
}

int UDPSocket::ReceiveFrom( void* inToReceive, int inMaxLength, SocketAddress& outFromAddress )
{
	socklen_t fromLength = outFromAddress.GetSize();

	int readByteCount = recvfrom( mSocket,
								 static_cast< char* >( inToReceive ),
								 inMaxLength,
								 0, &outFromAddress.mSockAddr, &fromLength );
	if( readByteCount >= 0 )
	{
		return readByteCount;
	}
	else
	{
		int error = SocketUtil::GetLastError();

#ifdef _WIN32
		if( error == WSAEWOULDBLOCK )
#else
		if( error == EWOULDBLOCK )
#endif
		{
			return 0;
		}
#ifdef _WIN32
		else if( error == WSAECONNRESET )
#else
		else if( error == ECONNRESET )
#endif
		{
			//this can happen if a client closed and we haven't DC'd yet.
			//this is the ICMP message being sent back saying the port on that computer is closed
			CCLOG( "Connection reset from %s", outFromAddress.ToString().c_str() );
#ifdef _WIN32
			return -WSAECONNRESET;
#else
			return -ECONNRESET;
#endif
		}
		else
		{
			SocketUtil::ReportError( "UDPSocket::ReceiveFrom" );
			return -error;
		}
	}
}

UDPSocket::~UDPSocket() //!!@Faizhal: how about socket shutdown operation?
{
#if _WIN32
	closesocket( mSocket );
#else
	close( mSocket );
#endif
}

//int UDPSocket::SetNonBlockingMode( bool inShouldBeNonBlocking )
//{
//#if _WIN32
//	u_long arg = inShouldBeNonBlocking ? 1 : 0;
//	int result = ioctlsocket( mSocket, FIONBIO, &arg );
//#else
//	int flags = fcntl( mSocket, F_GETFL, 0 );
//	flags = inShouldBeNonBlocking ? ( flags | O_NONBLOCK ) : ( flags & ~O_NONBLOCK);
//	int result = fcntl( mSocket, F_SETFL, flags );
//#endif
//
//	if( result == SOCKET_ERROR )
//	{
//		SocketUtil::ReportError( "UDPSocket::SetNonBlockingMode" );
//		return SocketUtil::GetLastError();
//	}
//	else
//	{
//		return NO_ERROR;
//	}
//}


