#include "SnakeBody.h"

SnakeBody* SnakeBody::CurMy;
SnakeBody::SnakeBody()
{
}

SnakeBody::~SnakeBody()
{
}

HRESULT SnakeBody::Add(shared_ptr<Sprite> _sprite)
{
	bodys.add(_sprite);
	return S_OK;
}

HRESULT SnakeBody::Update()
{
	for (int i = 0;i<bodys.size();i++)
	{
		bodys.find(i)->Update();
	}
	if (InputInit::g_KeyboardState[DIK_LEFT] & 0x8000f) {
		snakeup = 2;
	}
	if (InputInit::g_KeyboardState[DIK_RIGHT] & 0x8000f) { snakeup = 0; }
	if (InputInit::g_KeyboardState[DIK_UP] & 0x8000f) {
		snakeup = 1;
	}
	if (InputInit::g_KeyboardState[DIK_DOWN] & 0x8000f) { snakeup = 3; }
	return S_OK;
}

HRESULT SnakeBody::Render()
{
	for(int i=0;i<bodys.size();i++)
	{
		bodys.find(i)->Render();
	}
	return S_OK;
}

void * SnakeBody::callback()
{
	CurMy->snakenext();
	return NULL;
}
void SnakeBody::setCurMy()
{//设置当前对象为回调函数调用的对象  
	CurMy = this;
}
void SnakeBody::snakenext()
{
	list<shared_ptr<Sprite>>::iterator plist;
	bodys.setNow();
	for (int i = 2;i<bodys.size();i++)
	{
		shared_ptr<Sprite> basehead = bodys.getNow()->data;
		if (basehead == bodys.find(0)) {
			if (snakeup == 0) {
				basehead->Set_State(basehead->m_x + 32, basehead->m_y, 0);
				printf("ce");
			}
			if (snakeup == 1) {
				basehead->Set_State(basehead->m_x, basehead->m_y - 32, 0);
			}
			if (snakeup == 2) {
				basehead->Set_State(basehead->m_x - 32, basehead->m_y, 0);
			}
			if (snakeup == 3) {
				basehead->Set_State(basehead->m_x, basehead->m_y + 32, 0);
			}
		}
		else {
			shared_ptr<Sprite> base = basehead;
			bodys.goPrev();
			basehead = bodys.getNow()->data;
			base->Set_State(basehead->n_x, basehead->n_y, 0);
			bodys.goNext();
			//				if (list->next != NULL)
			//			list = list->next;
		}
		bodys.goNext();
	}
	shared_ptr<Timer> timer = make_shared<Timer>(1000);
	this->setCurMy();
	timer->cb_func = this->callback;
	TimeInit::time->add_timer(timer);
}
