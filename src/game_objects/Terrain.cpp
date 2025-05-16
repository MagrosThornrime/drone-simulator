#include <game_objects/Terrain.h>

void Terrain::_fillCollider(AssetManager& assetManager)
{
    Model* model = assetManager.getModel(_modelName);
    Mesh& mesh = model->meshes[0];
    std::vector<glm::vec3> vertices;
    std::vector<unsigned int> indices;

    mesh.getVertices(vertices);
    mesh.getIndices(indices);

    // find a y coordinate that is just slightly lower than the lowest point on terrain
    float minY = std::numeric_limits<float>::infinity();
    for (auto vertex : vertices)
    {
        minY = std::min(minY, vertex.y);
    }
    minY -= 1.0f;

    // construct a pillar using the face and a triangle parallel to x and z axis.
    for (int i = 0; i < indices.size(); i += 3)
    {
        std::vector<glm::vec3> part;
        for (int j = 0; j < 3; j++)
        {
            glm::vec3 faceVertex = vertices[indices[i] + j];
            glm::vec3 lowerVertex = {faceVertex.x, minY, faceVertex.z};
            part.push_back(lowerVertex);
            part.push_back(faceVertex);
        }
        _collider.addPart(part);
    }
}


Terrain::Terrain(const std::string& modelName, glm::vec3 position, glm::vec3 scale, AssetManager& assetManager)
{
    _modelName = modelName;
    _position = position;
    _scale = scale;
    Terrain::_fillCollider(assetManager);
}
