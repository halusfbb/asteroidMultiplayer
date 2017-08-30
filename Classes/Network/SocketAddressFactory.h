/*
 * SocketAddressFactory.h
 *
 *  Created on: 30 Aug 2017
 *      Author: faizh
 */

#ifndef NETWORK_SOCKETADDRESSFACTORY_H_
#define NETWORK_SOCKETADDRESSFACTORY_H_

#include "SocketAddress.h"
#include <string.h>

using namespace std;

class SocketAddressFactory
{
public:
	//The function returns a SocketAddressPtr so that it has the option of returning nullptr
	//if anything goes wrong with the name conversion. This is a nice alternative to making
	//a SocketAddress constructor do the conversion because, without requiring exception handling,
	//it makes sure there is never an incorrectly initialized SocketAddress in existence
	static SocketAddressPtr CreateIPv4FromString( const string& inString );
};

#endif /* NETWORK_SOCKETADDRESSFACTORY_H_ */
