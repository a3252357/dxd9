#pragma once
#include "Seting.h"
#include "Timer.h"
#define BUFFER_SIZE 64





//ʱ����
class time_wheel
{
public:
	time_wheel();
	~time_wheel();

	void add_timer(shared_ptr<Timer> timer);   //���ݶ�ʱֵ������ʱ������������ʵ�λ��
	void del_timer(shared_ptr<Timer> timer);    //ɾ��Ŀ�궨ʱ��
	void tick();                //ʱ�䵽����øú�����ʱ������ǰ����һ���ۼ��

private:
	static const int N = 120;    //ʱ�����ϲ۵���Ŀ
	const int TI = 5;    //�ۼ��ʱ�䣬ÿtickʱ����ת��һ��

	int cur_slot;               //ʱ���ֵĵ�ǰ��
	shared_ptr<Timer> slots[N];         //ʱ���ֵĲۣ�����ÿ��Ԫ��ָ��һ����ʱ������

};


