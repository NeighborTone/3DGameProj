#pragma once
#include "ECS.hpp"
#include <Windows.h>
#include "../../Engine.h"
#include "../../Engine/Graphics/Particle.h"
//仮処理、後でファイルを分ける
class CameraComponent : public Component
{
private:
	Camera camera3D;
	Camera camera2D;
public:
	void Init() override
	{
		camera3D.pos.z = -20;
		camera3D.pos.y = 5;

		camera3D.SetPerspective(45.0f, 1, 10000.0f);
		camera3D.SetDepthTest(true);

		camera2D.SetDepthTest(false);
		camera2D.SetOrthographic(1, 0.1f, 1000.0f);
	}

	void UpDate() override
	{

	}
	void Project3D()
	{
		camera3D.Run(true);
	}

	void Project2D()
	{
		camera2D.Run(false);
	}
	void Draw3D() override
	{
		
	}

	void Draw2D() override
	{
	
	}
	Camera GetCamera3D() const
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

	void Init() override
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
	void Init() override
	{

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

	void Draw2D() override
	{

	}

};

class ParticleComponent : Component
{
private:
	Particle particle;
public:


};