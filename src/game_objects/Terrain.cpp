#include <game_objects/Terrain.h>

void Terrain::_fillCollider(AssetManager& assetManager)
{
    Model* model = assetManager.getModel(_modelName);
    Mesh& mesh = model->meshes[0];
    std::vector<glm::dvec3> vertices;
    std::vector<unsigned int> indices;

    mesh.getVertices(vertices);
    mesh.getIndices(indices);

    // construct a pillar using the face and a triangle parallel to x and z axis.
    for (int i = 0; i < indices.size(); i += 3)
    {
        std::vector<glm::dvec3> part;
        double minY = std::numeric_limits<double>::infinity();
        int minVertex = -1;
        for (int j = 0; j < 3; j++)
        {
            glm::dvec3 faceVertex = vertices[indices[i] + j];
            if (faceVertex.y < minY)
            {
                minY = faceVertex.y;
                minVertex = j;
            }
            part.push_back(faceVertex);
        }
        for (int j = 0; j < 3; j++)
        {
            if (j == minVertex)
            {
                continue;
            }
            glm::dvec3 faceVertex = vertices[indices[i] + j];
            glm::dvec3 lowerVertex = {faceVertex.x, minY, faceVertex.z};
            part.push_back(lowerVertex);
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
    _collider.setDynamicVertices(position, scale);
}
