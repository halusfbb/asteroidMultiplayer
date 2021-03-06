/*
 * StringUtil.cpp
 *
 *  Created on: 1 Sep 2017
 *      Author: faizh
 */

#include "StringUtil.h"

string StringUtils::Sprintf( const char* inFormat, ... )
{
	//not thread safe...
	static char temp[ 4096 ];

	va_list args;
	va_start (args, inFormat );

#if _WIN32
	_vsnprintf_s( temp, 4096, 4096, inFormat, args );
#else
	vsnprintf(temp, 4096, inFormat, args);
#endif
	return string( temp );
}


