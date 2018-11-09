#pragma once
#include "SnakeBody.h"
#include "TimerCallback.h"
#include "TimerData.h"
using namespace UserCall;
template<typename T>
class CallBackTimer :public TimerData,public UserCall::Callback
{
	
private:
	shared_ptr<T> m_pAObj;
public:
	enum EVENT_TYPE
	{
		EVENT_TYPE_INVALID = -1,
		EVENT_TYPE1,
		EVENT_TYPE2,
		EVENT_TYPE_NUMBER,
	};
	CallBackTimer(shared_ptr<T> pA, bool (T::*function)()) : m_pAObj(pA)
	{
		registerCallback(function);
	};

	void registerCallback(bool (T::*function)())
	{
		// ���Ա����
		REGISTER_OBJFUNC(1, subscribeSlot, function, m_pAObj, this);
		// �ྲ̬����
		//REGISTER_FUNC(EVENT_TYPE2, subscribeSlot2, A::Test2, this);
	};
	void callback() override
	{
		Callback::evoke(1);
		//Callback::evoke(EVENT_TYPE2);
	};
	
};