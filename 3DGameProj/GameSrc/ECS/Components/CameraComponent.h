#pragma once
#include "Transform.hpp"

class CameraComponent : public Component
{
private:
	TransformComponent* transform;
	Camera camera3D;
	Camera camera2D;
	Sprite sprite;
public:
	CameraComponent();
	void Initialize() override;
	void UpDate() override;
	void Project3D();
	void Project2D();
	void Draw3D() STUB
	void Draw2D() override;
	void DrawCenterCursor(bool enable);
	const Camera& GetCamera3D() const;
};