#pragma once
#include "raylib.h"

class CollisionMap
{
  public:
    void Init(const Image* img);
    bool isWalkable(float x, float y) const;
  private:
    const Image* _img = nullptr;
};