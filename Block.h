#pragma once
#include "entity.h"
#include "TextureResource.h"
#include <SFML\System.hpp>


class Block :public Entity
{
private:
	TextureResource sprite;
public:
	Block(EntityType type, std::string spriteName, int x, int y);
	virtual ~Block();

	virtual void tick(float dt, GameWorld * g);
	virtual void draw(sf::RenderWindow & w);

	virtual void gotHit();
};

enum class ItemType{RANGE, SPEED, BOMB, nITEM};

class Item
{
private:
	ItemType type;
	GameWorld * gameWorld;
	sf::Vector2i loc;
	bool alive;
	TextureResource sprite;
	int life;
public:
	Item(int x, int y, GameWorld * g);
	~Item();
	void kill(){life--; if(life==0) alive=false;}
	bool isDead(){return !alive;}
	void draw(sf::RenderWindow & window);
	void use(Character * c);
};
