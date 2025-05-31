//
// Created by Zlin on 25-5-31.
//
#include "Bullet.h"
#include <cmath>

Bullet::Bullet(const sf::Vector2f pos, Monster *target, const sf::Texture &texture) : target(target), sprite(texture) {
}

void Bullet::update(float deltatTme) {
    sf::Vector2f velocity;
    auto [x, y] = sprite.getPosition();
    auto [dx, dy] = target->getPosition();
    if (x == dx) velocity.x = 0;
    else if (x > dx) velocity.x = -1;
    else velocity.x = 1;
    if (y == dy) velocity.y = 0;
    else if (y > dy) velocity.y = -1;
    else velocity.y = 1;
    sprite.move(velocity * deltatTme);
}

bool Bullet::checkCollision() {
    if (target->getHealth() <= 0) return true;
    if (const std::optional intersection = sprite.getGlobalBounds().findIntersection(target->getBounds())) {
        target->makeDamge(damge);
        return true;
    }
    return false;
}

void Bullet::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
