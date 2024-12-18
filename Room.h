//
// Created by Tim Apers on 29/10/2024.
//

#ifndef ROOM_H
#define ROOM_H

#include "Entity.h"

class Room {
public:

    Room();

    const std::vector<Entity *> &getEntities() const;

    void addEntity(Entity* newentity);

    // Deze functie niet aanpassen!
    void render(sf::RenderWindow* window) const;

    // Deze functie zal je zelf verder moeten aanvullen
    void update(sf::Event* event);

    Player *getPlayer() const;

    void setPlayer(Player *player);

private:
    std::vector<Entity*> entities;
    Player* player;
};



#endif //ROOM_H
