/*****************************************
 *  Author: Hannes Widmoser              *
 *  Copyright 2007, All rights reserved. *
 ****************************************/

#include "dxtimer.h"

using namespace DX;

/* ------------------------------------------------------- */
/* class Timer:                                            */
/*                      PUBLIC                             */
/* ------------------------------------------------------- */
Timer::Timer()
{
	LARGE_INTEGER ticksPerSecond;
	QueryPerformanceFrequency(&ticksPerSecond);
	ticksPerMicroSecond = (ticksPerSecond.QuadPart/1000.0f);
}
/* ------------------------------------------------------- */
void Timer::begin()
{
	QueryPerformanceCounter(&tbegin);
}
/* ------------------------------------------------------- */
double Timer::timeMS()
{
	LARGE_INTEGER time;
	QueryPerformanceCounter(&time);
	return (time.QuadPart - tbegin.QuadPart) / ticksPerMicroSecond;
}
/* ------------------------------------------------------- */