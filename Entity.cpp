//
// Created by Tim Apers on 29/10/2024.
//

#include "Entity.h"
#include <iostream>

void Entity::setSprite(const std::string& img_path) {
    if (!this->texture.loadFromFile(img_path)) {
        std::cerr << "Failed to load texture" << std::endl;
    }
    this->sprite.setTexture(this->texture);
    sf::Vector2u size = this->texture.getSize();
    float scaleX = 100.0f / size.x;
    float scaleY = 100.0f / size.y;
    this->sprite.setScale(scaleX, scaleY);
}

void Entity::render(sf::RenderWindow *window) {
    sprite.setPosition(position.x%700, position.y%700);
    window->draw(sprite);
}

void Entity::update(sf::Event* event, Position &playerpos) {

}

const Position Entity::getPosition() const {
    return position;
}

void Entity::setPosition(const Position &position) {
    Entity::position = position;
}

Entity::Entity() {
    setPosition(Position());
}

void Player::update(sf::Event* event, Position &playerpos) {
    Position position = getPosition();
    playerpos = getPosition();
    switch (event->key.code) {
        case sf::Keyboard::Left:
            // Move to the left
            position.x -= 100;
                break;
        case sf::Keyboard::Right:
            // Move to the right
            position.x += 100;
                break;
        case sf::Keyboard::Up:
            // Move up
            position.y -= 100;
                break;
        case sf::Keyboard::Down:
            // Move down
            position.y += 100;
                break;
        default: break;
    }
    setPosition(position);
}

bool Entity::standsOn(Entity *betredene) const {
    return position.x == betredene->position.x && position.y == betredene->position.y;
}

void Entity::interacts(Entity *betredene, const Position &playerpos) {}

void Player::setAttackPower(int attackPower) {
    AttackPower = attackPower;
}

int Player::getAttackPower() const {
    return AttackPower;
}

void Wall::interacts(Entity *betredene, const Position &playerpos) {
    if (standsOn(betredene) && this != betredene){
        betredene->setPosition(playerpos);
    }
}
