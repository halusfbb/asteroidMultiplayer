/*
 * SocketUtil.h
 *
 *  Created on: 29 Aug 2017
 *      Author: faizh
 */

#ifndef UTILS_SOCKETUTIL_H_
#define UTILS_SOCKETUTIL_H_

#include <sys/socket.h>

enum SocketAddressFamily
{
	INET = AF_INET,
	INET6 = AF_INET6
};

class SocketUtil
{
public:

	static bool			StaticInit();
	static void			CleanUp();

	static void			ReportError( const char* inOperationDesc );
	static int			GetLastError();

private:

};


#endif /* UTILS_SOCKETUTIL_H_ */
