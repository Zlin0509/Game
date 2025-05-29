//
// Created by 27682 on 2025/5/28.
//

#ifndef PLAYER_H
#define PLAYER_H

#include <SFML/Graphics.hpp>
#include "Monster.h"

class Player {
public:
    Player(const sf::Texture &texture); // 修改为接受纹理对象

    void updatePostion(float deltaTime); // 更新玩家位置

    void updateHealth(const std::vector<Monster> &monsters); // 更新玩家血量

    void update(float deltaTime, const std::vector<Monster> &monsters); // 更新玩家状态

    void draw(sf::RenderWindow &window); // 绘制玩家

    bool get_state() const;

    int get_health() const;

private:
    sf::Sprite sprite; // 玩家精灵
    float speed = 300.f; // 玩家移动速度
    int health = 1000000;
};
#endif //PLAYER_H
