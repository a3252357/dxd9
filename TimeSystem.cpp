//tw_timer.cpp

#include "TimeSystem.h"

time_wheel::time_wheel() :cur_slot(0)
{
	//初始化每个槽的头结点
	for (int i = 0; i < N; ++i)
		slots[i] = NULL;
}

time_wheel::~time_wheel()
{
	//遍历每个槽，并销毁定时器
	for (int i = 0; i < N; ++i) {
		shared_ptr<Timer> tmp = slots[i];
		while (tmp) {
			slots[i] = tmp->next;
			tmp.~shared_ptr();
			tmp = slots[i];
		}
	}
}

void time_wheel::add_timer(shared_ptr<Timer>timer)
{
	int timeout = timer->time;
	if (timeout < 0)
		return;

	int ticks = 0;              //待插入定时器所需要总ticks
	if (timeout < TI)
		ticks = 1;
	else
		ticks = timeout / TI;

	int rotation = ticks / N;   //计算待插入的定时器在时间轮上要转动多少圈后触发
	int ts = (cur_slot + ticks) % N; //计算待持入定时器应该被插入的位置
									 //int ts = (cur_slot + (ticks %N)) % N;

									 //创建定时器，它在时间轮转动rotation圈之后触发，且位于第ts个槽上

	//如果槽为空，则它新定时器插入，并设置为该槽的头节点
	if (!slots[ts]) {
		//printf("add timer, rotation is %d, ts is %d, cur_slot is %d\n",
		//	rotation, ts, cur_slot);
		slots[ts] = timer;
	}
	else {
		timer->next = slots[ts];
		slots[ts]->prev = timer;
		slots[ts] = timer;
	}
}

void time_wheel::del_timer(shared_ptr<Timer> timer)
{
	if (!timer)
		return;

	int timeout = timer->time;
	if (timeout < 0)
		return;

	int ticks = 0;              //待刪除定时器所需要总ticks
	if (timeout < TI)
		ticks = 1;
	else
		ticks = timeout / TI;

	//int rotation = ticks / N;   //计算待刪除的定时器在时间轮上要转动多少圈后触发
	int ts = (cur_slot + ticks) % N; //计算待刪除定时器应该被插入的位置
	if (timer == slots[ts]) {   //如果是头结点
		slots[ts] = slots[ts]->next;
		if (slots[ts])
			slots[ts]->prev = NULL;

		timer.~shared_ptr();
	}
	else {
		timer->prev->next = timer->next;
		if (timer->next)
			timer->next->prev = timer->prev;

		timer.~shared_ptr();
	}
}

void time_wheel::tick()
{
	//取得时间轮上当前槽的头结点
	shared_ptr<Timer> tmp = slots[cur_slot];
	//printf("current slot is %d\n", cur_slot);

	while (tmp) {
		//printf("tick the timer once\n");

		//如果定时器的rotation值大于0，则未到时，不处理
		if (tmp->time > N*TI) {
			tmp->time -= N* TI;
			tmp = tmp->next;
		}
		else {
			tmp->cb_func(tmp->user_data);
			if (tmp == slots[cur_slot]) {
				//printf("delete header in cur_slot\n");
				slots[cur_slot] = tmp->next;

				tmp.~shared_ptr();

				if (slots[cur_slot])
					slots[cur_slot]->prev = NULL;

				tmp = slots[cur_slot];
			}
			else {
				tmp->prev->next = tmp->next;
				if (tmp->next)
					tmp->next->prev = tmp->prev;

				shared_ptr<Timer> tmp2 = tmp->next;

				tmp.~shared_ptr();
				tmp = tmp2;
			}
		}
	}

	//更新时间轮的当前槽，以反映时间轮的转动
	cur_slot = ++cur_slot % N;
}

