// entityuserdata.h
#ifndef ENTITYUSERDATA_H
#define ENTITYUSERDATA_H

class EntityUserData {
public:
    enum Type {
        PLAYER,
        ENEMY
        
    };

    Type type;

    // Constructor
    EntityUserData(Type entityType) : type(entityType) {}
};

#endif // ENTITYUSERDATA_H
