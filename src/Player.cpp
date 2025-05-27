//
// Created by 27682 on 2025/5/28.
//
#include "../headers/Player.h"

// 构造函数，接受一个纹理对象
Player::Player(const sf::Texture &texture) : sprite(texture) {
    // 获取纹理尺寸并缩放精灵为 32x32
    sf::Vector2u textureSize = texture.getSize();
    sprite.setScale({32.f / textureSize.x, 32.f / textureSize.y});

    // 设置精灵的初始位置为窗口中心
    sprite.setPosition({400.f, 300.f});
}

// 处理玩家输入
void Player::handleInput(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    // 按键处理
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += 1.f;

    // 根据输入移动玩家
    if (movement != sf::Vector2f(0.f, 0.f)) {
        sprite.move(movement * speed * deltaTime);
    }
}

// 更新玩家状态
void Player::update(float deltaTime) {
    handleInput(deltaTime);
}

// 绘制玩家
void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}
