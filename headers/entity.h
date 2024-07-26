#ifndef ENTITY_H
#define ENTITY_H

class Player;
class Entity {
  public:
    enum EntityType {
      ENEMY,
      PLAYER,
      ITEM
    };
    Entity(EntityType eType);
    virtual ~Entity();
    EntityType eType;
    virtual void notify(Player& player) = 0;
    virtual char charAt() const = 0;
};

#endif
