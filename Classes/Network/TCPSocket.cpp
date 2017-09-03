/*
 * TCPSocket.cpp
 *
 *  Created on: 29 Aug 2017
 *      Author: faizh
 */

#include "TCPSocket.h"
#include "SocketUtil.h"
#include "cocos2d.h"
#include <unistd.h>

int TCPSocket::Connect( const SocketAddress& inAddress )
{
	int err = connect( mSocket, &inAddress.mSockAddr, inAddress.GetSize() );
	if( err < 0 )
	{
		SocketUtil::ReportError( "TCPSocket::Connect" );
		return -SocketUtil::GetLastError();
	}
#ifdef _WIN32
	return NO_ERROR;
#else
	return 0;
#endif
}

int TCPSocket::Bind( const SocketAddress& inBindAddress )
{
	int error = bind( mSocket, &inBindAddress.mSockAddr, inBindAddress.GetSize() );
	if( error != 0 )
	{
		SocketUtil::ReportError( "TCPSocket::Bind" );
		return SocketUtil::GetLastError();
	}

#ifdef _WIN32
	return NO_ERROR;
#else
	return 0;
#endif
}

int TCPSocket::Listen( int inBackLog )
{
	int err = listen( mSocket, inBackLog );
	if( err < 0 )
	{
		SocketUtil::ReportError( "TCPSocket::Listen" );
		return -SocketUtil::GetLastError();
	}

#ifdef _WIN32
	return NO_ERROR;
#else
	return 0;
#endif
}

TCPSocketPtr TCPSocket::Accept( SocketAddress& inFromAddress )
{
	socklen_t length = inFromAddress.GetSize();
	SOCKET newSocket = accept( mSocket, &inFromAddress.mSockAddr, &length );

#ifdef _WIN32
	if( newSocket != INVALID_SOCKET )
#else
	if( newSocket > 0 )
#endif
	{
		return TCPSocketPtr( new TCPSocket( newSocket ) );
	}
	else
	{
		SocketUtil::ReportError( "TCPSocket::Accept" );
		return nullptr;
	}
}

int32_t	TCPSocket::Send( const void* inData, size_t inLen )
{
	int bytesSentCount = send( mSocket, static_cast< const char* >( inData ), inLen, 0 );

	//!!@Faizhal am not sure if this case needs to be handled. applying an assert here to catch if such cases can occurs
	CCASSERT(bytesSentCount == inLen, "UDPSocket::sendTo bytes sent is less than requested length");

	if( bytesSentCount < 0 )
	{
		SocketUtil::ReportError( "TCPSocket::Send" );
		return -SocketUtil::GetLastError();
	}
	return bytesSentCount;
}

int32_t	TCPSocket::Receive( void* inData, size_t inLen )
{
	int bytesReceivedCount = recv( mSocket, static_cast< char* >( inData ), inLen, 0 );

	//!!@Faizhal am not sure if this case needs to be handled. applying an assert here to catch if such cases can occurs
	CCASSERT(bytesReceivedCount == inLen, "UDPSocket::sendTo bytes sent is less than requested length");


	if( bytesReceivedCount < 0 )
	{
		SocketUtil::ReportError( "TCPSocket::Receive" );
		return -SocketUtil::GetLastError();
	}
	return bytesReceivedCount;
}

TCPSocket::~TCPSocket()
{
#if _WIN32
	closesocket( mSocket );
#else
	close( mSocket );
#endif
}
