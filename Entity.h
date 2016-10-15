#pragma once
#include "object.h"
#include <SFML\Graphics.hpp>
#include "TextureResource.h"
#include "EntityType.h"
#include "GameWorld.h"

class GameWorld;
class Entity :public Object
{
protected:
	bool alive;
	EntityType type;
	sf::Vector2i currentLoc;
	TextureResource sprite;
	static GameWorld * gameWorld;
	sf::FloatRect boundingRect;
public:
	static void init(GameWorld * g){gameWorld=g;}
public:
	Entity::Entity(int x, int y, EntityType type_);
	virtual ~Entity();
	EntityType getType(){return type;}
	bool isAlive(){return alive;}
	void setAlive(bool alive_){alive=alive_;}
	sf::FloatRect& getBoundingRect(){return boundingRect;}
	sf::Vector2i& getLoc(){return currentLoc;}
	bool operator==(const Entity & e){return this->id==e.id;}

	virtual void tick(float dt, GameWorld * g)=0;
	virtual void draw(sf::RenderWindow & w)=0;
	
	virtual void gotHit()=0;
};

