#pragma once
#include "Timer.h"
#include <SFML\Graphics.hpp>


class Animation
{
private:
	sf::Sprite * sprite;
	sf::Vector2i spriteSize;
	sf::Vector2i frameCount;
	sf::Vector2i currentFrame;
	sf::Vector2i frameSize;
	bool active;
	double switchTime;
	double timeSoFar;
public:
	void update(float dt);
	void start(){active=true;}
	void stop(){active=false;}
	void setY(int y){currentFrame.y=y;}

	Animation(){};
	Animation(sf::Sprite * sprite, sf::Vector2i spriteSize, sf::Vector2i frameCount, double switchTime);
	~Animation();


};

