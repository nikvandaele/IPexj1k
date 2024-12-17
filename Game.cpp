//
// Created by Tim Apers on 29/10/2024.
//

#include "Game.h"
#include <fstream>
using namespace std;

Game::Game(sf::RenderWindow* window) {
    this->window = window;
}

void Game::update() {
    setCurrentRoom();
    this->window->clear();
    if (currentRoom) { currentRoom->render(this->window); }
    this->window->display();
    while (window->isOpen()) {
        sf::Event event;

        // Wait for event to fire
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            } else if (event.type == sf::Event::KeyPressed) {
                currentRoom->update(&event);
                setCurrentRoom();
                this->window->clear();
                currentRoom->render(this->window);
                this->window->display();
            }
        }
    }

}

void Game::loadMap(const std::string &filename) {
    ifstream file{filename};
    char token;
    int x = 0;
    int y = 0;
    int roomx = 0;
    int roomy = 0;
    int numberofrooms = 0;
    while(file.get(token)){
        if (token == '\n') {
            x = 0;
            y += 100;
        }else{
            roomx = x/700;
            roomy = y/700;
            Entity *newEp = new Entity;
            Position newEpos;
            newEpos.x = x;
            newEpos.y = y;
            newEp->setPosition(newEpos);
            if (token == '#') {
                newEp->setSprite("resources/wall.png");
            }else if (token == '_'){
                newEp->setSprite("resources/floor.png");
            }else if (token == '%'){
                newEp->setSprite("resources/enemy.png");
            }else if (token == '!'){
                newEp->setSprite("resources/weapon.png");
            }else if (token == '@'){
                newEp->setSprite("resources/player.png");
            }
            if (roomExsistence(roomx, roomy) == false){
                Room* newR = new Room;
                rooms.push_back(newR);
                addRoom(newR, roomy);
                numberofrooms++;
            }
            roomMatrix[roomy][roomx]->addEntity(newEp);
            x += 100;
        }
    }
    currentRoom = roomMatrix[1][0];
    currentRoom->render(window);
}

void Game::setCurrentRoom() {

}

bool Game::roomExsistence(int x, int y) const {
    return roomMatrix.size() > y && roomMatrix[y].size() > x;
}

bool Game::addRoom(Room *newroom, int y) {
    if (roomMatrix.size() == y+1){
        roomMatrix[y].push_back(newroom);
        return true;
    }
    if (roomMatrix.size() == y){
        vector<Room*> newRow;
        roomMatrix.push_back(newRow);
        roomMatrix[y].push_back(newroom);
        return true;
    }
    return false;
}