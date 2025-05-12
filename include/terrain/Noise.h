#pragma once
#include <memory>
#include <random>
#include <vector>
#include <glm/glm.hpp>

class Noise
{
    std::mt19937 _rng;
    std::uniform_real_distribution<float> _distribution;
    std::vector<int> _permutation;
    std::vector<std::vector<float>> _offsets;

    const glm::vec2 _constantVectors[4] = {
        glm::vec2(1.0, 1.0),
        glm::vec2(-1.0, 1.0),
        glm::vec2(-1.0, -1.0),
        glm::vec2(1.0, -1.0),
    };

    int _getHash(int X, int Y) const;
    void _createPermutation(int size);
    void _createOffsets(int size);
    float _getOffset(int x, int y) const;
    static float _linearInterpolation(float percentage, float value1, float value2);
    static float _fade(float interpolatedValue);
    float _generateOctave(float x, float y) const;
    glm::vec2 _getConstantVector(int hash) const;

public:
    explicit Noise(int permutationSize, float minOffset, float maxOffset);
    Noise(int permutationSize, float minOffset, float maxOffset, int seed);
    float generate(float x, float y, int octaves, float amplitude, float frequency,
                    float amplitudeFactor, float frequencyFactor);
};
