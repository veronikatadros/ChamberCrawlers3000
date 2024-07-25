#ifndef ENTITY_H
#define ENTITY_H

class Entity {
   protected:
    enum EntityType {
      ENEMY,
      PLAYER,
      ITEM
    };
  public:
    Entity(EntityType et);
    virtual ~Entity();
    EntityType entityType;
    void virtual notify() = 0;
    char virtual charAt() = 0;
};

#endif
