//
// Created by Tim Apers on 29/10/2024.
//

#ifndef GAME_H
#define GAME_H

#include "Room.h"
using namespace std;

class Game {
public:

    Game();

    // Deze functies niet aanpassen!
    Game(sf::RenderWindow* window);
    void update();
    std::vector<Room *> getRooms() { return rooms; }
    Room* getCurrentRoom() { return currentRoom; }

    // Deze functies zal je zelf verder moeten aanvullen
    void loadMap(const std::string& filename);
    void setCurrentRoom();

    bool roomExsistence (int x, int y) const;

    bool addRoom (Room* newroom, int y);


private:
    sf::RenderWindow* window;
    std::vector<Room*> rooms;
    vector<vector<Room *>> roomMatrix;
    Room* currentRoom = nullptr;
};



#endif //GAME_H
