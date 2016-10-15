#pragma once
#include "entity.h"
#include "TextureResource.h"
#include "Animation.h"
#include <SFML\Graphics.hpp>
#include "Timer.h"
enum class CharacterType{BLACK, SILVER, GRAY, YELLOW, ORANGE};
class Character :public Entity
{
public:	
	static void init();
	static void exit();
private:
	//All character objects share the textures
	static TextureResource * characterSprites;
private:
	Timer sinceLastBomb;
	std::string name;
	Animation animation;
	
	//Locations on the tile
	
	sf::Vector2i previousLoc;
	
	sf::Keyboard::Key leftKey;
	sf::Keyboard::Key rightKey;
	sf::Keyboard::Key upKey;
	sf::Keyboard::Key downKey;
	sf::Keyboard::Key bombKey;

	void move(float x, float y);
	void handleCollision(GameWorld * g);
	void syncGeometry();
public:
	Character(int x, int y, std::string name_, CharacterType type, sf::Keyboard::Key left, sf::Keyboard::Key up, sf::Keyboard::Key down, sf::Keyboard::Key right, sf::Keyboard::Key bomb);
	virtual ~Character();

	virtual void tick(float dt, GameWorld * g);
	virtual void draw(sf::RenderWindow & w);

	virtual void gotHit();

	int nBomb;
	int power;
	float speed;
};

