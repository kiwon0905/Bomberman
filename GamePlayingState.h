#pragma once
#include "State.h"
#include "Button.h"
#include "FontResource.h"
#include "SoundResource.h"


#include "GameWorld.h"

class Game;

class GamePlayingState :public State<Game>
{
private:
	GameWorld gameWorld;
	SoundResource menuSound;
	Button backButton;
	FontResource font;
public:
	virtual void enter(Game*);
	virtual void handleEvent(const sf::Event & event, Game * g);
	virtual void tick(Game*, float dt);
	virtual void exit(Game*);
	virtual void draw(sf::RenderWindow & window);

	GamePlayingState();
	virtual ~GamePlayingState();
};

