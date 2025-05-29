//
// Created by 27682 on 2025/5/28.
//
#include "Photo.h"

Photo::Photo() {
    auto playerTexture = std::make_unique<sf::Texture>();
    if (!playerTexture->loadFromFile("assets/Player/Main.png")) {
        std::cerr << "Error loading player texture" << std::endl;
    }
    all["Player"] = std::move(playerTexture);

    auto monsterTexture = std::make_unique<sf::Texture>();
    if (!monsterTexture->loadFromFile("assets/Monster/monster.png")) {
        std::cerr << "Error loading monster texture" << std::endl;
    }
    all["Monster"] = std::move(monsterTexture);

    auto Back_Opening = std::make_unique<sf::Texture>();
    if (!Back_Opening->loadFromFile("assets/Background/Opening.png")) {
        std::cerr << "Error loading opening texture" << std::endl;
    }
    all["Back_Opening"] = std::move(Back_Opening);

    auto Back_Playing = std::make_unique<sf::Texture>();
    if (!Back_Playing->loadFromFile("assets/Background/Playing.png")) {
        std::cerr << "Error loading playing texture" << std::endl;
    }
    all["Back_Playing"] = std::move(Back_Playing);
}

sf::Texture *Photo::getTexture(std::string name) {
    return all[name].get();
}
