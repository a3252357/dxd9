//tw_timer.cpp

#include "TimeWheel.h"

TimeWheel::TimeWheel() :cur_slot(0)
{
	//��ʼ��ÿ���۵�ͷ���
	for (int i = 0; i < N; ++i)
		slots[i] = NULL;
}

TimeWheel::~TimeWheel()
{
	//����ÿ���ۣ������ٶ�ʱ��
	for (int i = 0; i < N; ++i) {
		shared_ptr<Timer> tmp = slots[i];
		while (tmp) {
			slots[i] = tmp->next;
			tmp.~shared_ptr();
			tmp = slots[i];
		}
	}
}

void TimeWheel::add_timer(shared_ptr<Timer>timer)
{
	int timeout = timer->_time;
	if (timeout < 0)
		return;

	int ticks = 0;              //�����붨ʱ������Ҫ��ticks
	if (timeout < TI)
		ticks = 1;
	else
		ticks = timeout / TI;

	int rotation = ticks / N;   //���������Ķ�ʱ����ʱ������Ҫת������Ȧ�󴥷�
	int ts = (cur_slot + ticks) % N; //��������붨ʱ��Ӧ�ñ������λ��
									 //int ts = (cur_slot + (ticks %N)) % N;

									 //������ʱ��������ʱ����ת��rotationȦ֮�󴥷�����λ�ڵ�ts������

	//�����Ϊ�գ������¶�ʱ�����룬������Ϊ�ò۵�ͷ�ڵ�
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

void TimeWheel::del_timer(shared_ptr<Timer> timer)
{
	if (!timer)
		return;

	int timeout = timer->time;
	if (timeout < 0)
		return;

	int ticks = 0;              //���h����ʱ������Ҫ��ticks
	if (timeout < TI)
		ticks = 1;
	else
		ticks = timeout / TI;

	//int rotation = ticks / N;   //������h���Ķ�ʱ����ʱ������Ҫת������Ȧ�󴥷�
	int ts = (cur_slot + ticks) % N; //������h����ʱ��Ӧ�ñ������λ��
	if (timer == slots[ts]) {   //�����ͷ���
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

void TimeWheel::del_timer_next(shared_ptr<Timer> timer)
{
	if (!timer)
		return;

	int timeout = timer->time;
	if (timeout < 0)
		return;

	int ticks = 0;              //���h����ʱ������Ҫ��ticks
	if (timeout < TI)
		ticks = 1;
	else
		ticks = timeout / TI;

	//int rotation = ticks / N;   //������h���Ķ�ʱ����ʱ������Ҫת������Ȧ�󴥷�
	int ts = (cur_slot + ticks) % N; //������h����ʱ��Ӧ�ñ������λ��
	if (timer == slots[ts]) {   //�����ͷ���
		slots[ts] = slots[ts]->next;
		if (slots[ts])
			slots[ts]->prev = NULL;

		//timer.~shared_ptr();
	}
	else {
		timer->prev->next = timer->next;
		if (timer->next)
			timer->next->prev = timer->prev;

		//timer.~shared_ptr();
	}
}

void TimeWheel::tick()
{
	//ȡ��ʱ�����ϵ�ǰ�۵�ͷ���
	shared_ptr<Timer> tmp = slots[cur_slot];
	//printf("current slot is %d\n", cur_slot);

	while (tmp) {
		//printf("tick the timer once\n");

		//�����ʱ����rotationֵ����0����δ��ʱ��������
		if (tmp->time > N*TI) {
			tmp->time -= N*TI;
			tmp = tmp->next;
		}
		else {
				tmp->cb_func(tmp->data);
				if (tmp == slots[cur_slot]) {
					//printf("delete header in cur_slot\n");
					slots[cur_slot] = tmp->next;

					if (tmp->type == 0 && --(tmp->count) == 0) {
						tmp.~shared_ptr();
					}
					else {
						//del_timer_next(tmp);
						add_timer(tmp);
					}
					if (slots[cur_slot])
						slots[cur_slot]->prev = NULL;

					tmp = slots[cur_slot];
				}
				else {
					tmp->prev->next = tmp->next;
					if (tmp->next)
						tmp->next->prev = tmp->prev;

					shared_ptr<Timer> tmp2 = tmp->next;

					if (tmp->type == 0 && --(tmp->count) == 0) {
						tmp.~shared_ptr();
					}
					else {
						//del_timer_next(tmp);
						add_timer(tmp);
					}
					tmp = tmp2;
				}
		}
	}

	//����ʱ���ֵĵ�ǰ�ۣ��Է�ӳʱ���ֵ�ת��
	cur_slot = ++cur_slot % N;
}

