#include "GameSettingState.h"
#include "Game.h"
#include "GameMenuState.h"
#include <SFML\Audio.hpp>
#include <boost\lexical_cast.hpp>
#include <fstream>



GameSettingState::GameSettingState()
{
	font.load("C:/Users/Park/Desktop/Newfolder/Fonts/Ubuntu-L.TTF");
	menuSound.load("C:/Users/Park/Desktop/Newfolder/Music/button.wav");
	upSprite.load("C:/Users/Park/Desktop/Newfolder/upArrow.jpg");
	downSprite.load("C:/Users/Park/Desktop/Newfolder/downArrow.jpg");

	std::ifstream fin("C:/Users/Park/Desktop/Newfolder/setting.txt");
	std::string dummy;
	fin>>dummy;
	fin>>soundLevel;
	fin.close();
	sf::Listener::setGlobalVolume(soundLevel);
}


GameSettingState::~GameSettingState()
{
	std::ofstream fout("C:/Users/Park/Desktop/Newfolder/setting.txt");
	fout.clear();
	fout<<"Sound: "<<soundLevel;
	fout.close();
}

void GameSettingState::enter(Game* g)
{
	sf::Listener::setGlobalVolume(soundLevel);
	backButton.setWindow(g->getWindow());
	backButton.getText().setString("Back");
	backButton.getText().setFont(font());
	backButton.getText().setCharacterSize(50);
	backButton.getText().setColor(sf::Color::Blue);
	backButton.getText().setPosition(300, 300);
	backButton.setClickArea(backButton.getText().getGlobalBounds());

	soundControlLabel.setWindow(g->getWindow());
	soundControlLabel.getText().setString("Sound: "+boost::lexical_cast<std::string>(soundLevel));
	soundControlLabel.getText().setFont(font());
	soundControlLabel.getText().setCharacterSize(50);
	soundControlLabel.getText().setColor(sf::Color::Blue);
	soundControlLabel.getText().setPosition(300, 400);

	soundControlUpButton.setWindow(g->getWindow());
	soundControlUpButton.addSprite(upSprite());
	soundControlUpButton.getSprite().setColor(sf::Color::Blue);
	soundControlUpButton.getSprite().setPosition(500, 350);
	soundControlUpButton.setClickArea(soundControlUpButton.getSprite().getGlobalBounds());

	soundControlDownButton.setWindow(g->getWindow());
	soundControlDownButton.addSprite(downSprite());
	soundControlDownButton.getSprite().setColor(sf::Color::Blue);
	soundControlDownButton.getSprite().setPosition(500, 470);
	soundControlDownButton.setClickArea(soundControlDownButton.getSprite().getGlobalBounds());

}

void GameSettingState::handleEvent(const sf::Event & event, Game * g)
{
	backButton.update(event);
	soundControlUpButton.update(event);
	soundControlDownButton.update(event);
	if(backButton.isEntered())
	{
		backButton.getText().setCharacterSize(60);
		menuSound().play();
	}
	else if(backButton.isClicked())
	{
		g->getFSM().changeState(new GameMenuState());
	}
	else if(backButton.isExited())
	{
		backButton.getText().setCharacterSize(50);
	}
	else if(soundControlUpButton.isEntered())
	{
		soundControlUpButton.getSprite().setColor(sf::Color::Red);
		menuSound().play();
	}
	else if(soundControlUpButton.isClicked())
	{
		if(soundLevel<100)
			soundLevel+=1;
		sf::Listener::setGlobalVolume(soundLevel);
		soundControlLabel.getText().setString("Sound: "+boost::lexical_cast<std::string>(soundLevel));

	}
	else if(soundControlUpButton.isExited())
	{
		soundControlUpButton.getSprite().setColor(sf::Color::Blue);
	}
	else if(soundControlDownButton.isEntered())
	{
		soundControlDownButton.getSprite().setColor(sf::Color::Red);
		menuSound().play();
	}
	else if(soundControlDownButton.isClicked())
	{
		if(soundLevel>0)
			soundLevel-=1;
		sf::Listener::setGlobalVolume(soundLevel);
		soundControlLabel.getText().setString("Sound: "+boost::lexical_cast<std::string>(soundLevel));
	}
	else if(soundControlDownButton.isExited())
	{
		soundControlDownButton.getSprite().setColor(sf::Color::Blue);
	}
}

void GameSettingState::tick(Game* g, float dt)
{

}

void GameSettingState::draw(sf::RenderWindow & window)
{
	backButton.draw();
	soundControlLabel.draw();
	soundControlUpButton.draw();
	soundControlDownButton.draw();
}

void GameSettingState::exit(Game*)
{
}