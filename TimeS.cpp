#include "TimeS.h"
TimeS::TimeS(void)
{

}

TimeS::~TimeS(void)
{
}

void TimeS::start()
{
	startTime=clock();
}

long long TimeS::getStart()
{
	return startTime;
}

long long TimeS::getEnd()
{
	end();
	return endTime;
}

void TimeS::end()
{
	endTime = clock();
	time = endTime - startTime;
}

