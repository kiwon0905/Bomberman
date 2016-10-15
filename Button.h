#pragma once
#include <SFML/Graphics.hpp>
#include <functional>

class Button
{
private:
	sf::Text text;
	sf::Sprite * sprite;
	bool isPreviousIn;
	bool isCurrentIn;
	bool clicked;
	bool entered;
	bool exited;
	bool changed;
	sf::FloatRect rect;
	sf::RenderWindow * window;
public:
	Button();
	~Button();

	void setWindow(sf::RenderWindow & window){this->window=&window;}

	bool isChanged(){return entered||exited||clicked;}
	bool isEntered(){return entered;}
	bool isExited(){return exited;}
	bool isClicked(){return clicked;}
	
	sf::Sprite& getSprite(){return *sprite;}
	sf::Text& getText(){return text; }
	
	void setClickArea(sf::FloatRect area){rect=area;}
	void addSprite(sf::Sprite & sprite){this->sprite=&sprite;}
	void update(const sf::Event & event);
	void draw();
};

