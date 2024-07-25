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
    EntityType eType;
    void virtual notify() = 0;
    void virtual charAt() = 0;
};

#endif
