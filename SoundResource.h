#pragma once
#include "resource.h"
#include "SoundResourceManager.h"


class SoundResource :public Resource
{
private:
	static SoundResourceManager manager;
	sf::Sound sound;
public:
	SoundResource():Resource(){};
	SoundResource(std::string name);
	SoundResource(const SoundResource&);
	SoundResource& operator=(const SoundResource&);
	virtual void load(std::string name);
	~SoundResource();
	sf::Sound& operator()(){assert(loaded && "Resource is unloaded!");return sound;}
};

