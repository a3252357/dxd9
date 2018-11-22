#pragma once
#include "SnakeBody.h"
#include "TimerCallback.h"
#include "TimerData.h"
using namespace UserCall;
template<typename T>
class CallBackTimer :public TimerData,public UserCall::Callback
{
	
private:
	T* m_pAObj;
public:
	enum EVENT_TYPE
	{
		EVENT_TYPE_INVALID = -1,
		EVENT_TYPE1,
		EVENT_TYPE2,
		EVENT_TYPE_NUMBER,
	};
	CallBackTimer(shared_ptr<T> pA, bool (T::*function)()) : m_pAObj(pA.get())
	{
		registerCallback(function);
	};
	CallBackTimer(T* pA, bool (T::*function)()) : m_pAObj(pA)
	{
		registerCallback(function);
	};

	void registerCallback(bool (T::*function)())
	{
		// 类成员函数
		REGISTER_OBJFUNC(EVENT_TYPE1, subscribeSlot, function, m_pAObj, this);
		// 类静态函数
		//REGISTER_FUNC(EVENT_TYPE2, subscribeSlot2, A::Test2, this);
	};
	void callback() override
	{
		Callback::evoke(EVENT_TYPE1);
		//Callback::evoke(EVENT_TYPE2);
	};
	
};