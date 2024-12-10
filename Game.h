//
// Created by Tim Apers on 29/10/2024.
//

#ifndef GAME_H
#define GAME_H

#include "Room.h"

class Game {
public:
    // Deze functies niet aanpassen!
    Game(sf::RenderWindow* window);
    void update();

    // Deze functies zal je zelf verder moeten aanvullen
    void loadMap();
    void setCurrentRoom();

private:
    sf::RenderWindow* window;
    std::vector<Room*> rooms;
    Room* currentRoom;
};



#endif //GAME_H
