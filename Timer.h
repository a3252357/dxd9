#pragma once
#include "Seting.h"
//定时器
class Timer
{
public:
	Timer(int ts)
		:next(NULL), prev(NULL), time(ts) {}
	void(*cb_func)(shared_ptr<TimerData>);      //定时器的回调函数
	shared_ptr<TimerData> user_data;             //客户端数据

public:
	int time;                      //定时器时间


	shared_ptr<Timer> prev;                     //指向上一个定时器
	shared_ptr<Timer> next;                     //指向下一个定时器
};
