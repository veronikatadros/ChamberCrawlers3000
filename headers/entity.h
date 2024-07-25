#ifndef ENTITY_H
#define ENTITY_H

class Entity {
  public:
  enum EntityType {
      ENEMY,
      PLAYER,
      ITEM
    };
    Entity(EntityType entityType);
    virtual ~Entity();
    EntityType entityType;
    virtual void notify() = 0;
    virtual char charAt() = 0;
};

#endif
