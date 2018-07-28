#include "Engine/Engine.h"
#include "Engine/Utilitys/Utility.hpp"
#include "Engine/Utilitys/Console.hpp"
#include "GameSrc/GameMain.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ShowConsole();
	//ÉGÉìÉWÉìê∂ê¨
	Engine ge("3DGame!!", 1280, 960, Message::SetFullScreen());
	GameMain main(ge);
	main.Initialize();
	main.Run();
	main.Finalize();
	return 0;
}