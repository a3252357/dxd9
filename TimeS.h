#pragma once
#include <windows.h>
class TimeS
{
public:
	TimeS(void);
	~TimeS(void);//Îö¹¹º¯Êý

private:
	LARGE_INTEGER startTime;

	LARGE_INTEGER endTime;

	LARGE_INTEGER cpuHz;

public:
	double time;
	bool istimer;
public:
	void start();
	void end();
};

