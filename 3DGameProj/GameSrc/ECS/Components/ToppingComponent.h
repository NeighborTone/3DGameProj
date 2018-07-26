#pragma once
#include "../../Engine.h"
#include "../ECS.hpp"
#include "../Components/ComponentData/MetaData.hpp"
#include <vector>

class ToppingComponent : public Component
{
private:
	Mesh mesh;
	Texture tex;
	std::vector<ToppingData> data;
	void Executioners();
public:
	ToppingComponent();
	void Initialize() override;
	void UpDate() override;
	void Draw3D() override;
	void Draw2D() override;
	const std::vector<ToppingData>& GetData() const;
	void ToBeKidnapped(Entity& enemy);
};
