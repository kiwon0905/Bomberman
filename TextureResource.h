#pragma once
#include "resource.h"
#include <SFML\Graphics.hpp>
#include "TextureResourceManager.h"

class TextureResource :public Resource
{
public:
	static TextureResourceManager manager;
	sf::Sprite sprite;
public:
	TextureResource():Resource(){};
	TextureResource(std::string name);
	TextureResource(const TextureResource &);
	TextureResource& operator=(const TextureResource&);
	virtual void load(std::string name);
	~TextureResource();
	sf::Sprite& operator()(){assert(loaded && "Resource is unloaded!");return sprite;}

};

