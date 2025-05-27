//
// Created by 27682 on 2025/5/27.
//
#include "../headers/Player.hpp"
#include <cmath>
#include <iostream>

// 手动实现归一化
sf::Vector2f normalize(const sf::Vector2f &vector) {
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y); // 计算向量的长度
    if (length != 0.f) {
        return vector / length; // 归一化
    }
    return vector; // 如果长度为 0，返回原向量
}

Player::Player() : sprite(texture) {
    if (!texture.loadFromFile("C:/Users/27682/Desktop/Game/assets/Player/Main.png")) {
        std::cerr << "Failed to load image" << std::endl;
    }
    // 创建精灵并设置纹理
    sprite.setTexture(texture);

    // 缩放到 32x32 显示
    sf::Vector2u textureSize = texture.getSize();
    sprite.setScale({32.f / textureSize.x, 32.f / textureSize.y});

    // 设置精灵的原点（通常设为图片的中心）
    sprite.setOrigin({textureSize.x / 2.f, textureSize.y / 2.f});

    // 设置起始位置
    sprite.setPosition({400, 300});

    speed = 300.f; // 每秒移动速度
}

void Player::handleInput(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += 1.f;

    if (movement != sf::Vector2f(0.f, 0.f)) {
        sprite.move(normalize(movement) * speed * deltaTime);
    }
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);
    // 未来可添加：动画、状态、碰撞等
}

void Player::draw(sf::RenderTarget &target) const {
    // std::cerr << sprite.getPosition().x << " " << sprite.getPosition().y << std::endl;
    target.draw(sprite);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}
