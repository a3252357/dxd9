#pragma once
#include "Seting.h"
#include "CallBackTimer.h"
using namespace std;
template<typename T>
class Timerutil
{
typedef  std::map<string, CallBackTimer<T>*> TIMER_MAP;
public:
	TIMER_MAP timers;
	Timerutil() {};
	~Timerutil() {};
	bool InvokeRepeating(bool (T::*function)(), string functionname,float delayTime, float spawnTime) {
		CallBackTimer<T>* timer = new CallBackTimer<T>((T*)this, function);
		timer->start(100, 1, 100);
		timers.insert(TIMER_MAP::value_type(functionname, timer));
		return true;
	};
	bool CancelInvoke(string functionname) {
		std::map<string, CallBackTimer<T>*>::reverse_iterator iter;

		for (iter = timers.rbegin(); iter != timers.rend(); iter++)
		{
			if (lstrcmpW(StringUtil::ConvertstringToLPCWSTR(iter->first), StringUtil::ConvertstringToLPCWSTR(functionname)) == 0)
				iter->second->stop();
		}
		return true;
	};
};

