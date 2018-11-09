#include "TimerData.h"
TimerData::TimerData()
{
	
}

TimerData::~TimerData()
{
}

void  TimerData::callback()
{
}

void TimerData::start(int _timeout, int type, int count)
{
	time = make_shared<Timer>(_timeout);
	time->type = type;
	time->count = count;
	time->data = this;
	TimeInit::time->add_timer(time);
}

void TimerData::stop()
{
	TimeInit::time->del_timer(time);
}

int TimerData::getTimeout()
{
	return timeout;
}

void TimerData::setTimeout(int _timeout)
{
	timeout = _timeout;
}
