#include <VisualLeakDetector\vld.h>
#pragma comment(lib, "vld.lib")
//=================================================================//
#include "Game.h"
#include <ctime>
#include <cmath>
int main()
{
	srand(time(0));
	Game game;
	game.run();


	return 0;
}


