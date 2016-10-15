#include "Bomb.h"
#include "GameWorld.h"
#include "Character.h"

TextureResource * Bomb::bombSprites=nullptr;
SoundResource * Bomb::explosionSound=nullptr;
std::vector<sf::RectangleShape> Bomb::list=std::vector<sf::RectangleShape>();



 
void Explosion::draw(sf::RenderWindow & w)
{

	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f( 51, 48));
	rect.setFillColor(sf::Color::Magenta);
	rect.setOutlineColor(sf::Color::Black);
	rect.setPosition(104+loc.x*51, 8+loc.y*48);
	w.draw(rect);
	
}

void Bomb::init()
{
	bombSprites=new TextureResource("C:/Users/Park/Desktop/Newfolder/Blocks/darkgray.png");
	explosionSound=new SoundResource("C:/Users/Park/Desktop/Newfolder/Music/Bomb.wav");
}
void Bomb::exit()
{
	delete bombSprites;
	delete explosionSound;
}

Bomb::Bomb(int x, int y, int r, Character * owner_): Entity(x, y, EntityType::BOMB),range(r), exploded(false), owner(owner_)
{
	sprite=*bombSprites;
	sprite().setPosition(static_cast<float>(104+x*51), static_cast<float>(8+y*48));
	boundingRect=sprite().getGlobalBounds();
}

Bomb::~Bomb()
{
	(*explosionSound)().play();
	gameWorld->getGameMap().onExit(currentLoc.x, currentLoc.y, this);
}

void Bomb::explode()
{
	exploded=true;
	for(auto tile: gameWorld->getGameMap().getAllPossibleTilesWithin(currentLoc.x, currentLoc.y, range))
	{
		gameWorld->createExplosion(tile.x, tile.y);
	}
	alive=false;
	owner->nBomb++;
}

void Bomb::tick(float dt,  GameWorld * g)
{
	if(timer.getElapsedTime()>=3 && !exploded)
		explode();
}


void Bomb::draw(sf::RenderWindow & w)
{
	w.draw(sprite());
}


bool Explosion::expired()
{
	return timer.getElapsedTime()>0.3;
}


void Bomb::gotHit()
{
	
}