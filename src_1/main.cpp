//
// Created by Zlin on 2025/4/27.
//

#include "header/Player.h"
#include <SFML/Window.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(800, 600)), "MyPotatoGame");

    Player player;

    sf::Clock clock;
    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();
        while (const std::optional event = window.pollEvent()) {
            // Window closed or escape key pressed: exit
            if (event->is<sf::Event::Closed>() ||
                (event->is<sf::Event::KeyPressed>() &&
                 event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)) {
                window.close();
            }
        }
        player.handleInput(deltaTime);
        player.update();

        window.clear();
        player.draw(window);
        window.display();
    }

    return 0;
}
