//
// Created by 27682 on 2025/5/27.
//
#include <iostream>
#include <SFML/Graphics.hpp>

#include "Bullet.h"
#include "Photo.h"
#include "Player.h"
#include "Monster.h"

enum class GameState {
    Menu,
    Playing,
    Settings,
    Stoped,
    Exit
};

int main() {
    sf::RenderWindow window(sf::VideoMode({960, 540}), "Potato Brothers");
    window.setFramerateLimit(120);

    // 游戏页面状态
    GameState currentState = GameState::Menu;

    float bulletCooldown = 0.f;           // 冷却计时器
    const float bulletInterval = 0.3f;    // 冷却间隔


    // 读取字体
    sf::Font font;
    if (!font.openFromFile("assets/Font/A.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    int score = 0, highScore = 0;

    // Playing窗口的得分展示
    sf::Text scoreText(font);
    scoreText.setCharacterSize(24); // 字体大小
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({800.f, 10.f}); // 右上角位置

    // Playing窗口的血量展示
    sf::Text hpText(font);
    hpText.setCharacterSize(24); // 字体大小
    hpText.setFillColor(sf::Color::Red);
    hpText.setPosition({10.f, 10.f}); // 左上角位置

    // 游戏结束页面按钮
    sf::Text finalScoreText(font);
    finalScoreText.setCharacterSize(30);
    finalScoreText.setFillColor(sf::Color::Yellow);
    finalScoreText.setPosition({300.f, 150.f});

    sf::Text highScoreText(font);
    highScoreText.setCharacterSize(30);
    highScoreText.setFillColor(sf::Color::Cyan);
    highScoreText.setPosition({300.f, 200.f});

    sf::RectangleShape returnButton(sf::Vector2f(200.f, 50.f));
    returnButton.setPosition({380.f, 300.f});
    returnButton.setFillColor(sf::Color(150, 150, 250));

    sf::Text returnText(font);
    returnText.setCharacterSize(24);
    returnText.setString("Return to Menu");
    returnText.setFillColor(sf::Color::Black);
    returnText.setPosition({400.f, 310.f});

    sf::Text restartGame(font);
    restartGame.setCharacterSize(24);
    restartGame.setString("Restart");
    restartGame.setFillColor(sf::Color::Red);
    restartGame.setPosition({400.f, 410.f});

    // 读取Texture内容到内存池
    Photo all;

    // 玩家和怪物类
    Player player(*all.getTexture("Player"));
    std::vector<Monster> Monsters;
    std::vector<Bullet> Bullets;

    // 背景元素
    sf::Sprite OpeningBackground(*all.getTexture("Back_Opening"));
    sf::Sprite PlayingBackground(*all.getTexture("Back_Playing"));

    sf::Clock clock;
    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();

            // 处理窗口切换
            if (currentState == GameState::Menu) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                    sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                    int x = localPosition.x;
                    int y = localPosition.y;
                    if (x >= 25 && x <= 81 && y >= 323 && y <= 360) {
                        currentState = GameState::Playing;
                        std::cerr << "Switched to Playing state\n";
                    } else if (x >= 25 && x <= 81 && y >= 376 && y <= 400) {
                        currentState = GameState::Settings;
                        std::cerr << "Switched to Settings state\n";
                    } else if (x >= 25 && x <= 81 && y >= 464 && y <= 496) {
                        currentState = GameState::Exit;
                        std::cerr << "Exiting game...\n";
                    }
                }
            } else if (currentState == GameState::Playing) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
                    currentState = GameState::Stoped;
                    std::cerr << "Switched to Stoped state\n";
                }
            } else if (currentState == GameState::Settings) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                }
            } else if (currentState == GameState::Stoped) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                }
            }
        }

        window.clear(sf::Color::Black);

        float deltaTime = clock.restart().asSeconds();

        if (currentState == GameState::Exit) {
            window.close();
        } else if (currentState == GameState::Menu) {
            window.draw(OpeningBackground);
        } else if (currentState == GameState::Playing) {
            window.draw(PlayingBackground);

            // 如果怪物数量少于8，生成新怪物
            while (Monsters.size() < 16) Monsters.emplace_back(*all.getTexture("Monster"));

            // 每0.5秒向最近的怪物发射一个子弹
            bulletCooldown += deltaTime;

            if (bulletCooldown >= bulletInterval && !Monsters.empty()) {
                // 找到距离玩家最近的怪物
                Monster* closest = nullptr;
                float minDist = std::numeric_limits<float>::max();
                sf::Vector2f playerPos = player.getPosition();

                for (auto &monster : Monsters) {
                    sf::Vector2f mpos = monster.getPosition();
                    float dist = std::hypot(playerPos.x - mpos.x, playerPos.y - mpos.y);
                    if (dist < minDist) {
                        minDist = dist;
                        closest = &monster;
                    }
                }
                // 向最近的怪物发射子弹
                if (closest) {
                    Bullets.emplace_back(playerPos, closest, *all.getTexture("Bullet"));
                    bulletCooldown = 0.f;  // 重置冷却
                }
            }


            // 更新怪物坐标
            for (auto &monster: Monsters) monster.update(deltaTime);

            //更新子弹坐标
            for (auto &bullet: Bullets) bullet.update(deltaTime);

            // 判断子弹状态，如果集中目标或者目标已经死了，删除这个子弹
            for (auto it = Bullets.begin(); it != Bullets.end();) it->checkCollision() ? it = Bullets.erase(it) : ++it;

            // 判断怪物状态，如果怪物血量<=0，说明死亡，重置这个怪物
            for (auto &monster: Monsters) {
                if (monster.getHealth()) {
                    score += 1;
                    monster.reset();
                }
            }

            // 更新玩家坐标和血量
            player.update(deltaTime, Monsters);

            // 绘图
            for (auto &monster: Monsters) monster.draw(window);

            player.draw(window);

            for (auto &bullet: Bullets) bullet.draw(window);

            hpText.setString("HP: " + std::to_string(player.getHealth()));
            window.draw(hpText);

            scoreText.setString("Score: " + std::to_string(score));
            window.draw(scoreText);

            if (!player.getState()) currentState = GameState::Stoped;
        } else if (currentState == GameState::Stoped) {
            // std::cerr << "傻逼你已经死了\n";
            // 更新最高分
            if (score > highScore) highScore = score;

            // 绘制得分文本
            finalScoreText.setString("Your Score: " + std::to_string(score));
            highScoreText.setString("High Score: " + std::to_string(highScore));

            window.draw(finalScoreText);
            window.draw(highScoreText);
            window.draw(returnButton);
            window.draw(returnText);
            window.draw(restartGame);

            // 检测点击“Return to Menu”按钮
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
                score = 0;
                player.reset();
                Monsters.clear();
                Bullets.clear();
                auto [mx, my] = sf::Mouse::getPosition(window);
                if (mx >= 380 && mx <= 580 && my >= 300 && my <= 350) {
                    currentState = GameState::Menu;
                } else if (mx >= 380 && mx <= 580 && my >= 400 && my <= 450) {
                    currentState = GameState::Playing;
                }
            }

        }

        window.display();
    }

    return 0;
}
