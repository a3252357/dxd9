#include "PlayerStandState.h"



PlayerStandState::PlayerStandState(Player * _player)
{
	player = _player;
}

PlayerStandState::~PlayerStandState()
{
}

HRESULT PlayerStandState::Update()
{
	InputHandle();
	return E_NOTIMPL;
}

HRESULT PlayerStandState::Render()
{
	return E_NOTIMPL;
}

HRESULT PlayerStandState::InputHandle()
{
	if (InputInit::g_KeyboardState[DIK_LEFT] & 0x8000f) {
		//player->playeranimations
	}
	if (InputInit::g_KeyboardState[DIK_RIGHT] & 0x8000f) {}
	if (InputInit::g_KeyboardState[DIK_UP] & 0x8000f) {
	}
	if (InputInit::g_KeyboardState[DIK_DOWN] & 0x8000f) {}
	return S_OK;
}
