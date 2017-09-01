/*
 * UDPSocket.h
 *
 *  Created on: 1 Sep 2017
 *      Author: faizh
 */

#ifndef NETWORK_UDPSOCKET_H_
#define NETWORK_UDPSOCKET_H_

#include "SocketAddress.h"

using namespace std;

class UDPSocket
{
public:

	~UDPSocket();

	int Bind( const SocketAddress& inToAddress );
	int SendTo( const void* inToSend, int inLength, const SocketAddress& inToAddress );
	int ReceiveFrom( void* inToReceive, int inMaxLength, SocketAddress& outFromAddress );

private:
	UDPSocket( SOCKET inSocket ) : mSocket( inSocket ) {}
	SOCKET mSocket;

};

typedef shared_ptr< UDPSocket >	UDPSocketPtr;

#endif /* NETWORK_UDPSOCKET_H_ */
