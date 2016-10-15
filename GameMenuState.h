#pragma once
#include "State.h"
#include "Button.h"
#include "FontResource.h"
#include "SoundResource.h"
#include <SFML/System.hpp>
#include <unordered_map>
class Game;

class GameMenuState :public State<Game>
{
private:
	FontResource font;
	SoundResource menuSound;
	Button playButton;
	Button quitButton;
	Button settingButton;
	Button creditButton;
public:
	virtual void enter(Game*);
	virtual void handleEvent(const sf::Event & event, Game * g);
	virtual void tick(Game*, float dt);
	virtual void draw(sf::RenderWindow & window);
	virtual void exit(Game*);

	GameMenuState();
	virtual ~GameMenuState();
};

