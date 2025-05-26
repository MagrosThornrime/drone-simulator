#include <game_objects/GameObject.h>

void GameObject::_fillCollider(AssetManager& assetManager)
{
    Model* model = assetManager.getModel(_modelName);
    for (auto& mesh : model->meshes)
    {
        std::vector<glm::dvec3> vertices;
        mesh.getVertices(vertices);
        _collider.addPart(vertices);
    }
}

glm::dmat4 GameObject::_getModelMatrix()
{
    glm::mat4 modelMatrix = glm::dmat4(1.0);
    modelMatrix = glm::translate(modelMatrix, _position);
    modelMatrix = glm::scale(modelMatrix, _scale);
    return modelMatrix;
}

void GameObject::draw(Renderer& renderer, AssetManager& assetManager)
{
    Model* model = assetManager.getModel(_modelName);
    renderer.drawModel(model, glm::mat4(_getModelMatrix()));
}

bool GameObject::collidesWith(const GameObject& other) const
{
    return Collider::areColliding(_collider, other._collider);
}

GameObject::GameObject(const std::string& modelName, glm::vec3 position, glm::vec3 scale, AssetManager& assetManager)
: _modelName(modelName), _position(position), _scale(scale)
{
    GameObject::_fillCollider(assetManager);
    _collider.setDynamicVertices(_getModelMatrix(), _scale);
}
