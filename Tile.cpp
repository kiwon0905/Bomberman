#include "Tile.h"
#include "Entity.h"
#include <algorithm>
#include "Block.h"
#include "Character.h"


Tile::Tile(int x, int y):location(x, y)
{
	
}

Tile::~Tile()
{
}

void Tile::onExplosion(Explosion* e)
{
	explosions.insert(e); 
	for(auto ent: entities) 
		ent->gotHit();
	for(auto i: items)
		i->kill();
}



bool Tile::isPassable()
{
	if(!entities.empty())
		for(auto e: entities)
		{
			switch(e->getType())
			{
			case EntityType::BOMB:
			case EntityType::PERMANENT_BLOCK:
			case EntityType::SEMIPERMANENT_BLOCK:
				return false;
			default:
				continue;
			}
		}
	return true;
}
void Tile::onEnter(Entity * e)
{
	if(!explosions.empty())//if there is a explpsion
		e->gotHit();
	else 
		entities.insert(e);

	if(!items.empty() && e->getType()==EntityType::CHARACTER)
	{
		std::cout<<"CHaracter used item!";
		(*items.begin())->use(static_cast<Character*>(e));
	}

}

void Tile::onExit(Entity * e)
{
	entities.erase(e);
	if(e->getType()==EntityType::BOMB)
		sinceLastBombExploded.restart();
}

void Tile::onItem(Item * i)
{	
	items.insert(i);
}
void Tile::onItemExit(Item * i)
{
	items.erase(i);
}