#include <terrain/Noise.h>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <random>


void Noise::_createPermutation(int size)
{
    _permutation.reserve(size);
    for (int i = 0; i < size; i++)
    {
        _permutation.push_back(i);
    }
    std::shuffle(std::begin(_permutation), std::end(_permutation), *_rng);
}

void Noise::_createOffsets(int size)
{
    _offsets.resize(size);
    for (int i = 0; i < size; i++)
    {
        _offsets[i].reserve(size);
        for (int j = 0; j < size; j++)
        {
            _offsets[i].push_back((*_distribution)(*_rng));
        }
    }
}

float Noise::_getOffset(int X, int Y) const
{
    X %= _offsets.size();
    Y %= _offsets.size();
    return _offsets[X][Y];
}

int Noise::_getHash(int X, int Y) const
{
    X %= _permutation.size();
    Y %= _permutation.size();
    int index = (_permutation[X] + Y) % _permutation.size();
    return _permutation[index];
}

float Noise::_linearInterpolation(float percentage, float value1, float value2)
{
    return value1 + (value2 - value1) * percentage;
}

float Noise::_fade(float interpolatedValue)
{
    float result = 6.0f * interpolatedValue - 15.0f;
    result *= interpolatedValue;
    result += 10.0f;
    result *= pow(interpolatedValue, 3.0f);
    return result;
}

Noise::Noise(int permutationSize, float minOffset, float maxOffset)
{
    int seed = std::chrono::system_clock::now().time_since_epoch().count();
    _rng = std::make_shared<std::mt19937>(seed);
    if (minOffset > maxOffset)
    {
        throw std::invalid_argument("minOffset must be greater than maxOffset");
    }
    _distribution = std::make_shared<std::uniform_real_distribution<float>>(minOffset, maxOffset);
    _createPermutation(permutationSize);
    _createOffsets(permutationSize);
}

Noise::Noise(int permutationSize, float minOffset, float maxOffset, int seed)
{
    _rng = std::make_shared<std::mt19937>(seed);
    if (minOffset > maxOffset)
    {
        throw std::invalid_argument("minOffset must be greater than maxOffset");
    }
    _distribution = std::make_shared<std::uniform_real_distribution<float>>(minOffset, maxOffset);
    _createPermutation(permutationSize);
    _createOffsets(permutationSize);
}


glm::vec2 Noise::_getConstantVector(int hash) const
{
    return _constantVectors[hash % 4];
}


float Noise::_generateOctave(float x, float y) const
{
    float xRounded = floor(x);
    float yRounded = floor(y);

    int gridX = static_cast<int>(xRounded) % _permutation.size();
    int gridY = static_cast<int>(yRounded) % _permutation.size();

    float cellX = x - xRounded;
    float cellY = y - yRounded;

    glm::vec2 topRight = glm::vec2(cellX - 1.0f, cellY - 1.0f);
    glm::vec2 topLeft = glm::vec2(cellX, cellY - 1.0f);
    glm::vec2 bottomRight = glm::vec2(cellX - 1.0f, cellY);
    glm::vec2 bottomLeft = glm::vec2(cellX, cellY);

    int hashTopRight = _getHash(gridX + 1, gridY + 1);
    int hashTopLeft = _getHash(gridX, gridY + 1);
    int hashBottomRight = _getHash(gridX + 1, gridY);
    int hashBottomLeft = _getHash(gridX, gridY);

    float dotTopRight = glm::dot(topRight, _getConstantVector(hashTopRight));
    float dotTopLeft = glm::dot(topLeft, _getConstantVector(hashTopLeft));
    float dotBottomRight = glm::dot(bottomRight, _getConstantVector(hashBottomRight));
    float dotBottomLeft = glm::dot(bottomLeft, _getConstantVector(hashBottomLeft));

    dotTopRight += _getOffset(gridX + 1, gridY + 1);
    dotTopLeft += _getOffset(gridX, gridY + 1);
    dotBottomRight += _getOffset(gridX + 1, gridY);
    dotBottomLeft += _getOffset(gridX, gridY);

    float percentageX = _fade(cellX);
    float percentageY = _fade(cellY);

        return _linearInterpolation(
            percentageX,
            _linearInterpolation(percentageY, dotBottomLeft, dotTopLeft),
            _linearInterpolation(percentageY, dotBottomRight, dotTopRight)
        );
}

float Noise::generate(float x, float y, int octaves, float amplitude, float frequency,
                        float amplitudeFactor, float frequencyFactor)
{
    float result = 0.0f;
    for (int octave = 0; octave < octaves; octave++)
    {
        result += amplitude * _generateOctave(x * frequency, y * frequency);
        amplitude *= amplitudeFactor;
        frequency *= frequencyFactor;
    }
    return result;
}
