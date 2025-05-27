//
// Created by 27682 on 2025/5/28.
//
#include "../headers/Photo.h"

Photo::Photo() {
    auto backTexture = std::make_unique<sf::Texture>();
    if (!backTexture->loadFromFile("C:/Users/27682/Desktop/Game/assets/Background/background.jpg")) {
        std::cerr << "Error loading background texture" << std::endl;
    }
    all["Back1"] = std::move(backTexture);  // 使用 std::move 转移 ownership

    auto playerTexture = std::make_unique<sf::Texture>();
    if (!playerTexture->loadFromFile("C:/Users/27682/Desktop/Game/assets/Player/Main.png")) {
        std::cerr << "Error loading player texture" << std::endl;
    }
    all["Player1"] = std::move(playerTexture);  // 将 unique_ptr 存入容器
}

sf::Texture *Photo::getTexture(std::string name) {
    return all[name].get();  // 返回原始指针
}