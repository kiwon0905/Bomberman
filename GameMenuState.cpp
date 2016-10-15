#include "GameMenuState.h"
#include "GamePlayingState.h"
#include "GameSettingState.h"
#include "GameCreditState.h"
#include <iostream>
#include <fstream>
#include "Game.h"



GameMenuState::GameMenuState():State<Game>()
{
	font.load("C:/Users/Park/Desktop/Newfolder/Fonts/Ubuntu-L.TTF");
	menuSound.load("C:/Users/Park/Desktop/Newfolder/Music/button.wav");
}


GameMenuState::~GameMenuState()
{

}

void GameMenuState::enter(Game* g)
{
	std::string dummy;
	std::ifstream fin("C:/Users/Park/Desktop/Newfolder/setting.txt");
	fin>>dummy;
	int soundLevel;
	fin>>soundLevel;
	fin.close();
	sf::Listener::setGlobalVolume(static_cast<float>(soundLevel));

	playButton.setWindow(g->getWindow());
	quitButton.setWindow(g->getWindow());
	settingButton.setWindow(g->getWindow());
	creditButton.setWindow(g->getWindow());

	playButton.getText().setString("Play!");
	playButton.getText().setFont(font());
	playButton.getText().setCharacterSize(50);
	playButton.getText().setColor(sf::Color::Blue);
	playButton.getText().setPosition(300, 300);
	playButton.setClickArea(playButton.getText().getGlobalBounds());

	quitButton.getText().setString("Quit");
	quitButton.getText().setFont(font());
	quitButton.getText().setCharacterSize(50);
	quitButton.getText().setColor(sf::Color::Blue);
	quitButton.getText().setPosition(300, 500);
	quitButton.setClickArea(quitButton.getText().getGlobalBounds());

	settingButton.getText().setString("Setting");
	settingButton.getText().setFont(font());
	settingButton.getText().setCharacterSize(50);
	settingButton.getText().setColor(sf::Color::Blue);
	settingButton.getText().setPosition(300, 400);
	settingButton.setClickArea(settingButton.getText().getGlobalBounds());

	creditButton.getText().setString("Credits");
	creditButton.getText().setFont(font());
	creditButton.getText().setCharacterSize(50);
	creditButton.getText().setColor(sf::Color::Blue);
	creditButton.getText().setPosition(500, 300);
	creditButton.setClickArea(creditButton.getText().getGlobalBounds());
}

void GameMenuState::handleEvent(const sf::Event & event, Game * g)
{
	playButton.update(event);
	quitButton.update(event);
	settingButton.update(event);
	creditButton.update(event);
	if(playButton.isClicked())
	{
		g->getFSM().changeState(new GamePlayingState());
	}
	else if(playButton.isEntered())
	{
		playButton.getText().setCharacterSize(60);
		menuSound().play();
	}
	else if(playButton.isExited())
	{
		playButton.getText().setCharacterSize(50);
	}

	else if(quitButton.isClicked())
	{
		g->setRunning(false);
	}
	else if(quitButton.isEntered())
	{
		quitButton.getText().setCharacterSize(60);
		menuSound().play();
	}
	else if(quitButton.isExited())
	{
		quitButton.getText().setCharacterSize(50);
	}

	else if(settingButton.isClicked())
	{
		g->getFSM().changeState(new GameSettingState());
	}
	else if(settingButton.isEntered())
	{
		settingButton.getText().setCharacterSize(60);
		menuSound().play();
	}
	else if(settingButton.isExited())
	{
		settingButton.getText().setCharacterSize(50);
	}
	else if(creditButton.isEntered())
	{
		creditButton.getText().setCharacterSize(60);
		menuSound().play();
	}
	else if(creditButton.isClicked())
	{
		g->getFSM().changeState(new GameCreditState());
	}
	else if(creditButton.isExited())
	{
		creditButton.getText().setCharacterSize(50);
	}
}

void GameMenuState::tick(Game* g, float dt)	
{


}

void GameMenuState::draw(sf::RenderWindow & window)
{
	playButton.draw();
	quitButton.draw();
	settingButton.draw();
	creditButton.draw();
}

void GameMenuState::exit(Game* g)
{

}
