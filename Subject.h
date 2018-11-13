#pragma once
#include "Seting.h"
#include "Observer.h"
class Subject 
{
private:
	vector<Observer *>  observers;
	vector<Observer *>::iterator it;
public:
	void addObservers(Observer * observer) {
		observers.push_back(observer);
	}
	void removeObservers(Observer * observer) {
			for (it = observers.begin(); it != observers.end();)
			{
				if (*it == observer)
					it = observers.erase(it);    //删除元素，返回值指向已删除元素的下一个位置
				else
					++it;    //指向下一个位置
			}
	}
protected:
	void notify(shared_ptr<BaseSprite> sprite, Huangjianjian::Event event) {
		for (it = observers.begin(); it != observers.end();)
		{
			Observer * p= *it;
			p->onNotify(sprite,event);
		}
	}
};
