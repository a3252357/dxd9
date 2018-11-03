#pragma once
#include "Seting.h"
#include "TimerData.h"
//定时器
class Timer
{
public:
	Timer(int ts)
		:next(NULL), prev(NULL), time(ts),_time(ts) {} 
	TimerData * data;
	//TimerData user_data;             //客户端数据
	int time;                      //定时器时间
	int _time;                      //定时器初始时间
	int type = 0;
	int count = 1;
	shared_ptr<Timer> prev;                     //指向上一个定时器
	shared_ptr<Timer> next;                     //指向下一个定时器
};
