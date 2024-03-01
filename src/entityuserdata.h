#ifndef ENTITY_USER_DATA_H
#define ENTITY_USER_DATA_H

struct EntityUserData {
    enum EntityType { PLAYER, ENEMY };
    EntityType type;
};

#endif // ENTITY_USER_DATA_H
