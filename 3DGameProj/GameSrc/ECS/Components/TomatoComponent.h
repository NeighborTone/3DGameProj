#pragma once
#include "../../Engine.h"
#include "../ECS.hpp"
#include "../Components/ComponentData/MetaData.hpp"
#include <vector>

class TomatoComponent : public Component
{
private:
	static constexpr float OnGround = 4;
	Mesh mesh;
	Texture tex;
	std::vector<ToppingData> data;
	void Executioners();
public:
	TomatoComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() STUB
	const std::vector<ToppingData>& GetData() const;
	//º‚í‚ê‚Ä‚¢‚é‚Æ‚«‚Ì“®ì
	void ToBeKidnapped(Entity& enemy);
};
