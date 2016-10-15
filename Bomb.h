#pragma once
#include "entity.h"
#include "TextureResource.h"
#include "Timer.h"
#include "SoundResource.h"


class Explosion
{
	Timer timer;
	GameWorld * gameWorld;
public:
	Explosion(int x, int y, GameWorld * g):gameWorld(g)
	{
		loc.x=x; loc.y=y; gameWorld->getGameMap().onExplosion(loc.x, loc.y, this);
	}
	~Explosion()
	{
		gameWorld->getGameMap().onExplosionExit(loc.x, loc.y, this);
	}
	bool expired();
	void draw(sf::RenderWindow & w);
	sf::Vector2i loc;
};



class Bomb :public Entity
{
public:	
	static void init();
	static void exit();
private:
	//All bomb objects share the textures
	int range;
	bool exploded;
	static std::vector<sf::RectangleShape> list;
	static TextureResource * bombSprites;
	static SoundResource * explosionSound;
	Timer timer;

	Character * owner;
	
	void explode();

	virtual void gotHit();
public:

	Bomb(int x, int y, int r, Character * owner);
	virtual ~Bomb();

	int getRange(){return range;}
	virtual void tick(float dt,  GameWorld * g);
	virtual void draw(sf::RenderWindow & w);
};

