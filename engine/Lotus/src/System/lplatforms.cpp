/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include <system\lplatforms.h>

using namespace Lotus;

#if defined(USING_VC71)

String Lotus::TypeName(const char* typeName)
{
	typeName += 6;
	return String(typeName);
}

#endif