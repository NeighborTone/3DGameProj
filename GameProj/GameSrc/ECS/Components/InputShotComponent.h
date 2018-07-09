#pragma once
#include "Transform.hpp"
#include <vector>
class InputShotComponent : public Component 
{
private:
 float speed_;
 struct Shots
 {
	 bool isActive;
	 int deathTime;
	 Mesh mesh;
	 Velocity velocity;	//Œü‚«‚âˆÚ“®—Ê‚ðŠi”[
 };
 std::vector<Shots> shots;
 Texture tex;
public:
  InputShotComponent(const float speed,int maxNum);
  void Initialize() override;
  void UpDate() override;
  void Draw3D() override;
  void Draw2D() STUB

  void Shot(TransformComponent&& trans);

};