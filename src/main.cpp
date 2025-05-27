//
// Created by 27682 on 2025/5/27.
//
#include <iostream>
#include <SFML/Graphics.hpp>

constexpr float speed = 300.f;

// 玩家输入和移动处理函数
void handlePlayerInput(sf::Sprite &playerSprite, float deltaTime, float speed) {
    sf::Vector2f movement(0.f, 0.f);

    // 按键处理
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1.f;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += 1.f;

    // 移动玩家
    if (movement != sf::Vector2f(0.f, 0.f)) {
        playerSprite.move(movement * speed * deltaTime);
    }
}

int main() {
    // 创建一个窗口，大小为 800x600，标题为 "Potato Brothers"
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Potato Brothers");
    // 设置游戏帧率限制（例如 60 FPS）
    window.setFramerateLimit(120);

    // 初始化背景图片
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("C:/Users/27682/Desktop/Game/assets/background.jpg")) {
        std::cerr << "Error loading background image" << std::endl;
    } else {
        std::cerr << "Loaded background image" << std::endl;
    }
    sf::Sprite background(backgroundTexture);
    background.setScale({
        static_cast<float>(window.getSize().x / backgroundTexture.getSize().x),
        static_cast<float>(window.getSize().y / backgroundTexture.getSize().y)
    });

    // 初始化玩家
    sf::Texture player;
    if (!player.loadFromFile("C:/Users/27682/Desktop/Game/assets/Player/Main.png")) {
        std::cerr << "Error loading texture" << std::endl;
    } else {
        std::cerr << "Loaded player image" << std::endl;
    }
    sf::Sprite Player(player);
    Player.setScale({32.f / player.getSize().x, 32.f / player.getSize().y});
    Player.setPosition({window.getSize().x / 2.f, window.getSize().y / 2.f});

    // 游戏主循环
    sf::Clock clock; // 用于计算时间差，deltaTime
    while (window.isOpen()) {
        // 检查所有触发的窗口事件
        while (const std::optional event = window.pollEvent()) {
            // 关闭窗口指令
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // 计算时间差，deltaTime（以秒为单位）
        float deltaTime = clock.restart().asSeconds();

        // 处理玩家输入
        handlePlayerInput(Player, deltaTime, speed);

        window.clear(sf::Color::Black);

        window.draw(background);
        window.draw(Player);

        window.display();
    }

    return 0;
}
