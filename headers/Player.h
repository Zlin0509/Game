//
// Created by 27682 on 2025/5/28.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include <string>

class Player {
public:
    Player(const sf::Texture &texture); // 修改为接受纹理对象

    void handleInput(float deltaTime); // 处理玩家输入

    void update(float deltaTime); // 更新玩家状态

    void draw(sf::RenderWindow &window); // 绘制玩家

private:
    sf::Sprite sprite; // 玩家精灵
    float speed = 300.f; // 玩家移动速度
};
#endif //PLAYER_H
