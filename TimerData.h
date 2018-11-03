#pragma once
#include <string>
using namespace std;
class Timer;
class TimerData
{
public:
	TimerData();
	~TimerData();
	virtual	void callback();
	void start(int _timeout, int type = 0, int count = 1);
	void stop();
	int getTimeout();
	void setTimeout(int _timeout);
private:
	shared_ptr<Timer> time;
	int timeout;

};