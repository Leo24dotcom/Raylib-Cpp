#pragma once
#include "raylib.h"
#include "Transform2D.hpp"
#include "movementstate.hpp"

class CollisionMap;

struct Movement
{
  float speed = 0.0f;

  void Update(Transform2D& transform, const MovementState& movementState, float delta, const CollisionMap * collisionMap = nullptr);
};