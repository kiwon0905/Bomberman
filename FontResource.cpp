#include "FontResource.h"

FontResourceManager FontResource::manager=FontResourceManager();


FontResource::FontResource(std::string name):Resource(name)
{
	//if(manager.create(name))
		//manager.resourceMap[name].second->loadFromFile(name);
	load(name);
}

FontResource::FontResource(const FontResource & f)
{
	this->name=f.name;
	this->loaded=f.loaded;
	if(loaded)
		load(name);
}
FontResource& FontResource::operator=(const FontResource & f)
{
	if(this==&f)
		return *this;
	if(loaded)
		manager.destroy(this->name);
	this->name=f.name;
	this->loaded=f.loaded;
	if(loaded)
		load(name);
	return *this;
}

void FontResource::load(std::string name_)
{
	loaded=true;
	name=name_;
	if(manager.create(name))
		manager.resourceMap[name].second->loadFromFile(name);
}

FontResource::~FontResource()
{
	if(loaded)
		manager.destroy(name);
}
