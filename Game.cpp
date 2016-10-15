#include "Game.h"
#include "GameMenuState.h"
#include "Timer.h"
#include <iostream>
#include "FPS.h"
#include <thread>
Game::Game():stateMachine(this, new GameMenuState()), running(true), window(sf::VideoMode(1024, 688), "My Window")
{
	//window.setVerticalSyncEnabled(true);
}


Game::~Game()
{
}

void Game::run()
{
	Timer timer;
	FPS fpsCounter;
	int frames=0;
	while(running)
	{
		
		//===========Process Event=========//
		sf::Event event;
		while(window.pollEvent(event))
		{  
			if(event.type==sf::Event::Closed)
				running=false;
			stateMachine.handleEvent(event, this);
		}
		//=================================//
		double dt=timer.getElapsedTime();
		timer.restart();
		stateMachine.tick(static_cast<float>(dt));

		window.clear();
		stateMachine.draw(window);
		window.display();
	}
}
