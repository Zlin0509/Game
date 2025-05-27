//
// Created by 27682 on 2025/5/27.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void handleInput(float deltaTime);
    void update(float deltaTime);
    void draw(sf::RenderTarget& target) const;

    sf::Vector2f getPosition() const;

private:
    sf::Texture texture;
    sf::Sprite sprite;   // 精灵对象
    float speed;
};

#endif //PLAYER_H
