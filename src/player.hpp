#pragma once

#include "raylib.h"
#include "Transform2D.hpp"
#include "Sprite.hpp"
#include "movement.hpp"

class CollisionMap;

class Player
{
  public:
    Player(Texture2D* tex);

    void Draw() const;
    void Update(float delta);

    Vector2 GetPosition() const;

    void SetPosition(Vector2 positon);

    void SetCollisionMap(const CollisionMap *collisionMap);

  private:
    Transform2D _transform;
    Sprite _sprite;
    Movement _movement;
    const CollisionMap *_collisionMap = nullptr;
};