#include "SnakeBody.h"

SnakeBody::SnakeBody()
{
	//timer->cb_func = &SnakeBody::snakenext;
	//timer->CurMy = this;
}

SnakeBody::~SnakeBody()
{
}

HRESULT SnakeBody::Add(shared_ptr<AnimationFrame> _sprite)
{
	bodys.add(_sprite);
	return S_OK;
}

HRESULT SnakeBody::Update()
{
	bodys.setHeadToNow();
	for (int i = 0;i<bodys.size();i++)
	{
		bodys.getNow()->data->Update();
		bodys.goNext();
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
		bodys.getNow()->data->Render();
		bodys.goNext();
	}
	return S_OK;
}

bool SnakeBody::snake()
{
	list<shared_ptr<AnimationFrame>>::iterator plist;
	bodys.setHeadToNow();
	for (int i = 1;i < bodys.size();i++)
	{
		shared_ptr<AnimationFrame> basehead = bodys.getNow()->data;
		notify(basehead, Huangjianjian::SNAKE_GO);
		if (basehead == bodys.head->data) {
			if (snakeup == 0) {
				basehead->Set_State(basehead->m_x + BOX_WIDTH, basehead->m_y, 0);
			}
			if (snakeup == 1) {
				basehead->Set_State(basehead->m_x, basehead->m_y - BOX_WIDTH, 0);
			}
			if (snakeup == 2) {
				basehead->Set_State(basehead->m_x - BOX_WIDTH, basehead->m_y, 0);
			}
			if (snakeup == 3) {
				basehead->Set_State(basehead->m_x, basehead->m_y + BOX_WIDTH, 0);
			}
		}
		else {
			shared_ptr<AnimationFrame> base = basehead;
			bodys.goPrev();
			basehead = bodys.getNow()->data;
			base->Set_State(basehead->n_x, basehead->n_y, 0);
			bodys.goNext();
			//				if (list->next != NULL)
			//			list = list->next;
		}
		bodys.goNext();
	}
	return true;
}
