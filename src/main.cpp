//
// Created by 27682 on 2025/5/27.
//
#include <iostream>
#include <SFML/Graphics.hpp>
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

    // 读取字体
    sf::Font font;
    if (!font.openFromFile("C:/Users/27682/Desktop/Game/assets/Font/A.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
    }

    // Playing窗口的血量展示
    sf::Text hpText(font);
    hpText.setCharacterSize(24); // 字体大小
    hpText.setFillColor(sf::Color::Red);
    hpText.setPosition({10.f, 10.f}); // 左上角位置

    // 读取基本Texture内容到内存池
    Photo all;

    // 玩家和怪物类
    Player player(*all.getTexture("Player"));
    std::vector<Monster> monsters;

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

            while (monsters.size() <= 8) monsters.emplace_back(*all.getTexture("Monster"));

            for (auto &monster: monsters) monster.update(deltaTime);

            player.update(deltaTime, monsters);

            for (auto &monster: monsters) monster.draw(window);

            player.draw(window);

            hpText.setString("HP: " + std::to_string(player.get_health()));
            window.draw(hpText);

            if (!player.get_state()) currentState = GameState::Stoped;
        } else if (currentState == GameState::Stoped) {
        }

        window.display();
    }

    return 0;
}
