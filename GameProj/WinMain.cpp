#pragma warning (disable : 4100)	//メイン関数の引数
#include "Engine/Engine.h"
#include "Engine/Utilitys/Console.hpp"
#include "Engine/Graphics/Model.h"
#include "Engine/Physics/Physics.h"
#include "Engine/Graphics/Model.h"
#include "Engine/Sounds/SoundSource.h"
#include "Engine/Sounds/SoundEffect.h"
#include "Engine/Graphics/Particle.h"

using namespace DirectX;
bool HitBall(Vec3 &c1, Vec3& c2, float r, float r2)
{
	if ((c1.x - c2.x) * (c1.x - c2.x) + ((c1.y - c2.y) * (c1.y - c2.y)) + ((c1.z - c2.z) * (c1.z - c2.z)) <= (r + r) * (r2 + r2))
	{
		return true;
	}
	return false;

}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	ShowConsole();
	//ゲームエンジン生成
	Engine ge("DirectX11", 1280, 900, true);
	//カメラ生成
	Camera camera3D;
	camera3D.pos.z = -20;
	camera3D.pos.y = 5;

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
	struct Obj
	{
		Mesh mesh;
		bool isActive;

		float
			dirX = 0, 
			dirY = 0, 
			dirZ = 0;
		int dethTime = 0;
	};
	SoundEngine::SoundSource sound;
	SoundEngine::SoundEffect sEffect;
	sEffect.limiter.Loudness = 1700;
	Particle expro;
	expro.Load("Resource/Effect/testEf.efk");
	sound.Load("Resource/Sounds/se.ogg", true);
	sEffect.AttachLimiter(sound);
	Obj hoge;
	hoge.mesh.GetMaterial().Load("Resource/Shader/hoge.hlsl");
	hoge.mesh.CreateSphere(2,12);
	hoge.mesh.GetMaterial().SetTexture(0,&walltex);
	hoge.isActive = true;
	hoge.mesh.pos.y = 10;
	hoge.mesh.CreateSphere();
	
	Obj shot[20];
	for (auto& it : shot)
	{
		it.mesh.GetMaterial().Load("Resource/Shader/shot.hlsl");
		it.mesh.CreateSphere();
		it.mesh.GetMaterial().SetTexture(0, &walltex);
		it.isActive = false;
	}
	phy.AddGeometry(new StaticBox(Vec3(ground.pos), Vec3(ground.scale)));
	Mouse::SetMousePos(0, 0);
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
			camera3D.angle.x += Mouse::GetMousePosCenter().y * 0.3f;
			camera3D.angle.y += Mouse::GetMousePosCenter().x * 0.3f;

			bool o = Mouse::L_On() % 8 == 1;
			for (auto& i : shot)
			{
				if (o && !i.isActive)
				{
					i.mesh.pos = camera3D.pos;
					
					//90度ずれてしまうのでオフセットする
					i.dirX = cosf(XMConvertToRadians(-camera3D.angle.y+90)) * cosf(XMConvertToRadians(-camera3D.angle.x)) * 3;
					i.dirY = sinf(XMConvertToRadians(-camera3D.angle.x)) * 3;
					i.dirZ = cosf(XMConvertToRadians(-camera3D.angle.x)) * sinf(XMConvertToRadians(-camera3D.angle.y+90)) * 3;
				
					i.isActive = true;
					break;
				}
			}
			for (auto& i : shot)
			{
				if (i.dethTime > 100 && i.isActive)
				{
					i.dethTime = 0;
					i.isActive = false;
				}
			}
			for (auto& i : shot)
			{
				if (HitBall(hoge.mesh.pos, i.mesh.pos, 1, 0.5f) && hoge.isActive)
				{
					expro.pos = hoge.mesh.pos;
					expro.Play();
					sound.PlaySE();
					i.isActive = false;
					hoge.isActive = false;
				}
			}
			
			for (auto& i : shot)
			{
				if (i.isActive)
				{
					i.mesh.pos.x += i.dirX;
					i.mesh.pos.y += i.dirY;
					i.mesh.pos.z += i.dirZ;
					++i.dethTime;
					i.mesh.Draw();

				}
			}
			
			if (hoge.isActive)
			{
				hoge.mesh.Draw();
			}
			
			ground.Draw();
			expro.Draw(camera3D);
			sound.UpDate3DSound(Vec3(hoge.mesh.pos),Vec3(camera3D.pos));
			//===================================//
			//==========2DRendering=================//
			//===================================//
			camera2D.Run(false);
			--cursor.angle.z;
			cursor.Draw();
			Mouse::SetMousePos(0, 0);
			Mouse::DrawCursor(false);
			std::cout << "X: "<< camera3D.angle.x << "Y: " << camera3D.angle.y << "Z: " << camera3D.angle.z << std::endl;
	}
	//終了
	return 0;

}