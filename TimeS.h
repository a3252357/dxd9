#pragma once
#include <windows.h>
#include <time.h>
class TimeS
{
public:
	TimeS(void);
	~TimeS(void);//��������

private:
	long startTime;

	long endTime;

	long cpuHz;

public:
	long time;
public:
	void start();
	long getStart();
	long getEnd();
	void end();
};

