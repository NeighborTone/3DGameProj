#pragma once
#include "../ECS.hpp"
#include "../../Utilitys/Counter.hpp"
#include "../../Utilitys/Counter.hpp"
#include "ComponentData/MetaData.hpp"

class TimerComponent : public Component
{
private:
	const std::string font = "Segoe Print";
	static constexpr float size = 35;
	UIData data;
	Counter cnt;
	Text text;
public:
	void Initialize() override;
	void UpDate() override;
	void Draw3D() STUB
	void Draw2D() override;
	void TimerRun();
	[[nodiscard]] const bool IsTimeOver();

};