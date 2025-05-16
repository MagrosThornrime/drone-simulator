#pragma once
#include <game_objects/GameObject.h>

class Terrain : public GameObject
{
    void _fillCollider(AssetManager& assetManager) override;
    public:
    Terrain(const std::string& modelName, glm::vec3 position, glm::vec3 scale, AssetManager& assetManager);
};