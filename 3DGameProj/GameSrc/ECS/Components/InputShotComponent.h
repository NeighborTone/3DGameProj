#pragma once
#include "Transform.hpp"
#include "ComponentData/Collision.h"
#include <vector>

//�R���X�g���N�^(���x,�ő��,���a)
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
	 Velocity velocity;	//������ړ��ʂ��i�[
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