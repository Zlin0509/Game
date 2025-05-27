//
// Created by 27682 on 2025/5/27.
//
#include "../headers/Player.hpp"
#include <cmath>

// 手动实现归一化
sf::Vector2f normalize(const sf::Vector2f& vector) {
    float length = std::sqrt(vector.x * vector.x + vector.y * vector.y);  // 计算向量的长度
    if (length != 0.f) {
        return vector / length;  // 归一化
    }
    return vector;  // 如果长度为 0，返回原向量
}

Player::Player() {
    shape.setRadius(25.f);
    shape.setFillColor(sf::Color::Green);
    shape.setOrigin(sf::Vector2f(shape.getRadius(), shape.getRadius()));
    shape.setPosition(sf::Vector2f(400.f, 300.f)); // 起始位置

    speed = 300.f; // 每秒移动速度
}

void Player::handleInput(float deltaTime) {
    sf::Vector2f movement(0.f, 0.f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += 1.f;

    if (movement != sf::Vector2f(0.f, 0.f)) {
        shape.move(normalize(movement) * speed * deltaTime);
    }
}

void Player::update(float deltaTime) {
    handleInput(deltaTime);
    // 未来可添加：动画、状态、碰撞等
}

void Player::draw(sf::RenderTarget& target) const {
    target.draw(shape);
}

sf::Vector2f Player::getPosition() const {
    return shape.getPosition();
}
