#include "GameWorld.h"
#include "Character.h"
#include "Bomb.h"
#include "Character.h"
#include "Block.h"
#include "GameMap.h"
#include <algorithm>

GameWorld::GameWorld()
{
	Entity::init(this);
	Character::init();
	Bomb::init();
	Character* e=new Character(1, 1, "HI", CharacterType::BLACK, sf::Keyboard::Left, sf::Keyboard::Up, sf::Keyboard::Down, sf::Keyboard::Right, sf::Keyboard::Space);
	characters.push_back(e);
	Character * e2=new Character(1, 3, "JORDI", CharacterType::BLACK, sf::Keyboard::A, sf::Keyboard::W, sf::Keyboard::S, sf::Keyboard::D, sf::Keyboard::LShift);
	characters.push_back(e2);
	gameMap.load("C:/Users/Park/Desktop/Newfolder/Map Files/Plain_1.gmap", this);
}
GameWorld::~GameWorld()
{	
	Character::exit();
	Bomb::exit();
	for(auto c:characters)
		delete c;
	for(auto b:blocks)
		delete b;
	for(auto b:bombs)
		delete b;
}

void GameWorld::handleEvent(const sf::Event & event)
{

}

void GameWorld::tick(float dt)
{

	for(auto iter=bombs.begin(); iter!=bombs.end();)
	{
		if((*iter)->isAlive())//if the entity is in the cancel list
		{
			(*iter)->tick(dt, this);
			++iter;
		}
		else//THe bomb must explode
		{
			delete *iter;
			iter=bombs.erase(iter);
		}
	}
	for(auto iter=characters.begin(); iter!=characters.end();)
	{
		if((*iter)->isAlive())
		{
			(*iter)->tick(dt, this);
			++iter;
		}
		else
		{
			delete *iter;
			iter=characters.erase(iter);
		}
	}
	for(auto iter=blocks.begin(); iter!=blocks.end();)
	{
		if((*iter)->isAlive())
		{
			(*iter)->tick(dt, this);
			++iter;
		}
		else
		{
			delete *iter;
			iter=blocks.erase(iter);
		}
	}
	for(auto iter=explosions.begin(); iter!=explosions.end();)
	{
		if((*iter)->expired())
		{
			delete (*iter);
			iter=explosions.erase(iter);
		}
		else
			++iter;
	}

	for(auto iter=items.begin(); iter!=items.end();)
	{
		if((*iter)->isDead())
		{
			delete (*iter);
			iter=items.erase(iter);
		}
		else
			++iter;
	}
	
}
void GameWorld::draw(sf::RenderWindow & w)
{
	gameMap.draw(w);
	for(auto b:blocks)
		b->draw(w);	
	for(auto b:bombs)
		b->draw(w);
	for(auto e: explosions)
		e->draw(w);
	for(auto i: items)
		i->draw(w);
	for(auto c:characters)
		c->draw(w);
}

	
void GameWorld::createBomb(int x, int y, int r, Character * owner)
{
	bombs.push_back(new Bomb(x, y, r, owner));
}

void GameWorld::createBlock(EntityType type, std::string sprite, int x, int y)
{
	blocks.push_back(new Block(type, sprite, x, y));

}

void GameWorld::createExplosion(int x, int y)
{
	explosions.push_back(new Explosion(x, y, this));
}

void GameWorld::createItem(int x, int y)
{
	items.push_back(new Item(x, y, this));
}