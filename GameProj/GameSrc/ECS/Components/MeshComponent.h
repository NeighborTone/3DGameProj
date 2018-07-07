#pragma once
#include "CameraComponent.h"
#include "../../Graphics/Mesh.h"

class MeshComponent : public Component
{
private:
	bool isCreate;
	TransformComponent* transform;
	Texture tex;
	Mesh mesh;
public:
	MeshComponent(const char* Texturepath);
	MeshComponent(const char* Texturepath, const char* shaderPath);
	bool CreateCube(bool shouldClear = true);
	bool CreateSphere(float radius = 0.5f, int tessellation = 10, bool shouldClear = true);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB
};