#include "SnakeBody.h"


HRESULT SnakeBody::Add(shared_ptr<Sprite> _sprite)
{
	bodys.push_back(_sprite);
	return S_OK;
}

HRESULT SnakeBody::Update()
{
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
	return S_OK;
}

void SnakeBody::snakenext()
{
	list<shared_ptr<Sprite>>::iterator plist;
	for (plist = bodys.begin(); plist != bodys.end(); plist++) {
		shared_ptr<Sprite> basehead = *plist;
		if (plist == bodys.begin()) {
			if (snakeup == 0) {
				basehead->Set_State(basehead->m_x + 32, basehead->m_y, 0);
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
			plist--;
			shared_ptr<Sprite> base = *plist;
			base->Set_State(basehead->n_x, basehead->n_y, 0);
			plist++;
			//				if (list->next != NULL)
			//			list = list->next;
		}
	}
}
