#include "Achievements.h"



Achievements::Achievements()
{
}


Achievements::~Achievements()
{
}

void Achievements::onNotify(shared_ptr<BaseSprite>, Huangjianjian::Event event)
{
	switch (event) {
	case Huangjianjian::Event::SNAKE_GO: MessageBox(SystemInit::hwnd, L"≤‚ ‘", L"≥…æÕ", 0);
	}
}
