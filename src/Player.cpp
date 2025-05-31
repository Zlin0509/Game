//
// Created by 27682 on 2025/5/28.
//
#include "Player.h"

#include <iostream>

// 构造函数，接受一个纹理对象
Player::Player(const sf::Texture &texture) : sprite(texture) {
    // 获取纹理尺寸并缩放精灵为 32x32
    sf::Vector2u textureSize = texture.getSize();
    sprite.setScale({32.f / textureSize.x, 32.f / textureSize.y});

    // 设置精灵的初始位置为窗口中心
    sprite.setPosition({400.f, 300.f});
}

bool Player::getState() const {
    return health > 0;
}

int Player::getHealth() const {
    return health;
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}

// 更新玩家位置
void Player::updatePostion(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += 1.f;

    if (movement != sf::Vector2f(0.f, 0.f)) sprite.move(movement * speed * deltaTime);

    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::Vector2f pos = sprite.getPosition();

    float minX = 0.f;
    float minY = 0.f;
    float maxX = 960.f - bounds.size.x;
    float maxY = 540.f - bounds.size.y;

    // 修正位置
    if (pos.x < minX) pos.x = minX;
    if (pos.y < minY) pos.y = minY;
    if (pos.x > maxX) pos.x = maxX;
    if (pos.y > maxY) pos.y = maxY;

    sprite.setPosition(pos);
}

// 更新玩家血量
void Player::updateHealth(const std::vector<Monster> &monsters) {
    for (const Monster &monster: monsters) {
        if (const std::optional intersection = sprite.getGlobalBounds().findIntersection(monster.getBounds())) {
            health -= monster.getDamage();
            // std::cerr << "Health: " << health << std::endl;
        }
    }
}

// 更新玩家状态
void Player::update(float deltaTime, const std::vector<Monster> &monsters) {
    updatePostion(deltaTime);
    updateHealth(monsters);
}

// 绘制玩家
void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
