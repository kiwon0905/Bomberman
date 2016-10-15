#include "Character.h"
#include <iostream>
#include <cmath>
#include <SFML/Window.hpp>
#include "GameWorld.h"
#include "Bomb.h"
#include "GameMap.h"

TextureResource* Character::characterSprites=nullptr;


void Character::init()
{
	characterSprites=new TextureResource[4];
	characterSprites->load("C:/Users/Park/Desktop/Newfolder/Characters/Character1.png");
	(characterSprites+1)->load("C:/Users/Park/Desktop/Newfolder/Characters/Character2.png");
	(characterSprites+2)->load("C:/Users/Park/Desktop/Newfolder/Characters/Character3.png");
	(characterSprites+3)->load("C:/Users/Park/Desktop/Newfolder/Characters/Character4.png");
}

void Character::exit()
{
	delete[] characterSprites;
}

Character::Character(int x, int y,std::string name_, CharacterType type, sf::Keyboard::Key left, sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key right, sf::Keyboard::Key bomb):
	name(name_), Entity(x, y, EntityType::CHARACTER), nBomb(1), power(1), leftKey(left), upKey(up), downKey(down), rightKey(right), bombKey(bomb)
{
	sprite=characterSprites[0];
	sprite().setOrigin(16, 34);
	sprite().setTextureRect(sf::IntRect(0, 0, 32, 34));
	sprite().setScale(1.7f, 1.7f);
	
	boundingRect.left=static_cast<float>(104+51*x);
	boundingRect.top=static_cast<float>(8+48*y);
	boundingRect.height=static_cast<float>(8);
	boundingRect.width=static_cast<float>(24);
	speed=200;
	animation=Animation(&sprite(), sf::Vector2i(96, 136), sf::Vector2i(3, 4), 0.1); 
}


Character::~Character()
{
	gameWorld->getGameMap().onExit(currentLoc.x, currentLoc.y, this);
}

void Character::move(float x, float y)
{
	boundingRect.left+=x;
	boundingRect.top+=y;
}

void Character::syncGeometry()
{
	sprite().setPosition(boundingRect.left+boundingRect.width/2, boundingRect.top+boundingRect.height/2);
}

void Character::handleCollision(GameWorld * g)
{
	//left
	if(currentLoc.x!=0)
	{
		if(!g->getGameMap().isPassable(currentLoc.x-1, currentLoc.y) && boundingRect.intersects(g->getGameMap().getBoundary(currentLoc.x-1, currentLoc.y)))
			move(g->getGameMap().getBoundary(currentLoc.x-1, currentLoc.y).left+51 -boundingRect.left, 0);
	}
	//right
	if(currentLoc.x!=15)
	{
		if(!g->getGameMap().isPassable(currentLoc.x+1, currentLoc.y) && boundingRect.intersects(g->getGameMap().getBoundary(currentLoc.x+1, currentLoc.y)))
			move(g->getGameMap().getBoundary(currentLoc.x+1, currentLoc.y).left-(boundingRect.left+boundingRect.width), 0);
	}
	
	if(currentLoc.y!=0)
	{
		if(!g->getGameMap().isPassable(currentLoc.x, currentLoc.y-1) && boundingRect.intersects(g->getGameMap().getBoundary(currentLoc.x, currentLoc.y-1)))
			move(0, (g->getGameMap().getBoundary(currentLoc.x, currentLoc.y-1).top+g->getGameMap().getBoundary(currentLoc.x, currentLoc.y-1).height)-boundingRect.top);
	}
	if(currentLoc.y!=13)
	{
		if(!g->getGameMap().isPassable(currentLoc.x, currentLoc.y+1) && boundingRect.intersects(g->getGameMap().getBoundary(currentLoc.x, currentLoc.y+1)))
			move(0, g->getGameMap().getBoundary(currentLoc.x, currentLoc.y+1).top-(boundingRect.top+boundingRect.height));
	}
}

void Character::tick(float dt, GameWorld * g)
{
	if(speed>350)
		speed=350;
		animation.start();
		if(sf::Keyboard::isKeyPressed(leftKey))
		{
			if(boundingRect.left+(-speed*dt)>104)
				move(-speed*dt, 0);
			animation.setY(1);
		}
		else if(sf::Keyboard::isKeyPressed(upKey))
		{
			if(boundingRect.top+(-speed*dt)>8)
				move(0, -speed*dt);
			animation.setY(3);
		}
		else if(sf::Keyboard::isKeyPressed(rightKey))
		{
			if(boundingRect.left+boundingRect.width+speed*dt<920)
				move(speed*dt, 0);
			animation.setY(2);
		}
		else if(sf::Keyboard::isKeyPressed(downKey))
		{
			if(boundingRect.top+boundingRect.height+speed*dt<680)
				move(0, speed*dt);
			animation.setY(0);
		}
		else 
			animation.stop();
		 
		handleCollision(g);

	previousLoc=currentLoc;
	currentLoc.x=static_cast<int>(std::floor(   16*((boundingRect.left+(boundingRect.width/2)-104)/816)) );
	currentLoc.y=static_cast<int>(std::floor(   14*((boundingRect.top+(boundingRect.height/2)-8)/672)));

	syncGeometry();
	animation.update(dt);
	//Place bomb
	if(sf::Keyboard::isKeyPressed(bombKey))
	{
		if(sinceLastBomb.getElapsedTime()>0.25 && gameWorld->getGameMap().canPlaceBomb(currentLoc.x, currentLoc.y) && nBomb>0)
		{
			gameWorld->createBomb(currentLoc.x, currentLoc.y, power, this);
			sinceLastBomb.restart();
			nBomb--;
		}
	
	}


	if(previousLoc!=currentLoc)
	{
		gameWorld->getGameMap().onEnter(currentLoc.x, currentLoc.y, this);
		gameWorld->getGameMap().onExit(previousLoc.x, previousLoc.y, this);
	}
}

void Character::draw(sf::RenderWindow & w)
{
	
	w.draw(sprite());

	//DEBUG
	static std::vector<sf::RectangleShape> list;
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
	{
		for(auto tile: gameWorld->getGameMap().getAllPossibleTilesWithin(currentLoc.x, currentLoc.y, 4))
		{
			sf::RectangleShape rect;
			rect.setSize(sf::Vector2f( 51, 48));
			rect.setFillColor(sf::Color::Magenta);
			rect.setOutlineColor(sf::Color::Black);
			rect.setPosition(104+tile.x*51, 8+tile.y*48);
			list.push_back(rect);
		}
	}
	for(auto& r: list)
		w.draw(r);
	list.clear();


	//DEBUG
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f(boundingRect.width, boundingRect.height));
	rect.setPosition(boundingRect.left, boundingRect.top);
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineColor(sf::Color::Black);
	rect.setOutlineThickness(1);
	
	w.draw(rect);
}

void Character::gotHit()
{
	std::cout<<"I got hit\n";
	alive=false;
}