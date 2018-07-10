#pragma once
#include "CameraComponent.h"
#include "../../Graphics/Mesh.h"

//‚±‚ÌComponent‚Í•s—v‚È‹C‚ª‚·‚é
class MeshComponent : public Component
{
private:
	bool isCreate;
	TransformComponent* transform;
	Texture tex;
	Mesh mesh;
	void LoadTexture(const char* Texturepath);
	void LoadShader(const char* shaderPath);
public:
	MeshComponent() {}
	MeshComponent(const char* Texturepath);
	MeshComponent(const char* Texturepath, const char* shaderPath);
	void SetMaterial(const char* Texturepath, const char* shaderPath = "Resource/Shader/mesh.hlsl");
	void SetTransform(Pos&& pos, Velocity&& velocity, Angles&& angle, Scale&& scale);
	bool CreateCube(bool shouldClear = true);
	bool CreateSphere(float radius = 0.5f, int tessellation = 10, bool shouldClear = true);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB
};