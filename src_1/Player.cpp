//
// Created by Zlin on 2025/4/27.
//
#include "Player.h"
#include <SFML/Window.hpp>
#include <iostream>
#include <cmath>

Player::Player(): sprite(texture) {
    if (!texture.loadFromFile("assets/player.png")) {
        std::cerr << "Error loading texture" << std::endl;
        return;
    }
    sprite.setTexture(texture);
    // 图像原点为照片中心
    sprite.setScale(sf::Vector2f(texture.getSize().x / 2.0f, texture.getSize().y / 2.0f));
    // 初始位置
    sprite.setPosition(sf::Vector2f(400.0f, 300.0f));
}

void Player::handleInput(float deltaTime) {
    sf::Vector2f movement(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1.0f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x -= 1.0f;

    sprite.move(movement * speed * deltaTime);
}


void Player::update(float deltaTime) {
    // 玩家朝向鼠标方向旋转
    sf::Vector2i mousePos = sf::Mouse::getPosition();
    sf::Vector2f playerPos = sprite.getPosition();
    float angle = atan2(mousePos.y - playerPos.y, mousePos.x - playerPos.x) * 180 / M_PI;
    sprite.setRotation(sf::degrees(angle + 90.0f));  // 获取角度的度数并设置旋转
}

void Player::draw(sf::RenderWindow &window) {
    window.draw(sprite);
}

sf::Vector2f Player::getPosition() const {
    return sprite.getPosition();
}
