#pragma once
#include "Seting.h"
#include "Timer.h"
template<class T>
class TimerWithSprite {
	public:
		TimerWithSprite(T * _CurMy, void (T::*_cb_func)());
		static T* CurMy;//存储回调函数调用的对象  
		static void* callback();
		static void (T::*cb_func)();      //定时器的回调函数
		void start(int _timeout, int type = 0, int count = 1);
		void getTimeout();
		void setTimeout(int _timeout);
	private:
		shared_ptr<Timer> time;
		int timeout;
};
template<class T>
T* TimerWithSprite<T>::CurMy;

template<class T>
void (T::*TimerWithSprite<T>::cb_func)();

template<class T>
inline TimerWithSprite<T>::TimerWithSprite(T * _CurMy, void (T::*_cb_func)())
{
	CurMy = _CurMy;
	cb_func = _cb_func;
}

template<class T>
inline void * TimerWithSprite<T>::callback()
{
	(CurMy->*cb_func)();
	return NULL;
}

template<class T>
inline void TimerWithSprite<T>::start(int _timeout,int type=0,int count=1)
{
	time =make_shared<Timer>(_timeout);
	time->type = type;
	time->count = count;
	time->cb_func = this->callback;
	TimeInit::time->add_timer(time);
}

template<class T>
inline void TimerWithSprite<T>::getTimeout()
{
	return timeout;
}

template<class T>
inline void TimerWithSprite<T>::setTimeout(int _timeout)
{
	timeout = _timeout;
}
