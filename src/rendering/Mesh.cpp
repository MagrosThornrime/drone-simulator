#include <stdexcept>
#include <rendering/Mesh.h>
#include <resources/AssetManager.h>

Mesh::Mesh(const std::vector<VertexData>& vertices, const std::vector<unsigned int>& indices,
           const std::vector<std::string>& texturePaths, const std::vector<std::string>& textureTypes)
        : _vertices(vertices), _indices(indices), texturePaths(texturePaths), textureTypes(textureTypes)
{
    glGenVertexArrays(1, &_vao);
    glGenBuffers(1, &_vbo);
    glGenBuffers(1, &_ebo);

    glBindVertexArray(_vao);
    glBindBuffer(GL_ARRAY_BUFFER, _vbo);

    glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(VertexData), &_vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(unsigned int), &_indices[0], GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, normal));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(VertexData), (void*)offsetof(VertexData, texCoords));

    glBindVertexArray(0);
}

void Mesh::draw(const Shader& shader)
{
    // bind appropriate textures
    unsigned int diffuseNr  = 1;
    unsigned int specularNr = 1;
    unsigned int normalNr   = 1;
    unsigned int heightNr   = 1;
    for(int i = 0; i < textures.size(); i++)
    {
        glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
        // retrieve texture number (the N in diffuse_textureN)
        std::string number;
        Texture* texture = textures[i];
        std::string name = texture->typeName;
        if(name == "texture_diffuse")
            number = std::to_string(diffuseNr++);
        else if(name == "texture_specular")
            number = std::to_string(specularNr++); // transfer unsigned int to string
        else if(name == "texture_normal")
            number = std::to_string(normalNr++); // transfer unsigned int to string
        else if(name == "texture_height")
            number = std::to_string(heightNr++); // transfer unsigned int to string
        else
            throw std::runtime_error("Unknown texture type: " + name);

        // now set the sampler to the correct texture unit
        shader.setInt(name + number, i);
        // and finally bind the texture
        texture->bind();
    }

    // draw mesh
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(_indices.size()), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);

    // always good practice to set everything back to defaults once configured.
    glActiveTexture(GL_TEXTURE0);
}

void Mesh::getVertices(std::vector<glm::vec3>& vertices) const
{
    vertices.reserve(_vertices.size());
    for (auto& vertex : _vertices)
    {
        vertices.push_back(vertex.position);
    }
}

void Mesh::getIndices(std::vector<unsigned int>& indices) const
{
    indices.reserve(_indices.size());
    for (auto& index : _indices)
    {
        indices.push_back(index);
    }
}
