//
// Created by Zlin on 25-5-31.
//

#ifndef BULLET_H
#define BULLET_H

#pragma once
#include <SFML/Graphics.hpp>
#include "Monster.h"
#include "Player.h"

class Bullet {
public:
    Bullet(const sf::Vector2f pos, Monster *target, const sf::Texture &texture);

    void update(float deltaTime);

    void draw(sf::RenderWindow &window);

    bool isOffScreen(const sf::RenderWindow &window) const;

    bool checkCollision(); // 命中检测

private:
    sf::Sprite sprite;
    Monster *target;
    int damge = 10;
    float speed = 100.f;
};

#endif //BULLET_H
