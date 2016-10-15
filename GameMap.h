#pragma once
#include <string>
#include "TextureResource.h"
#include <SFML\Graphics.hpp>
#include "EntityType.h"
#include "Tile.h"
#include <array>
#include "MusicResource.h"
class GameWorld;
class GameMap
{
private:
	TextureResource background;//Texture for background 
	std::array<std::array<Tile, 16>, 14> tiles;
	std::vector<Entity*> queryList;
	std::vector<sf::Vector2i> queryVec;
	sf::FloatRect queryRect;
	MusicResource bgm;
	//x=16, y=14
	void loadBackground(std::ifstream & );
	void readBlockInfo(std::ifstream & fin, std::map<int, std::pair<std::string, EntityType>>&);
	void loadBlocks(std::ifstream & fin, std::map<int, std::pair<std::string, EntityType>>&, GameWorld * );
public:
	void load(std::string name, GameWorld * );
	void onEnter(int x, int y, Entity *); //called when an entity enters this tile
	void onExit(int x, int y, Entity *); //called when an entity exits this tile
	void draw(sf::RenderWindow & w);
	bool isPassable(int x, int y);
	bool canPlaceBomb(int x, int y){return tiles[y][x].canPlaceBomb() && tiles[y][x].isPassable();}
	sf::FloatRect& getBoundary(int x, int y);

	std::vector<Entity*>& getAllEntitiesWithin(int x, int y, int r);
	std::vector<sf::Vector2i>& getAllPossibleTilesWithin(int x, int y, int r);
	std::vector<Entity*>& getEntitiesOn(int x, int y);

	void onExplosion(int x, int y, Explosion * e);
	void onExplosionExit(int x, int y, Explosion * e);
	void onItem(int x, int y, Item *e );
	void onItemExit(int x, int y, Item *e);

	void bomb();

	GameMap();
	~GameMap();
};

