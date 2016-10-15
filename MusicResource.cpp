#include "MusicResource.h"

MusicResourceManager MusicResource::manager=MusicResourceManager();


MusicResource::MusicResource(std::string name):Resource(name)
{
	//if(manager.create(name)) //map the resource
		//manager.resourceMap[name].second->openFromFile(name); //load the resource if needed
	load(name);
}

MusicResource::MusicResource(const MusicResource & m)
{
	this->name=m.name;
	this->loaded=m.loaded;
	if(loaded)
		load(name);
}
MusicResource& MusicResource::operator=(const MusicResource & m)
{
	if(this==&m)
		return *this;
	if(loaded)
		manager.destroy(this->name);
	this->name=m.name;
	this->loaded=m.loaded;
	if(loaded)
		load(name);
	return *this;
}

void MusicResource::load(std::string name_)
{
	loaded=true;
	name=name_;
	if(manager.create(name)) //map the resource
		manager.resourceMap[name].second->openFromFile(name); //load the resource if needed
}
MusicResource::~MusicResource()
{
	if(loaded)
		manager.destroy(name);
}


