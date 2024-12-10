//
//  !!! Dit bestand moet je in principe NIET wijzigen !!!
//

#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
    sf::RenderWindow window(sf::VideoMode(700, 700), "Game");
    Game game = Game(&window);
    game.loadMap();
    game.update();
    return 0;
}
