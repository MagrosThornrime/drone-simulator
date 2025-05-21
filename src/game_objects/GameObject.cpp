#include <game_objects/GameObject.h>

void GameObject::_fillCollider(AssetManager& assetManager)
{
    Model* model = assetManager.getModel(_modelName);
    for (auto& mesh : model->meshes)
    {
        std::vector<glm::dvec3> vertices;
        mesh.getVertices(vertices);
        _collider.addPart(vertices);
        // Logger::log(std::to_string(vertices.size()), info);
    }
}

void GameObject::draw(Renderer& renderer, AssetManager& assetManager)
{
    Model* model = assetManager.getModel(_modelName);
    renderer.drawModel(model, _position, _scale);
}

bool GameObject::collidesWith(const GameObject& other) const
{
    return Collider::areColliding(_collider, other._collider);
}

GameObject::GameObject(const std::string& modelName, glm::vec3 position, glm::vec3 scale, AssetManager& assetManager)
: _modelName(modelName), _position(position), _scale(scale)
{
    GameObject::_fillCollider(assetManager);
    _collider.setDynamicVertices(_position, _scale);
}
