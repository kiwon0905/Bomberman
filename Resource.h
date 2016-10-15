#pragma once
#include <string>
#include <cassert>

//Base class for all resources.........
class Resource
{
public:
	std::string name;
	bool loaded;
public:
	Resource():loaded(false){};
	Resource(std::string name_):name(name_), loaded(true){};
	virtual void load(std::string name)=0;
	~Resource(){};
};

