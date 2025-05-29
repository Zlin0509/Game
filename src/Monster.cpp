//
// Created by 27682 on 2025/5/29.
//
#include "Monster.h"
#include <random>

std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());

Monster::Monster(const sf::Texture &texture) : sprite(texture) {
    respawn();
}

void Monster::respawn() {
    // 1. 随机位置（以窗口 800x600 为例）
    float x = static_cast<float>(rng() % 960);
    float y = static_cast<float>(rng() % 540);
    sprite.setPosition({x, y});

    // 2. 随机速度方向（-25 到 25 像素/秒）
    float vx = static_cast<float>(rng() % 51 - 25);
    float vy = static_cast<float>(rng() % 51 - 25);
    velocity = {vx, vy};

    damage = rng() % 10;
}

void Monster::update(float deltaTime) {
    sprite.move(velocity * deltaTime);

    // 如果超出屏幕边界，可以反弹或重新随机方向
    sf::Vector2f pos = sprite.getPosition();
    if (pos.x < 10 || pos.x > 950 || pos.y < 10 || pos.y > 510) {
        respawn(); // 超出边界重新随机生成
    }
}

void Monster::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

sf::FloatRect Monster::getBounds() const {
    return sprite.getGlobalBounds();
}

int Monster::getDamage() const {
    return damage;
}

