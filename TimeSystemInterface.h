#pragma once
class TimeSystemInterface {
public:
	virtual int getCurrentTime() = 0;
	virtual int getLastTime() = 0;
};