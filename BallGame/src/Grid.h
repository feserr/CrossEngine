/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef BALLGAME_SRC_GRID_H_
#define BALLGAME_SRC_GRID_H_

#include <vector>
#include "Ball.h"

struct Cell {
  std::vector<Ball*> balls;
};

class Grid {
  friend class BallController;

 public:
  /**
   * @brief Construct a new Grid object.
   *
   * @param width The width of the grid.
   * @param height The height of the grid.
   * @param cell_size The cell size.
   */
  Grid(const int width, const int height, const int cell_size);

  /**
   * @brief Destroy the Grid object.
   *
   */
  ~Grid();

  /**
   * @brief Adds a ball and determines which cell it belongs to.
   *
   * @param[in] ball The new ball.
   */
  void AddBall(Ball* ball);

  /**
   * @brief Adds a ball to the specified cell.
   *
   * @param[in] ball The new ball.
   * @param[in] cell The cell.
   */
  void AddBall(Ball* ball, Cell* cell);

  /**
   * @brief Gets cell based on cell coordinates.
   *
   * @param[in] x The X axis coordinate.
   * @param[in] y The Y axis coordinate.
   * @return Cell* The selected cell.
   */
  Cell* GetCell(const int x, const int y);

  /**
   * @brief Gets cell based on window coordinates.
   *
   * @param[in] pos The position of the screen.
   * @return Cell* The selected cell.
   */
  Cell* GetCell(const glm::vec2& pos);

  /**
   * @brief Removes a ball from a cell.
   *
   * @param[in] ball The ball to remove.
   */
  void RemoveBallFromCell(Ball* ball);

 private:
  std::vector<Cell> cells_;
  int cell_size_;
  int width_;
  int height_;
  int num_x_cells_;
  int num_y_cells_;
};

#endif  // BALLGAME_SRC_GRID_H_
