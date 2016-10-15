#include "GameCreditState.h"
#include "GameMenuState.h"
#include "Game.h"


GameCreditState::GameCreditState()
{
	font.load("C:/Users/Park/Desktop/Newfolder/Fonts/Ubuntu-L.TTF");
	menuSound.load("C:/Users/Park/Desktop/Newfolder/Music/button.wav");
	movie.openFromFile("C:/Users/Park/Desktop/Newfolder/My Movie.wmv");
}


GameCreditState::~GameCreditState()
{
}


void GameCreditState::enter(Game* g)
{
	backButton.setWindow(g->getWindow());
	backButton.getText().setString("Back");
	backButton.getText().setFont(font());
	backButton.getText().setCharacterSize(50);
	backButton.getText().setColor(sf::Color::Blue);
	backButton.setClickArea(backButton.getText().getGlobalBounds());
	movie.setPosition(300, 0);
	movie.play();
}
void GameCreditState::handleEvent(const sf::Event & event, Game * g)
{
	backButton.update(event);
	if(backButton.isEntered())
	{
		menuSound().play();
		backButton.getText().setCharacterSize(60);
	}
	else if(backButton.isClicked())
	{
		g->getFSM().changeState(new GameMenuState());
	}
	else if(backButton.isExited())
	{
		backButton.getText().setCharacterSize(50);
	}
}
void GameCreditState::tick(Game*, float dt)
{

}

void GameCreditState::exit(Game*)
{
	movie.stop();
}

void GameCreditState::draw(sf::RenderWindow & window)
{
	backButton.draw();
	window.draw(movie);
}

