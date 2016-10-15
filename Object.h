#pragma once
#include <string>

class Object
{
private:
	static unsigned long nextID()
	{
		static unsigned long id=0;
		return ++id;
	}
protected:
	unsigned long id;//Every game Object has an unique id. For future use maybe.
public:
	Object(){id=nextID();}
	Object(const Object&){id=nextID();}
	Object& operator=(const Object & o)
	{
		id=nextID();
	}
	virtual ~Object(){}
	unsigned long getID(){return id;}

	//virtual void tick(double dt)=0;
};