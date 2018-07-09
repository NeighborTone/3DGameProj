#include "Engine/Engine.h"
#include "Engine/Utilitys/Console.hpp"
#include "GameSrc/GameMain.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	ShowConsole();
	//�G���W������
	Engine ge("3DGame!!", 1280, 900, true);
	GameMain main(ge);
	main.Initialize();
	main.Run();
	main.Finalize();
	return 0;
}