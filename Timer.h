#pragma once
#include "Seting.h"
//��ʱ��
class Timer
{
public:
	Timer(int ts)
		:next(NULL), prev(NULL), time(ts) {}
	void(*cb_func)(shared_ptr<TimerData>);      //��ʱ���Ļص�����
	shared_ptr<TimerData> user_data;             //�ͻ�������

public:
	int time;                      //��ʱ��ʱ��


	shared_ptr<Timer> prev;                     //ָ����һ����ʱ��
	shared_ptr<Timer> next;                     //ָ����һ����ʱ��
};
