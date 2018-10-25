#pragma once
class IState
{
public:
	IState();
	~IState();
	HRESULT Update(float delta);

private:

};

IState::IState()
{
}

IState::~IState()
{
}

inline HRESULT IState::Update(float delta)
{
	throw "Is Not Im";
}
