//
// Created by 27682 on 2025/5/27.
//
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "../headers/Player.hpp"

int main() {
    // 创建一个窗口，大小为 800x600，标题为 "Potato Brothers"
    sf::RenderWindow window(sf::VideoMode({800, 600}), "Potato Brothers");

    // 创建玩家对象
    Player player;

    // 设置游戏帧率限制（例如 60 FPS）
    window.setFramerateLimit(60);

    // 游戏主循环
    sf::Clock clock;  // 用于计算时间差，deltaTime
    while (window.isOpen()) {
        // 检查所有触发的窗口事件
        while (const std::optional event = window.pollEvent())
        {
            // 关闭窗口指令
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // 计算时间差，deltaTime（以秒为单位）
        float deltaTime = clock.restart().asSeconds();
        // 更新玩家状态
        player.update(deltaTime);

        // 清空窗口
        window.clear(sf::Color::Black);

        // 绘制玩家对象
        player.draw(window);

        // 显示窗口内容
        window.display();
    }

    return 0;
}
