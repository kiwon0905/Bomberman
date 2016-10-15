#include "SoundResource.h"

SoundResourceManager SoundResource::manager=SoundResourceManager();

SoundResource::SoundResource(std::string name):Resource(name)
{	
	load(name);
}

SoundResource::SoundResource(const SoundResource & s)
{
	this->name=s.name;
	this->sound=s.sound;
	this->loaded=s.loaded;
	if(loaded)
		load(name);
}

SoundResource& SoundResource::operator=(const SoundResource & s)
{
	if(this==&s)
		return *this;
	if(loaded)
		manager.destroy(this->name);
	this->name=s.name;
	this->sound=s.sound;
	this->loaded=s.loaded;
	if(loaded)
		load(name);
	return *this;
}

void SoundResource::load(std::string name_)
{
	loaded=true;
	name=name_;
	if(manager.create(name))
		manager.resourceMap[name].second->loadFromFile(name);
	sound.setBuffer(*manager.resourceMap[name].second);	
}

SoundResource::~SoundResource()
{
	if(loaded)
		manager.destroy(name);
}
