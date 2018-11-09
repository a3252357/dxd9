#pragma once
/*
**FileName: callback.h
**Description: 回调函数机制封装（支持类成员函数与全局函数）
**Autor: by Roobt
**Create Time: 2012/11/26   10:34
*/

#include <map>
#include <string>
using std::map;
using std::make_pair;
namespace UserCall {
	typedef int EventID;
	typedef bool (SlotFunction)();  //函数指针
	//回调基类
	class SlotFunctorBase
	{
	public:
		virtual ~SlotFunctorBase() {};

		//使用操作符来调用函数
		virtual bool operator()() = 0;
	};

	//全局函数、静态函数或类的静态成员函数做回调
	class FreeFunctionSlot : public SlotFunctorBase
	{

	public:
		FreeFunctionSlot(SlotFunction* func) : d_function(func)
		{}

		virtual bool operator()()
		{
			return d_function();
		}

	private:
		SlotFunction* d_function;
	};

	//类的普通成员函数做回调
	template<typename T>
	class MemberFunctionSlot : public SlotFunctorBase
	{
	public:
		//!成员变量的回调函数定义
		typedef bool (T::*MemberFunctionType)();  //类的成员函数指针的类型

	public:
		MemberFunctionSlot(MemberFunctionType func, shared_ptr<T> obj) :
			d_function(func), d_object(obj)
		{}

		virtual bool operator()()
		{
			T *pInt = d_object.get();
			return (pInt->*d_function)();  //调用类的成员函数
		}

	private:
		MemberFunctionType d_function;
		shared_ptr<T> d_object;
	};


	//对上面2种实现的封装
	class SubscriberSlot
	{
	public:
		//默认构造函数
		SubscriberSlot()
		{
			d_functor_impl = NULL;
		}

		//标准析构函数
		~SubscriberSlot()
		{
			delete d_functor_impl;
			d_functor_impl = NULL;
		}

		//调用函数的()重载，具体由第一类Functor实现
		bool operator()() const
		{
			return (*d_functor_impl)();
		}

		//返回成员是否有效，是否已经连接到一个具体的Functor实现
		bool connected() const
		{
			return d_functor_impl != NULL;
		}

		//FreeFunctionSlot，自由函数的封装类
		SubscriberSlot(SlotFunction* func) :
			d_functor_impl(new FreeFunctionSlot(func))
		{}

		// 模板构造函数，以成员函数的封装为参数，MemberFunctionSlot。
		template<typename T>
		SubscriberSlot(bool (T::*function)(), shared_ptr<T> obj) :
			d_functor_impl(new MemberFunctionSlot<T>(function, obj))
		{}

	private:
		//内部基本Functor的指针，SlotFunctorBase基类的优势在这里用到了
		SlotFunctorBase* d_functor_impl;
	};

	// 注册函数宏
	// 注册全局函数、类静态成员函数作为回调函数
#define  REGISTER_FUNC(id, subscribeSlot, func, q) \
 UserCall::SubscriberSlot* subscribeSlot = new UserCall::SubscriberSlot((FreeFunctionSlot::SlotFunction*)&func);\
 q->subscribe(id, subscribeSlot);

// 注册类成员函数作为回调函数
// param0: 事件id
// param1: psubscribeSlot, 随便一个变量名
// param2: func, 要注册的类的普通成员函数（即：回调函数）
// param3: p, func所在类的一个实例指针
// param4: q, 注册类（调用注册函数的类）的一个实例指针
#define REGISTER_OBJFUNC(id, subscribeSlot, func, p, q) \
 UserCall::SubscriberSlot* subscribeSlot = new UserCall::SubscriberSlot(func, p);\
 q->subscribe(id, subscribeSlot);

// 回调
	class Callback
	{
	public:
		typedef map<EventID, UserCall::SubscriberSlot*> EventMap;

	public:
		Callback() { eventList.clear(); }
		~Callback() { eventList.clear(); }

		bool subscribe(EventID id, UserCall::SubscriberSlot* subscriberSlot)
		{
			if (NULL == subscriberSlot)
				return false;
			EventMap::iterator iter = eventList.find(id);
			if (iter != eventList.end())
				return false;
			eventList.insert(make_pair(id, subscriberSlot));
			return true;
		}

		bool evoke(EventID id)
		{
			EventMap::iterator iter = eventList.find(id);
			if (iter == eventList.end())
				return false;
			UserCall::SubscriberSlot* subscribeSlot = eventList[id];
			if (subscribeSlot)
			{
				(*subscribeSlot)();
				return true;
			}
			return false;
		}

	private:
		EventMap eventList;
	};
}