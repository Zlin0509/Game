//
// Created by Zlin on 25-5-31.
//
#include "Bullet.h"
#include <cmath>
#include <iostream>

Bullet::Bullet(const sf::Vector2f pos, Monster *target, const sf::Texture &texture) : target(target), sprite(texture) {
    sprite.setScale({32.f / 1024.f, 32.f / 1024.f});
    sprite.setPosition(pos);
}

void Bullet::update(float deltaTime) {
    sf::Vector2f pos = sprite.getPosition();
    sf::Vector2f targetPos = target->getPosition();

    sf::Vector2f direction = targetPos - pos;

    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
    if (length != 0) direction /= length;

    float speed = 150.f;
    sprite.move(direction * speed * deltaTime);
}


bool Bullet::checkCollision() {
    if (target->getHealth()) return true;
    if (const std::optional intersection = sprite.getGlobalBounds().findIntersection(target->getBounds())) {
        target->changeLive();
        target->makeDamge(damge);
        return true;
    }
    return false;
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
