#pragma once
#include "resource.h"
#include "FontResourceManager.h"


class FontResource :public Resource
{
private:
	static FontResourceManager manager;
public:
	FontResource():Resource(){};
	FontResource(std::string name);
	FontResource(const FontResource&);
	FontResource& operator=(const FontResource&);
	virtual void load(std::string name);
	~FontResource();
	sf::Font& operator()(){assert(loaded && "Resource is unloaded!");return *manager.resourceMap[name].second;}

};

