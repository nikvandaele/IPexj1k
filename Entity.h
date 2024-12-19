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

    virtual Entity* interacts(Entity* interactor, const Position &playerpos, int &interactreturn);

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

class Weapon : public Entity {
public:
    virtual Entity* interacts(Entity* interactor, const Position &playerpos, int &interactreturn);
};

class Wall : public Entity {
public:
    virtual Entity* interacts(Entity* interactor, const Position &playerpos, int &interactreturn);
};

class Floor : public Entity {};

class Enemy : public Entity {
private:
    int health;
public:
    virtual Entity* interacts(Entity* interactor, const Position &playerpos, int &interactreturn);

    void setHealth(int health);

    int getHealth() const;
};

class Portal : public Entity {
private:
    Position target;
public:
    const Position &getTarget() const;

    void setTarget(const Position &target);

    virtual Entity* interacts(Entity* interactor, const Position &playerpos, int &interactreturn);
};


#endif //ENTITY_H
