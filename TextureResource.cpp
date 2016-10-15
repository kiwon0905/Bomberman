#include "TextureResource.h"


TextureResourceManager TextureResource::manager=TextureResourceManager();

TextureResource::TextureResource(std::string name):Resource(name)
{
	load(name);
}

TextureResource::TextureResource(const TextureResource & t)
{
	this->name=t.name;
	this->loaded=t.loaded;
	this->sprite=t.sprite;

	//Load it if this needs to be loaded
	if(loaded)
		load(name);
}

TextureResource& TextureResource::operator=(const TextureResource& t)
{
	if(this==&t)
		return *this;
	//destroy the previous resource
	if(loaded)
		manager.destroy(this->name);

	this->name=t.name;
	this->loaded=t.loaded;
	this->sprite=t.sprite;
	if(loaded)
		load(name);
	return *this;
}

void TextureResource::load(std::string name_)
{
	loaded=true;
	name=name_;
	if(manager.create(name))
		manager.resourceMap[name].second->loadFromFile(name);
	sprite.setTexture(*manager.resourceMap[name].second);
}

TextureResource::~TextureResource()
{
	if(loaded)
		manager.destroy(name);
}



