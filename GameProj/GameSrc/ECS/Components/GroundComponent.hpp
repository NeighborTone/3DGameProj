#pragma once
#include "Transform.hpp"
#include "MeshComponent.h"

//�e�X�g
//Tips:�R���|�[�l���g���m������I�Ɍ������Ĉ�̃R���|�[�l���g�Ƃ��Ďg�����Ƃ��ł���
class GroundComponent : public Component
{
private:
	TransformComponent * trans;
	MeshComponent* mesh;
	Pos pos;
	Angles angle;
	Scale scale;
public:
	GroundComponent(Pos&& pos, Angles&& angle, Scale&& scale) :
		pos(pos),
		angle(angle),
		scale(scale)
	{}
	void Initialize() override
	{
		if (!entity->HasComponent<TransformComponent>())
		{
			entity->AddComponent<TransformComponent>();
			trans = &entity->GetComponent<TransformComponent>();
		}
		trans->pos = pos;
		trans->angle = angle;
		trans->scale = scale;
		if (!entity->HasComponent<MeshComponent>())
		{
			entity->AddComponent<MeshComponent>("Resource/Texture/stonewall_diff.jpg", "Resource/Shader/hoge.hlsl").CreateSphere();
			mesh = &entity->GetComponent<MeshComponent>();
		}
	}

	void UpDate() STUB

	void Draw3D() STUB

	void Draw2D() STUB

};