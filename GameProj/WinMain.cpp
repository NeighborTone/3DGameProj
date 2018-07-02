#pragma warning (disable : 4100)	//メイン関数の引数
#include "Engine/Engine.h"
#include "Engine/Utilitys/Console.hpp"
#include "Engine/Graphics/Model.h"
#include "Engine/Physics/Physics.h"
#include "Engine/Graphics/Model.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	ShowConsole();
	//ゲームエンジン生成
	Engine ge("DirectX11", 1280, 900, true);
	//カメラ生成
	Camera camera3D;
	camera3D.pos.z = -20;
	camera3D.pos.y = 5;
	camera3D.angle.x = 15;

	camera3D.SetPerspective(45.0f, 1, 10000.0f);
	camera3D.SetDepthTest(true);

	Camera camera2D;
	camera2D.SetDepthTest(false);
	camera2D.SetOrthographic(1, 0.1f, 1000.0f);

	Texture walltex("Resource/Texture/stonewall_diff.jpg");
	Sprite cursor("Resource/Texture/cursor.png");
	PhysicsWorld phy;
	Mesh ground;
	ground.pos.y = -10;
	ground.scale = 100;
	ground.scale.y = 5;
	ground.CreateCube();
	ground.GetMaterial().SetTexture(0,&walltex);
	struct Shot
	{
		Mesh mesh;
		bool isActive;
	};
	Shot shot[30];
	for (auto& it : shot)
	{
		it.mesh.GetMaterial().Load("Resource/Shader/shot.hlsl");
		it.mesh.CreateCube();
		it.mesh.GetMaterial().SetTexture(0, &walltex);
		it.isActive = false;
	}
	phy.AddGeometry(new StaticBox(Vec3(ground.pos), Vec3(ground.scale)));
	while (ge.Run())
	{
		phy.UpDate();
			//===================================//
			//==========3DRendering=================//
			//===================================//
			camera3D.Run(true);

			if (KeyBoard::Down(KeyBoard::Key::KEY_ESCAPE) ||
				DInput::Down(DInput::Button::PAD_START))
			{
				break;
			}
			if (KeyBoard::On(KeyBoard::Key::KEY_RIGHT))
			{
				camera3D.pos.x += 0.6f;
			}
			if (KeyBoard::On(KeyBoard::Key::KEY_LEFT))
			{
				camera3D.pos.x -= 0.6f;
			}
			if (KeyBoard::On(KeyBoard::Key::KEY_LCONTROL))
			{
				camera3D.pos.y += 0.6f;
			}
			if (KeyBoard::On(KeyBoard::Key::KEY_RCONTROL))
			{
				camera3D.pos.y -= 0.6f;
			}
			if (KeyBoard::On(KeyBoard::Key::KEY_UP))
			{
				camera3D.pos.z += 0.6f;
			}
			if (KeyBoard::On(KeyBoard::Key::KEY_DOWN))
			{
				camera3D.pos.z -= 0.6f;
			}
			//camera3D.angle.x += Mouse::GetMousePosCenter().y * 0.3f;
			//camera3D.angle.y += Mouse::GetMousePosCenter().x * 0.3f;

			bool o = Mouse::L_On() % 8 == 1;
			for (auto& i : shot)
			{
				if (o && !i.isActive)
				{
					i.mesh.pos = camera3D.pos;
					i.mesh.pos.z += 5;
					i.mesh.pos.y -= 2;
					i.isActive = true;
					break;
				}
				
				if (i.mesh.pos.z > 200)
				{
					i.isActive = false;
				}
			}

			for (auto& i : shot)
			{
				if (i.isActive)
				{
					i.mesh.pos.z += 3;
					i.mesh.Draw();

				}
			}
	
			ground.Draw();

			//===================================//
			//==========2DRendering=================//
			//===================================//
			camera2D.Run(false);

			cursor.Draw();
			Mouse::SetMousePos(0, 0);
			Mouse::DrawCursor(false);
			std::cout << Mouse::L_On() << std::endl;
	}
	//終了
	return 0;

}