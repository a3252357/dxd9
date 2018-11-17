#pragma once
class BaseUI {
	//IState();
public:
	virtual ~BaseUI() {};
	virtual HRESULT 	Init() = 0;
	virtual HRESULT Update() = 0;
};
