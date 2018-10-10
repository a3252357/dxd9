#pragma once
#include "Seting.h"
#include "Timer.h"
#define BUFFER_SIZE 64





//时间轮
class time_wheel
{
public:
	time_wheel();
	~time_wheel();

	void add_timer(shared_ptr<Timer> timer);   //根据定时值创建定时器，并插入合适的位置
	void del_timer(shared_ptr<Timer> timer);    //删除目标定时器
	void tick();                //时间到后调用该函数，时间轮向前滚动一个槽间隔

private:
	static const int N = 120;    //时间轮上槽的数目
	const int TI = 5;    //槽间隔时间，每tick时间轮转动一次

	int cur_slot;               //时间轮的当前槽
	shared_ptr<Timer> slots[N];         //时间轮的槽，其中每个元素指向一个定时器链表

};


