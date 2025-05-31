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

    sf::Vector2f getPosition() const;

    int getDamage() const;

    bool getHealth() const;

    bool isUsed() const;

    void changeLive();

    void makeDamge(int damge);

    void respawn(); // 重新随机生成怪物

    void reset();

private:
    sf::Sprite sprite;
    sf::Vector2f velocity; // 移动方向
    int damage = 1, health = 100;
    bool alive = false;
};

#endif //MONSTER_H
