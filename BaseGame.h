#ifndef BASEGAME_H
#define BASEGAME_H
#include "Seting.h"
class BaseGame
{
public:
	virtual HRESULT Update() = 0;
	virtual HRESULT Init() = 0;
	virtual HRESULT Render() = 0;
};
#endif