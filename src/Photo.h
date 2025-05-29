//
// Created by 27682 on 2025/5/28.
//

#ifndef PHOTO_H
#define PHOTO_H
#include <iostream>
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class Photo {
public:
    Photo();

    sf::Texture* getTexture(std::string name);
private:
    std::unordered_map<std::string, std::unique_ptr<sf::Texture>> all;
};

#endif //PHOTO_H
