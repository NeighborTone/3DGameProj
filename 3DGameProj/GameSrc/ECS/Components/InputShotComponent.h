#pragma once
#include "Transform.hpp"
#include "ComponentData/Collision.h"
#include <vector>

//コンストラクタ(速度,最大個数,半径)
class InputShotComponent : public Component 
{
private:
 float speed_;
 struct Shots
 {
	 bool isActive;
	 int deathTime;
	 float radius;
	 Mesh mesh;
	 Velocity velocity;	//向きや移動量を格納
 };
 std::vector<Shots> shots;
 Texture tex;
public:
  InputShotComponent(const float speed,const int maxNum,const float radius);
  void Initialize() override;
  void UpDate() override;
  void Draw3D() override;
  void Draw2D() STUB
  void Shot(TransformComponent&& trans);
  bool IsHit(AABB&& aabb);
  const std::vector<Shots>& GetShots() const;

};