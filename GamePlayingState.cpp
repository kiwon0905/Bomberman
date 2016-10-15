#include "GamePlayingState.h"
#include "GameMenuState.h"
#include <iostream>
#include "Game.h"


GamePlayingState::GamePlayingState():State<Game>(), gameWorld()
{
	font.load("C:/Users/Park/Desktop/Newfolder/Fonts/Ubuntu-L.TTF");
	menuSound.load("C:/Users/Park/Desktop/Newfolder/Music/button.wav");
}


GamePlayingState::~GamePlayingState()
{
}


void GamePlayingState::enter(Game* g)
{
	backButton.setWindow(g->getWindow());
	backButton.getText().setString("Back");
	backButton.getText().setFont(font());
	backButton.getText().setCharacterSize(30);
	backButton.getText().setColor(sf::Color::Blue);
	backButton.setClickArea(backButton.getText().getGlobalBounds());
}
void GamePlayingState::handleEvent(const sf::Event & event, Game * g)
{
	backButton.update(event);
	if(backButton.isEntered())
	{
		menuSound().play();
		backButton.getText().setCharacterSize(40);
	}
	else if(backButton.isClicked())
	{
		g->getFSM().changeState(new GameMenuState());
	}
	else if(backButton.isExited())
	{
		backButton.getText().setCharacterSize(30);
	}
	gameWorld.handleEvent(event);
}
void GamePlayingState::tick(Game* g, float dt)
{
	gameWorld.tick(dt);
}
void GamePlayingState::draw(sf::RenderWindow & window)
{
	backButton.draw();
	gameWorld.draw(window);
}

void GamePlayingState::exit(Game* g)
{

}