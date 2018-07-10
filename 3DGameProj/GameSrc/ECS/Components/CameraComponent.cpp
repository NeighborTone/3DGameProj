#include "CameraComponent.h"

CameraComponent::CameraComponent()
{
	sprite.Load("Resource/Texture/cursor.png");
}

void CameraComponent::Initialize()
{
	if (!entity->HasComponent<TransformComponent>())
	{
		entity->AddComponent<TransformComponent>();
	}

	transform = &entity->GetComponent<TransformComponent>();
	camera3D.pos = transform->pos;

	camera3D.SetPerspective(45.0f, 1, 10000.0f);
	camera3D.SetDepthTest(true);

	camera2D.SetDepthTest(false);
	camera2D.SetOrthographic(1, 0.1f, 1000.0f);
}

void CameraComponent::UpDate()
{
	
	camera3D.pos = transform->pos;
	camera3D.angle = transform->angle;
}

void CameraComponent::Project3D()
{
	camera3D.Run(true);
}

void CameraComponent::Project2D()
{
	camera2D.Run(false);
}

void CameraComponent::Draw2D()
{
	DrawCenterCursor(true);
}

void CameraComponent::DrawCenterCursor(bool enable)
{
	if (!enable)
	{
		return;
	}
	--sprite.angle.z;
	sprite.Draw();
}

const Camera& CameraComponent::GetCamera3D() const
{
	return camera3D;
}