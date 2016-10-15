#include "Button.h"
#include <SFML/Window.hpp>

Button::Button():clicked(false), entered(false), exited(false), sprite(nullptr)
{
}

Button::~Button()
{
}

void Button::update(const sf::Event & event)
{
	sf::Vector2i mousePos=sf::Mouse::getPosition(*window);
	isPreviousIn=isCurrentIn;

	if(rect.left<=mousePos.x && mousePos.x<=rect.left+rect.width && rect.top<=mousePos.y && mousePos.y<=rect.top+rect.height)
	{
		isCurrentIn=true;
		clicked=event.type==sf::Event::MouseButtonReleased;
	}
	else 
		isCurrentIn=false;
	if(isCurrentIn==true && isPreviousIn==false)
		entered=true;
	else
		entered=false;
	if(isCurrentIn==false && isPreviousIn==true)
		exited=true;
	else
		exited=false;

}



void Button::draw()
{
	window->draw(text);
	if(sprite!=nullptr)
		window->draw(*sprite);
}