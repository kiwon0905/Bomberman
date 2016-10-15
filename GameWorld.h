#pragma once
#include "Tile.h"
#include "GameMap.h"

class Character;
class Block;
class Bomb;
class Item;
class Explosion;


class GameWorld
{
private:
	//std::vector<Item*> items;
	std::list<Character *> characters;
	std::list<Block *> blocks;
	std::list<Bomb *> bombs;
	std::list<Explosion *> explosions;
	std::list<Item *> items;

	GameMap  gameMap;
	struct vecSort{
		bool operator()(const sf::Vector2i & v1, const sf::Vector2i & v2){return (v1.x+v1.y)>(v1.x+v1.y);}
	};
	std::set<sf::Vector2i, vecSort> bombArea;

	
public:

	void handleEvent(const sf::Event & event);
	void tick(float dt);
	void draw(sf::RenderWindow & w);
	
	
	GameMap& getGameMap(){return gameMap;}

	void createBomb(int x, int y, int r, Character * owner);
	void createBlock(EntityType type, std::string sprite, int x, int y);
	void createExplosion(int x, int y);
	void createItem(int x, int y);

	GameWorld();
	~GameWorld();
};

