#ifndef BASE_H
#define BASE_H
class Base
{
public:
	void Update();
protected:
	virtual void OUpdate()=0;
	virtual void ORender()=0;
};
#endif
	