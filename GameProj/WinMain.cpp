#include "Engine/Engine.h"
#include "Engine/Utilitys/Console.hpp"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	ShowConsole();
	//�Q�[���G���W������
	Engine ge("DirectX11", 640, 450, true);
	
	//�J��������
	Camera camera3D;
	camera3D.pos.z = -20;
	camera3D.pos.y = 5;
	camera3D.angle.x = 0;

	camera3D.SetPerspective(45.0f, 1, 10000.0f);
	camera3D.SetDepthTest(true);

	Camera camera2D;
	camera2D.SetDepthTest(false);
	camera2D.SetOrthographic(1, 0.1f, 1000.0f);
	
	while (ge.Run())
	{
		//===================================//
		//==========3DRendering=================//
		//===================================//
		camera3D.Run(true);
		
		//===================================//
		//==========2DRendering=================//
		//===================================//
		camera2D.Run(false);
		
	}

	//�I��
	return 0;

}