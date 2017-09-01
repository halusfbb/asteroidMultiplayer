/*
 * SocketUtil.cpp
 *
 *  Created on: 29 Aug 2017
 *      Author: faizh
 */

#include "SocketUtil.h"

#include "cocos2d.h"

bool SocketUtil::StaticInit()
{
#if _WIN32
	WSADATA wsaData;
	int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if ( iResult != NO_ERROR )
	{
		ReportError ("Starting Up");
		return false;
	}
#endif
	return true;
}

void SocketUtil::CleanUp()
{
#if _WIN32
	WSACleanup();
#endif
}

void SocketUtil::ReportError( const char* inOperationDesc )
{
#if _WIN32
	LPVOID lpMsgBuf;
	DWORD errorNum = GetLastError();

	FormatMessage(
				  FORMAT_MESSAGE_ALLOCATE_BUFFER |
				  FORMAT_MESSAGE_FROM_SYSTEM |
				  FORMAT_MESSAGE_IGNORE_INSERTS,
				  NULL,
				  errorNum,
				  MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
				  (LPTSTR) &lpMsgBuf,
				  0, NULL );


	CCLOG( "Error %s: %d- %s", inOperationDesc, errorNum, lpMsgBuf );
#else
	CCLOG( "Error: %s", inOperationDesc );
#endif
}

int SocketUtil::GetLastError()
{
#if _WIN32
	return WSAGetLastError();
#else
	return errno;
#endif
}
