#pragma once
#include <SFML\Graphics.hpp>
#include <SFML/Window.hpp>

template<class T>
class State
{
public:
	virtual void enter(T*)=0;
	virtual void handleEvent(const sf::Event & event, T* owner)=0;
	virtual void tick(T*, float dt)=0;
	virtual void draw(sf::RenderWindow & window)=0;
	virtual void exit(T*)=0;

	State(){};
	virtual ~State(){};
};

