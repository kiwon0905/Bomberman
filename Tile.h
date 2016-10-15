#pragma once
#include <list>
#include <SFML\System.hpp>
#include "TextureResource.h"
#include <set>
#include "Timer.h"
//#include "Bomb.h"
class Entity;
class Explosion;
class Item;
class Tile
{
private:
	sf::Vector2i location;
	std::set<Entity*> entities;//List of entities that are in this tile
	std::set<Explosion*> explosions;
	std::set<Item*> items;
	Timer sinceLastBombExploded;
public:
	std::set<Entity*>& getEntities(){return entities;}
	bool canPlaceBomb(){return sinceLastBombExploded.getElapsedTime()>0.1;}
	void onEnter(Entity * e);
	void onExit(Entity * e);
	void onExplosion(Explosion* e);
	void onExplosionExit(Explosion* e){explosions.erase(e);}
	void onItem(Item * i);
	void onItemExit(Item * i);


	void draw(sf::RenderWindow & w);
	bool isPassable();
	bool isEmpty(){return entities.empty();}
	Tile(){};
	Tile(int x, int y);



	virtual ~Tile();
};

