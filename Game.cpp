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
    Room* roombuilder;
    vector<Room*> rooms;
    ifstream file{filename};
    char token;
    int x = 0;
    while(file.get(token)){
        if (x%700 == 0){
            rooms.push_back(roombuilder);
            roombuilder = new Room;
        }
        int y = 0;
        while (y != 700){
            Entity* newEp = new Entity;
            Position newEpos;
            newEpos.x = x;
            newEpos.y = y;
            newEp->setPosition(newEpos);
            newEp->setSprite("resources/wall.png");
            roombuilder->addEntity(newEp);
            y += 100;
        }
        x += 100;
    }
    currentRoom = rooms[1];
    currentRoom->render(window);
}

void Game::setCurrentRoom() {

}