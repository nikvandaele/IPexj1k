//
// Created by Tim Apers on 29/10/2024.
//

#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

struct Position {
    int x;
    int y;
};

class Entity {
public:

    Entity();

    virtual void update(sf::Event* event, Position &playerpos);

    // Onderstaande functies niet aanpassen!
    void setSprite(const std::string &img_path);

    void render(sf::RenderWindow *painter);
    ~Entity() = default;

    const Position getPosition() const;

    void setPosition(const Position &position);

    bool standsOn(Entity* betredene) const;

    virtual void interacts(Entity* betredene, const Position &playerpos);

private:
    Position position;
    sf::Sprite sprite;
    sf::Texture texture;
};


class Player : public Entity {
    int AttackPower;
public:
    void update(sf::Event* event, Position &playerpos) override;

    void setAttackPower(int attackPower);

    int getAttackPower() const;

};

class Weapon : public Entity {};

class Wall : public Entity {
public:
    virtual void interacts(Entity* betredene, const Position &playerpos);
};

class Floor : public Entity {};

class Enemy : public Entity {};



#endif //ENTITY_H
