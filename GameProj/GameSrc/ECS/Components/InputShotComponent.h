#pragma once
#include "Transform.hpp"

class InputShotComponent : public Component 
{
private:
 TransformComponent* transform;
 float speed_;
 bool isActive;
 int deathTime;
public:
  InputShotComponent(const float speed);
  void Initialize() override;
  void UpDate() override;
  void Draw3D() STUB
  void Draw2D() STUB

  void Shot(TransformComponent&& trans);

  bool IsActive();
};