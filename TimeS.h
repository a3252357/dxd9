#pragma once
#include <windows.h>
#include <time.h>
class TimeS
{
public:
	TimeS(void);
	~TimeS(void);//��������

private:
	long long startTime;

	long long endTime;

	long long cpuHz;

public:
	long long time;
public:
	void start();
	long long getStart();
	long long getEnd();
	void end();
};

