#pragma once
#include "Seting.h"
//��ʱ��
class Timer
{
public:
	Timer(int ts)
		:next(NULL), prev(NULL), time(ts),_time(ts) {} 
	void *(*cb_func)();      //��ʱ���Ļص�����
	TimerData user_data;             //�ͻ�������

public:
	int time;                      //��ʱ��ʱ��
	int _time;                      //��ʱ����ʼʱ��
	int type = 0;
	int count = 1;
	shared_ptr<Timer> prev;                     //ָ����һ����ʱ��
	shared_ptr<Timer> next;                     //ָ����һ����ʱ��
};
