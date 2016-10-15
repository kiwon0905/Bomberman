#pragma once
#include "StateMachine.h"
#include <SFML/Graphics.hpp>
//The main game engine class
class Game
{
private:
	bool running;
	//StateMachine for gameState-Menu, Playing
	StateMachine<Game> stateMachine;

	//Graphics context
	sf::RenderWindow window;
public:
	bool isRunning(){return running;}
	void setRunning(bool on_off){running=on_off;}
	sf::RenderWindow& getWindow(){return window;}
	void run();

	StateMachine<Game>& getFSM(){return stateMachine;}
	
	Game();
	~Game();
};

