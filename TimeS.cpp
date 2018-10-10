#include "TimeS.h"
TimeS::TimeS(void)
{
	istimer = false;
	QueryPerformanceFrequency(&cpuHz);
}

TimeS::~TimeS(void)
{
}

void TimeS::start()
{
  bool set=	QueryPerformanceCounter(&startTime);
  istimer = true;
}

void TimeS::end()
{
	bool set = QueryPerformanceCounter(&endTime);

	time = ((double)endTime.QuadPart - (double)startTime.QuadPart) / (double)cpuHz.QuadPart;
	istimer = false;
}

