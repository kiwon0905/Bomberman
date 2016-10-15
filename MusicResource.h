#pragma once
#include "resource.h"
#include "MusicResourceManager.h"

class MusicResource :public Resource
{
private:
	static MusicResourceManager manager;
public:
	MusicResource():Resource(){};
	MusicResource(std::string name);
	MusicResource(const MusicResource &);
	MusicResource& operator=(const MusicResource&);
	virtual void load(std::string name);
	~MusicResource();
	sf::Music& operator()(){assert(loaded && "Resource is unloaded!");return *manager.resourceMap[name].second;}
};
