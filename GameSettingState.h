#pragma once
#include "state.h"
#include "Button.h"
#include "FontResource.h"
#include "TextureResource.h"
#include "SoundResource.h"
class Game;

class GameSettingState :public State<Game>
{
private:
	Button backButton;
	Button soundControlLabel;
	Button soundControlDownButton;
	Button soundControlUpButton;
	FontResource font;
	TextureResource upSprite;
	TextureResource downSprite;
	SoundResource menuSound;
	float soundLevel;
public:
	GameSettingState();
	virtual ~GameSettingState();

	virtual void enter(Game*);
	virtual void handleEvent(const sf::Event & event, Game * g);
	virtual void tick(Game*, float dt);
	virtual void draw(sf::RenderWindow & window);
	virtual void exit(Game*);

};

