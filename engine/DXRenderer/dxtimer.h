/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#ifndef _HDR_DXTIMER_H
#define _HDR_DXTIMER_H

#include <windows.h>

namespace DX
{
	class Timer
	{
	private:
		double ticksPerMicroSecond;
		LARGE_INTEGER tbegin;
	public:
		Timer();
		void begin();
		double timeMS();
	};
}

#endif