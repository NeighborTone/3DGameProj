#pragma once
#include "Transform.hpp"
#include "ComponentData/Collision.h"
#include "../Components/ComponentData/MetaData.hpp"
#include <vector>

//�R���X�g���N�^(���x,�ő��,���a)
class InputShotComponent : public Component 
{
private:
 float speed_;
 Mesh mesh;
 std::vector<ShotData> shots;
 Texture tex;
public:
  InputShotComponent(const float speed,const int maxNum,const float radius);
  void Initialize() override;
  void UpDate() override;
  void Draw3D() override;
  void Draw2D() STUB
  void Shot(TransformComponent&& trans);
  bool IsHit(AABB& aabb);

};