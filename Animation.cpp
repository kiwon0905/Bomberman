#include "Animation.h"
#include <SFML\Graphics.hpp>
#include <iostream>

Animation::Animation(sf::Sprite * sprite_, sf::Vector2i spriteSize_, sf::Vector2i frameCount_, double switchTime_):
	sprite(sprite_), spriteSize(spriteSize_), frameCount(frameCount_), active(false), switchTime(switchTime_), timeSoFar(0)
{
	frameSize.x=spriteSize.x/frameCount.x;
	frameSize.y=spriteSize.y/frameCount.y;
}

Animation::~Animation()
{
}

void Animation::update(float dt)
{
	if(active)
	{
		timeSoFar+=dt;
		if(timeSoFar>=switchTime)//switch the frame 
		{
			currentFrame.x=(currentFrame.x+1)%frameCount.x;
			timeSoFar=0;
			sprite->setTextureRect(sf::IntRect(currentFrame.x * frameSize.x, currentFrame.y * frameSize.y, frameSize.x, frameSize.y));
		}
	}
}
