#include "movement.hpp"
#include "collisionmap.hpp"

void Movement::Update(Transform2D& transform, Vector2 moveDir, float delta, const CollisionMap *collisionMap)
{
  float newX = transform.position.x + moveDir.x * speed * delta;
  float newY = transform.position.y + moveDir.y * speed * delta;

  if(collisionMap)
  {
    if(collisionMap->isWalkable(newX, transform.position.y)){
      transform.position.x = newX;
    }
    if(collisionMap->isWalkable(transform.position.x, newY)){
      transform.position.y = newY;
    }
  }
  else
  {
    transform.position.x = newX;
    transform.position.y = newY;
  }
}