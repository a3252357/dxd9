#pragma once
#include "TimeWheel.h"
class TimeWheel;
static class TimeInit {
public:
	static HRESULT Time_Init();
	static shared_ptr<TimeWheel> time;
};