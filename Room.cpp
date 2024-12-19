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
    Position playerpos;
    for (Entity* entity : entities) {
        entity->update(event, playerpos);
    }
    for (Entity *entity2: entities) {
        int interactio = player->getAttackPower();
        Entity* to_delete = entity2->interacts(player, playerpos, interactio);
        if (to_delete != nullptr && to_delete != player){
            player->setAttackPower(1);
            removeEntity(to_delete);
        }
    }
}

const std::vector<Entity *> &Room::getEntities() const {
    return entities;
}

void Room::addEntity(Entity* newentity) {
    entities.push_back(newentity);
}

void Room::removeEntity(Entity *deathbound) {
    for (int i = 0; i < entities.size(); i++){
        if (entities[i] == deathbound){
            entities.erase(entities.begin()+i);
        }
    }
}

Room::Room() {}

Player *Room::getPlayer() const {
    return player;
}

void Room::setPlayer(Player *player) {
    Room::player = player;
}
