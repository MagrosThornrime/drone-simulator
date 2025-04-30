#pragma once
#include <vector>
#include <glm/glm.hpp>

class Noise
{
    std::vector<int> _permutation;
    const glm::vec2 _constantVectors[4] = {
        glm::vec2(1.0, 1.0),
        glm::vec2(-1.0, 1.0),
        glm::vec2(-1.0, -1.0),
        glm::vec2(1.0, -1.0),
    };

    int _getHash(int X, int Y) const;
    void _createPermutation(int size, int seed);

    static float _linearInterpolation(float percentage, float value1, float value2);
    static float _fade(float interpolatedValue);
    float _generateOctave(float x, float y) const;
    glm::vec2 _getConstantVector(int hash) const;

public:
    explicit Noise(int permutationSize);
    Noise(int permutationSize, int seed);
    float generate(float x, float y, int octaves, float amplitude, float frequency,
                    float amplitudeFactor, float frequencyFactor);
};
