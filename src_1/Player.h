//
// Created by Zlin on 2025/4/27.
//
#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    // 处理输入
    void handleInput(float deltaTime);

    // 更新玩家状态
    void update(float deltaTime);

    // 绘制玩家
    void draw(sf::RenderWindow &window);

    // 获取玩家位置
    sf::Vector2f getPosition() const;

private:
    sf::Sprite sprite;
    sf::Texture texture;
    float speed = 200.0f;
};

#endif
