#pragma once
#include "Transform.hpp"
#include "../../Graphics/Mesh.h"

//簡易スカイボックス
class SkyBoxComponent : public Component
{
private:
	TransformComponent* trans;
	Mesh sky;
	Texture tex;
public:
	SkyBoxComponent(std::string texturePath);
	void SetPos(Pos&& pos);
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB

};