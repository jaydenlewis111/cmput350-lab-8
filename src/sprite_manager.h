#ifndef SPRITE_MANAGER_H
#define SPRITE_MANAGER_H

#include "sprite.h"
#include <SFML/Graphics.hpp>
#include <cstddef>
#include <deque>
#include <string>
#include <unordered_map>
#include <utility>

using SpriteID = std::size_t;

class SpriteManager {
public:
    SpriteManager() = default;

    // Sprites point into this manager's texture storage, so copying is unsafe.
    SpriteManager(const SpriteManager&) = delete;
    SpriteManager& operator=(const SpriteManager&) = delete;

    sf::Texture& registerTexture(const std::string& filepath) {
        return mTextures.try_emplace(filepath, filepath).first->second;
    }

    template <typename... Args>
    SpriteID createSprite(Args&&... args) {
        mSprites.emplace_back(std::forward<Args>(args)...);
        return mSprites.size() - 1;
    }

    Sprite& getSprite(SpriteID id) {
        return mSprites.at(id);
    }

private:
    // Rehashing preserves references to unordered_map elements.
    std::unordered_map<std::string, sf::Texture> mTextures;
    // Appending to a deque preserves references returned by getSprite.
    std::deque<Sprite> mSprites;
};

#endif  // SPRITE_MANAGER_H
