#include "Entity.h"

GameWorld* Entity::gameWorld=nullptr;

Entity::Entity(int x, int y, EntityType type_):currentLoc(x, y), type(type_)
{
	gameWorld->getGameMap().onEnter(x, y, this);
}

Entity::~Entity()
{
	gameWorld->getGameMap().onExit(currentLoc.x, currentLoc.y, this);
}