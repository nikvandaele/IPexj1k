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
            Position newEpos;
            newEpos.x = x;
            newEpos.y = y;
            if (roomExsistence(roomx, roomy) == false){
                Room* newR = new Room;
                rooms.push_back(newR);
                addRoom(newR, roomy);
                numberofrooms++;
            }
            if (token == '#') {
                //add wall
                Wall* newEp = new Wall;
                newEp->setPosition(newEpos);
                newEp->setSprite("resources/wall.png");
                roomMatrix[roomy][roomx]->addEntity(newEp);
            }else if (token == '"'){
                //add void wall
                Wall* newEp = new Wall;
                newEp->setPosition(newEpos);
                roomMatrix[roomy][roomx]->addEntity(newEp);
            }else if (token == '-'){
                //add floor be displayed
                Floor* tileunderplayer = new Floor;
                tileunderplayer->setPosition(newEpos);
                tileunderplayer->setSprite("resources/floor.png");
                roomMatrix[roomy][roomx]->addEntity(tileunderplayer);
                //add invis wall
                Wall* newEp = new Wall;
                newEp->setPosition(newEpos);
                roomMatrix[roomy][roomx]->addEntity(newEp);
            }else if (token == '_'){
                //add floor
                Floor* newEp = new Floor;
                newEp->setPosition(newEpos);
                newEp->setSprite("resources/floor.png");
                roomMatrix[roomy][roomx]->addEntity(newEp);
            }else if (token == '%'){
                //add tile to go under enemy
                Floor* tileunderplayer = new Floor;
                tileunderplayer->setPosition(newEpos);
                tileunderplayer->setSprite("resources/floor.png");
                roomMatrix[roomy][roomx]->addEntity(tileunderplayer);

                //add weapon
                Enemy* newEp = new Enemy;
                newEp->setPosition(newEpos);
                newEp->setSprite("resources/enemy.png");
                roomMatrix[roomy][roomx]->addEntity(newEp);
            }else if (token == '!'){
                //add tile to go under enemy
                Floor* tileunderplayer = new Floor;
                tileunderplayer->setPosition(newEpos);
                tileunderplayer->setSprite("resources/floor.png");
                roomMatrix[roomy][roomx]->addEntity(tileunderplayer);

                //add weapon
                Weapon* newEp = new Weapon;
                newEp->setPosition(newEpos);
                newEp->setSprite("resources/weapon.png");
                roomMatrix[roomy][roomx]->addEntity(newEp);
            }else if (token == '@'){
                //add tile to go under playe
                Floor* tileunderplayer = new Floor;
                tileunderplayer->setPosition(newEpos);
                tileunderplayer->setSprite("resources/floor.png");
                roomMatrix[roomy][roomx]->addEntity(tileunderplayer);

                //add player
                Player* newEp = new Player;
                newEp->setPosition(newEpos);
                newEp->setSprite("resources/player.png");
                currentRoom = roomMatrix[roomy][roomx];
                currentRoom->setPlayer(newEp);
                roomMatrix[roomy][roomx]->addEntity(newEp);
            }else if (token == 'o'){
                Portal* newEp = new Portal;
                newEp->setPosition(newEpos);
                newEp->setSprite("resources/portal.png");
                Position target;
                target.x = 8000;
                target.y = 800;
                newEp->setTarget(target);
                roomMatrix[roomy][roomx]->addEntity(newEp);
            }
            x += 100;
        }
    }
    currentRoom->render(window);
}

void Game::setCurrentRoom() {
    Room* changecheck = currentRoom;
    Player* player = currentRoom->getPlayer();
    Position position = player->getPosition();
    int x = position.x/700;
    int y = position.y/700;
    currentRoom = roomMatrix[y][x];
    if (changecheck != currentRoom){
        currentRoom->addEntity(player);
        changecheck->removeEntity(player);
        currentRoom->setPlayer(player);
    }
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

Game::Game() {}


