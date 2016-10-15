#include "Block.h"
#include "Character.h"

int rand(int low, int high){return rand () % (high - low + 1) + low;}

Item::Item(int x, int y, GameWorld * g):gameWorld(g), loc(x, y), life(2), alive(true)
{
	type=static_cast<ItemType>(rand(0, static_cast<int>(ItemType::nITEM)-1));
	std::string name;
	std::cout<<"\n"<<int(type)<<"\n";
	if(type==ItemType::RANGE)
		name="C:/Users/Park/Desktop/Newfolder/item-range.png";
	else if(type==ItemType::BOMB)
		name="C:/Users/Park/Desktop/Newfolder/item-bomb.png";
	else if(type==ItemType::SPEED)
		name="C:/Users/Park/Desktop/Newfolder/item-speed.jpg";
	sprite.load(name);
	sprite().setPosition(104+loc.x*51, loc.y*48+8);
	gameWorld->getGameMap().onItem(loc.x, loc.y, this);
}
void Item::use(Character * c)
{
	switch (type)
	{
	case ItemType::RANGE:
		c->power++;
		break;
	case ItemType::SPEED:
		c->speed+=35;
		break;
	case ItemType::BOMB:
		c->nBomb++;
		break;
	default:
		break;
	}
	alive=false;
}
Item::~Item()
{
	gameWorld->getGameMap().onItemExit(loc.x, loc.y, this);
	std::cout<<"ITEM DESTRORED!";
}

void Item::draw(sf::RenderWindow & window)
{
	window.draw(sprite());
}



Block::Block(EntityType type, std::string name, int x, int y):
	Entity(x, y, type)
{
	sprite.load(name);
	sprite().setPosition(static_cast<float>(104+x*51), static_cast<float>(8+y*48));
	boundingRect=sprite().getGlobalBounds();
}
Block::~Block()
{
	gameWorld->getGameMap().onExit(currentLoc.x, currentLoc.y, this);
}

void Block::tick(float dt, GameWorld * g)
{
}

void Block::draw(sf::RenderWindow & w)
{
	w.draw(sprite());
	sf::RectangleShape rect;
	rect.setPosition(boundingRect.left, boundingRect.top);
	rect.setSize(sf::Vector2f(boundingRect.width, boundingRect.height));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(1);
	w.draw(rect);
}

void Block::gotHit()
{
	if(type!=EntityType::PERMANENT_BLOCK)
	{
		alive=false;
		if(rand(1,5)<=2)
			gameWorld->createItem(currentLoc.x, currentLoc.y);
	}
}