#pragma once
#include "ECS.hpp"
#include <Windows.h>
#include <iostream>
#include "../../Engine.h"
#include "../../Engine/Graphics/Particle.h"

#define STUB override {}
//仮処理、後でファイルを分ける
class CameraComponent : public Component
{
private:
	Camera camera3D;
	Camera camera2D;
public:
	void Initialize() override
	{
		camera3D.pos.z = -20;
		camera3D.pos.y = 5;

		camera3D.SetPerspective(45.0f, 1, 10000.0f);
		camera3D.SetDepthTest(true);

		camera2D.SetDepthTest(false);
		camera2D.SetOrthographic(1, 0.1f, 1000.0f);
	}

	void UpDate() STUB

	void Project3D()
	{
		camera3D.Run(true);
	}

	void Project2D()
	{
		camera2D.Run(false);
	}
	void Draw3D() STUB

	void Draw2D() STUB

	const Camera& GetCamera3D() const
	{
		return camera3D;
	}

};
//リソース確保はロードかコンストラクタ
class SpriteComponent : public Component
{
private:
	Sprite sp;
public:

	void Initialize() override
	{
		sp.pos = 0;
		sp.angle = 0;
		sp.scale = 1;
	}
	SpriteComponent(const char* const filePath)
	{
		sp.Load(filePath);
	}
	void UpDate() override
	{
		--sp.angle.z;
	}
	void Draw3D() override
	{
		sp.color = Float4(1, 0, 0, 1);
		sp.scale = 1.0f / sp.GetSize().y;
		sp.Draw();
	}
	void Draw2D() override
	{
		sp.color = Float4(1, 1, 1, 1);
		sp.scale = 1;
		sp.Draw();
	}

};

class MeshComponent : public Component
{
private:
	Mesh mesh;
	Texture tex;
public:
	MeshComponent(const char* const filePath)
	{
		tex.Load(filePath);
		mesh.CreateSphere();
		mesh.GetMaterial().SetTexture(0, &tex);
		
	}
	void Initialize() override
	{
		mesh.pos = 0;
		mesh.angle = 0;
		mesh.scale = 1;
	}

	void UpDate() override
	{
		++mesh.angle.x;
	}

	void Draw3D() override
	{
		mesh.pos.x = 2;
		mesh.Draw();
	}

	void Draw2D() STUB

};


//パーティクル自体をstd::mapで管理するほうが良いかも
class ParticleComponent : public Component
{
private:
	Particle particle;
public:
	ParticleComponent(const char* path)
	{
		particle.Load(path);
	}
	void Initialize() override
	{
		particle.pos = 0;
		particle.angle = 0;
		particle.scale = 1;
	}
	void Play()
	{
		if(KeyBoard::Down(KeyBoard::Key::KEY_Z))
		particle.Play();
	}
	void UpDate() STUB

	//このメソッド消したい
	void UpDate3DParticle(const Camera& camera) override
	{
		//↡この引数クッソ邪魔!!!
		particle.Draw(camera);
	}
	void Draw3D() STUB
	//{
		//particle.Draw()	//これが理想
	//}

	void Draw2D() STUB

};