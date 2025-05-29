//
// Created by 27682 on 2025/5/29.
//

#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/Graphics.hpp>

class Monster {
public:
    Monster(const sf::Texture &texture);

    void update(float deltaTime);

    void draw(sf::RenderWindow &window);

    sf::FloatRect getBounds() const;

    int getDamage() const;

    void respawn(); // 重新随机生成怪物

private:
    sf::Sprite sprite;
    sf::Vector2f velocity; // 移动方向
    int damage = 1;
};

#endif //MONSTER_H
