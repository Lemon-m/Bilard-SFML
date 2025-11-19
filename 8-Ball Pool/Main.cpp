#include "Game.h"
#include "MainMenuState.h"

static const float pi = 3.141592654f;

#ifdef _DEBUG
int main()
#else
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
#endif
{
	Game game;
	game.pushState(std::make_unique<MainMenuState>(game));
	game.run();
}
 