/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef PONG_SRC_PLAYER_H_
#define PONG_SRC_PLAYER_H_

#include <crossengine/sprite.h>
#include <crossengine/sprite_batch.h>
#include <crossengine/tile_sheet.h>
#include <crossengine/vertex.h>
#include "ball.h"

enum class PlayerMoveState { STANDING, MOVING };
enum class PlayerType { PLAYERONE, PLAYERTWO, BOT };

class Player {
 public:
  /**
   * @brief Initialize the player.
   *
   * @param[in] position The position.
   * @param[in] draw_dimensions The image dimensions.
   * @param[in] collision_dimensions The collision dimensions.
   * @param[in] color The color.
   * @param[in] player_type The player type: player or bot.
   */
  void Init(const glm::vec2& position, const glm::vec2& draw_dimensions,
            const glm::vec2& collision_dimensions,
            const CrossEngine::ColorRGBA8 color, const PlayerType player_type);

  /**
   * @brief Destroy the player.
   */
  void Destroy();

  /**
   * @brief Render the player in the sprite batch.
   *
   * @param sprite_batch The main sprite batch.
   */
  void Draw(CrossEngine::SpriteBatch* sprite_batch);

  /**
   * @brief Main loop of the player.
   *
   * @param delta_time The delta time.
   * @param window_size The size of the window.
   * @param ball The ball.
   */
  void Update(const float delta_time, const glm::vec2& window_size, Ball* ball);

  /**
   * @brief Get the position object.
   *
   * @return const glm::vec2 The position of the player.
   */
  const glm::vec2 GetPosition() const {
    glm::vec2 rv;
    rv.x = position_.x;
    rv.y = position_.y;
    return rv;
  }

  /**
   * @brief Get the draw dimensions object.
   *
   * @return const glm::vec2& The draw dimensions.
   */
  const glm::vec2& GetDrawDims() const { return draw_dimensions_; }

  const glm::vec2& GetCollisionDims() const { return collision_dimensions_; }

  const CrossEngine::ColorRGBA8& GetColor() const { return color_; }

 private:
  glm::vec2 position_;
  glm::vec2 draw_dimensions_;
  glm::vec2 collision_dimensions_;
  CrossEngine::ColorRGBA8 color_;
  CrossEngine::TileSheet texture_;
  PlayerMoveState move_state_ = PlayerMoveState::STANDING;
  glm::vec2 velocity_;
  PlayerType player_type_;
};

#endif  // PONG_SRC_PLAYER_H_
