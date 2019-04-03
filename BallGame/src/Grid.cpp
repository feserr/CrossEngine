/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "grid.h"

#include <cmath>
#include <cstdlib>

Grid::Grid(const int width, const int height, const int cell_size)
    : width_(width), height_(height), cell_size_(cell_size) {
  num_x_cells_ = ceil(static_cast<float>(width_) / cell_size_);
  num_y_cells_ = ceil(static_cast<float>(height_) / cell_size_);

  // Allocate all the cells
  const int BALLS_TO_RESERVE = 20;
  cells_.resize(num_y_cells_ * num_x_cells_);
  for (int i = 0; i < cells_.size(); i++) {
    cells_[i].balls.reserve(BALLS_TO_RESERVE);
  }
}

Grid::~Grid() {}

void Grid::AddBall(Ball* ball) {
  Cell* cell = GetCell(ball->position);
  cell->balls.push_back(ball);
  ball->ownerCell = cell;
  ball->cellVectorIndex = cell->balls.size() - 1;
}

void Grid::AddBall(Ball* ball, Cell* cell) {
  cell->balls.push_back(ball);
  ball->ownerCell = cell;
  ball->cellVectorIndex = cell->balls.size() - 1;
}

Cell* Grid::GetCell(const int x, const int y) {
  int temp_x = x;
  if (x < 0) temp_x = 0;
  if (x >= num_x_cells_) temp_x = num_x_cells_ - 1;

  int temp_y = y;
  if (y < 0) temp_y = 0;
  if (y >= num_y_cells_) temp_y = num_y_cells_ - 1;

  return &cells_[temp_y * num_x_cells_ + temp_x];
}

Cell* Grid::GetCell(const glm::vec2& pos) {
  int cellX = static_cast<int>(pos.x / cell_size_);
  int cellY = static_cast<int>(pos.y / cell_size_);

  return GetCell(cellX, cellY);
}

void Grid::RemoveBallFromCell(Ball* ball) {
  std::vector<Ball*>& balls = ball->ownerCell->balls;
  // Normal vector swap
  balls[ball->cellVectorIndex] = balls.back();
  balls.pop_back();
  // Update vector index
  if (ball->cellVectorIndex < balls.size()) {
    balls[ball->cellVectorIndex]->cellVectorIndex = ball->cellVectorIndex;
  }
  // Set the index of ball to -1.
  ball->cellVectorIndex = -1;
  ball->ownerCell = nullptr;
}
