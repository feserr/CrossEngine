#pragma once

#include <glm/glm.hpp>
#include <CrossEngine/Vertex.h>
#include <CrossEngine/CrossTexture.h>

struct Cell;

// POD
struct Ball {
    Ball(float radius, float mass, const glm::vec2& pos,
         const glm::vec2& vel, CrossEngine::CrossTexture texture,
         const CrossEngine::ColorRGBA8& color);

    float radius; 
    float mass; 
    glm::vec2 velocity;
    glm::vec2 position;
    CrossEngine::CrossTexture texture;
    CrossEngine::ColorRGBA8 color;
    Cell* ownerCell = nullptr;
    int cellVectorIndex = -1;
};
