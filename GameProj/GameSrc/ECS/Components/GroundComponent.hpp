#pragma once
#include "Transform.hpp"
#include "MeshComponent.h"

//テスト
//Tips:コンポーネント同士を内部的に結合して一つのコンポーネントとして使うこともできた
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