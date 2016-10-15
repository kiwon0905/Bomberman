#pragma once
#include "state.h"
#include "Button.h"
#include "SoundResource.h"
#include "FontResource.h"
#include <sfeMovie\Movie.hpp>
class Game;

class GameCreditState :public State<Game>
{
private:
	Button backButton;
	SoundResource menuSound;
	FontResource font;
	sfe::Movie movie;
public:

	virtual void enter(Game*);
	virtual void handleEvent(const sf::Event & event, Game * g);
	virtual void tick(Game*, float dt);
	virtual void exit(Game*);
	virtual void draw(sf::RenderWindow & window);


	GameCreditState();
	virtual ~GameCreditState();
};

