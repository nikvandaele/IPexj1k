//
// Created by Tim Apers on 29/10/2024.
//

#include "Room.h"
using namespace std;

void Room::render(sf::RenderWindow* window) const {
    Player* player = nullptr;
    std::vector<Entity*> others = {};
    for (Entity* entity : entities) {
        if (auto* floor = dynamic_cast<Floor*>(entity)) {floor->render(window);}
        else if (auto* p = dynamic_cast<Player*>(entity)) { player = p;}
        else { others.push_back(entity); }
    }
    for (Entity* e : others) { e->render(window); }
    if (player) { player->render(window);}
}

void Room::update(sf::Event* event) {
    for (Entity* entity : entities) {
        entity->update(event);
    }
}

const std::vector<Entity *> &Room::getEntities() const {
    return entities;
}

void Room::addEntity(Entity* newentity) {
    entities.push_back(newentity);
}
