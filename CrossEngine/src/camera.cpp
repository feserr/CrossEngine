/*
 * Copyright 2013 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 * Modified:
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#include "crossengine/camera.h"

#include <bx/allocator.h>
#include <bx/math.h>
#include <bx/timer.h>

#include "entry/cmd.h"
#include "entry/entry.h"
#include "entry/input.h"

namespace CrossEngine {
int cmdMove(CmdContext* /*_context*/, void* /*_userData*/, int _argc,
            char const* const* _argv) {
  if (_argc > 1) {
    if (0 == bx::strCmp(_argv[1], "forward")) {
      CameraSetKeyState(CAMERA_KEY_FORWARD, true);
      return 0;
    } else if (0 == bx::strCmp(_argv[1], "left")) {
      CameraSetKeyState(CAMERA_KEY_LEFT, true);
      return 0;
    } else if (0 == bx::strCmp(_argv[1], "right")) {
      CameraSetKeyState(CAMERA_KEY_RIGHT, true);
      return 0;
    } else if (0 == bx::strCmp(_argv[1], "backward")) {
      CameraSetKeyState(CAMERA_KEY_BACKWARD, true);
      return 0;
    } else if (0 == bx::strCmp(_argv[1], "up")) {
      CameraSetKeyState(CAMERA_KEY_UP, true);
      return 0;
    } else if (0 == bx::strCmp(_argv[1], "down")) {
      CameraSetKeyState(CAMERA_KEY_DOWN, true);
      return 0;
    }
  }

  return 1;
}

static void cmd(const void* _userData) { cmdExec((const char*)_userData); }

static const InputBinding s_camBindings[] = {
    {entry::Key::KeyW, entry::Modifier::None, 0, cmd, "move forward"},
    {entry::Key::GamepadUp, entry::Modifier::None, 0, cmd, "move forward"},
    {entry::Key::KeyA, entry::Modifier::None, 0, cmd, "move left"},
    {entry::Key::GamepadLeft, entry::Modifier::None, 0, cmd, "move left"},
    {entry::Key::KeyS, entry::Modifier::None, 0, cmd, "move backward"},
    {entry::Key::GamepadDown, entry::Modifier::None, 0, cmd, "move backward"},
    {entry::Key::KeyD, entry::Modifier::None, 0, cmd, "move right"},
    {entry::Key::GamepadRight, entry::Modifier::None, 0, cmd, "move right"},
    {entry::Key::KeyQ, entry::Modifier::None, 0, cmd, "move down"},
    {entry::Key::GamepadShoulderL, entry::Modifier::None, 0, cmd, "move down"},
    {entry::Key::KeyE, entry::Modifier::None, 0, cmd, "move up"},
    {entry::Key::GamepadShoulderR, entry::Modifier::None, 0, cmd, "move up"},

    INPUT_BINDING_END};

struct Camera {
  struct MouseCoords {
    int32_t m_mx;
    int32_t m_my;
  };

  Camera() {
    reset();
    entry::MouseState mouseState;
    update(0.0f, mouseState);

    cmdAdd("move", cmdMove);
    inputAddBindings("camBindings", s_camBindings);
  }

  ~Camera() { inputRemoveBindings("camBindings"); }

  void reset() {
    m_mouseNow.m_mx = 0;
    m_mouseNow.m_my = 0;
    m_mouseLast.m_mx = 0;
    m_mouseLast.m_my = 0;
    m_eye.x = 0.0f;
    m_eye.y = 0.0f;
    m_eye.z = -35.0f;
    m_at.x = 0.0f;
    m_at.y = 0.0f;
    m_at.z = -1.0f;
    m_up.x = 0.0f;
    m_up.y = 1.0f;
    m_up.z = 0.0f;
    m_horizontalAngle = 0.01f;
    m_verticalAngle = 0.0f;
    m_mouseSpeed = 0.0020f;
    m_gamepadSpeed = 0.04f;
    m_moveSpeed = 30.0f;
    m_keys = 0;
    m_mouseDown = false;
  }

  void setKeyState(uint8_t _key, bool _down) {
    m_keys &= ~_key;
    m_keys |= _down ? _key : 0;
  }

  void update(float _deltaTime, const entry::MouseState& _mouseState) {
    if (!m_mouseDown) {
      m_mouseLast.m_mx = _mouseState.m_mx;
      m_mouseLast.m_my = _mouseState.m_my;
    }

    m_mouseDown = !!_mouseState.m_buttons[entry::MouseButton::Right];

    if (m_mouseDown) {
      m_mouseNow.m_mx = _mouseState.m_mx;
      m_mouseNow.m_my = _mouseState.m_my;
    }

    if (m_mouseDown) {
      int32_t deltaX = m_mouseNow.m_mx - m_mouseLast.m_mx;
      int32_t deltaY = m_mouseNow.m_my - m_mouseLast.m_my;

      m_horizontalAngle += m_mouseSpeed * float(deltaX);
      m_verticalAngle -= m_mouseSpeed * float(deltaY);

      m_mouseLast.m_mx = m_mouseNow.m_mx;
      m_mouseLast.m_my = m_mouseNow.m_my;
    }

    entry::GamepadHandle handle = {0};
    m_horizontalAngle +=
        m_gamepadSpeed *
        inputGetGamepadAxis(handle, entry::GamepadAxis::RightX) / 32768.0f;
    m_verticalAngle -= m_gamepadSpeed *
                       inputGetGamepadAxis(handle, entry::GamepadAxis::RightY) /
                       32768.0f;
    const int32_t gpx = inputGetGamepadAxis(handle, entry::GamepadAxis::LeftX);
    const int32_t gpy = inputGetGamepadAxis(handle, entry::GamepadAxis::LeftY);
    m_keys |= gpx < -16834 ? CAMERA_KEY_LEFT : 0;
    m_keys |= gpx > 16834 ? CAMERA_KEY_RIGHT : 0;
    m_keys |= gpy < -16834 ? CAMERA_KEY_FORWARD : 0;
    m_keys |= gpy > 16834 ? CAMERA_KEY_BACKWARD : 0;

    const bx::Vec3 direction = {
        bx::cos(m_verticalAngle) * bx::sin(m_horizontalAngle),
        bx::sin(m_verticalAngle),
        bx::cos(m_verticalAngle) * bx::cos(m_horizontalAngle),
    };

    const bx::Vec3 right = {
        bx::sin(m_horizontalAngle - bx::kPiHalf),
        0,
        bx::cos(m_horizontalAngle - bx::kPiHalf),
    };

    const bx::Vec3 up = bx::cross(right, direction);

    if (m_keys & CAMERA_KEY_FORWARD) {
      const bx::Vec3 pos = m_eye;
      const bx::Vec3 tmp = bx::mul(direction, _deltaTime * m_moveSpeed);

      m_eye = bx::add(pos, tmp);
      setKeyState(CAMERA_KEY_FORWARD, false);
    }

    if (m_keys & CAMERA_KEY_BACKWARD) {
      const bx::Vec3 pos = m_eye;
      const bx::Vec3 tmp = bx::mul(direction, _deltaTime * m_moveSpeed);

      m_eye = bx::sub(pos, tmp);
      setKeyState(CAMERA_KEY_BACKWARD, false);
    }

    if (m_keys & CAMERA_KEY_LEFT) {
      const bx::Vec3 pos = m_eye;
      const bx::Vec3 tmp = bx::mul(right, _deltaTime * m_moveSpeed);

      m_eye = bx::add(pos, tmp);
      setKeyState(CAMERA_KEY_LEFT, false);
    }

    if (m_keys & CAMERA_KEY_RIGHT) {
      const bx::Vec3 pos = m_eye;
      const bx::Vec3 tmp = bx::mul(right, _deltaTime * m_moveSpeed);

      m_eye = bx::sub(pos, tmp);
      setKeyState(CAMERA_KEY_RIGHT, false);
    }

    if (m_keys & CAMERA_KEY_UP) {
      const bx::Vec3 pos = m_eye;
      const bx::Vec3 tmp = bx::mul(up, _deltaTime * m_moveSpeed);

      m_eye = bx::add(pos, tmp);
      setKeyState(CAMERA_KEY_UP, false);
    }

    if (m_keys & CAMERA_KEY_DOWN) {
      const bx::Vec3 pos = m_eye;
      const bx::Vec3 tmp = bx::mul(up, _deltaTime * m_moveSpeed);

      m_eye = bx::sub(pos, tmp);
      setKeyState(CAMERA_KEY_DOWN, false);
    }

    m_at = bx::add(m_eye, direction);
    m_up = bx::cross(right, direction);
  }

  void getViewMtx(float* _viewMtx) {
    bx::mtxLookAt(_viewMtx, bx::load<bx::Vec3>(&m_eye.x),
                  bx::load<bx::Vec3>(&m_at.x), bx::load<bx::Vec3>(&m_up.x));
  }

  void setPosition(const bx::Vec3& _pos) { m_eye = _pos; }

  void setVerticalAngle(float _verticalAngle) {
    m_verticalAngle = _verticalAngle;
  }

  void setHorizontalAngle(float _horizontalAngle) {
    m_horizontalAngle = _horizontalAngle;
  }

  MouseCoords m_mouseNow;
  MouseCoords m_mouseLast;

  bx::Vec3 m_eye;
  bx::Vec3 m_at;
  bx::Vec3 m_up;
  float m_horizontalAngle;
  float m_verticalAngle;

  float m_mouseSpeed;
  float m_gamepadSpeed;
  float m_moveSpeed;

  uint8_t m_keys;
  bool m_mouseDown;
};

static Camera* s_camera = NULL;

void CameraCreate() { s_camera = BX_NEW(entry::getAllocator(), Camera); }

void CameraDestroy() {
  BX_DELETE(entry::getAllocator(), s_camera);
  s_camera = NULL;
}

void CameraSetPosition(const bx::Vec3& _pos) { s_camera->setPosition(_pos); }

void CameraSetHorizontalAngle(float _horizontalAngle) {
  s_camera->setHorizontalAngle(_horizontalAngle);
}

void CameraSetVerticalAngle(float _verticalAngle) {
  s_camera->setVerticalAngle(_verticalAngle);
}

void CameraSetKeyState(uint8_t _key, bool _down) {
  s_camera->setKeyState(_key, _down);
}

void CameraGetViewMtx(float* _viewMtx) { s_camera->getViewMtx(_viewMtx); }

bx::Vec3 CameraGetPosition() { return s_camera->m_eye; }

bx::Vec3 CameraGetAt() { return s_camera->m_at; }

void CameraUpdate(float _deltaTime, const entry::MouseState& _mouseState) {
  s_camera->update(_deltaTime, _mouseState);
}

bool IsBoxInView(const bx::Vec3& position, const bx::Vec3& dimensions,
                 const float width, const float height) {
  float scale = 1.0f;
  bx::Vec3 scaledScreenDimensions =
      bx::div(bx::Vec3(width, height, 0.0f), scale);

  // The minimum distance before a collision occurs
  const float MIN_DISTANCE_X =
      dimensions.x / 2.0f + scaledScreenDimensions.x / 2.0f;
  const float MIN_DISTANCE_Y =
      dimensions.y / 2.0f + scaledScreenDimensions.y / 2.0f;

  // Center position of the parameters.
  bx::Vec3 centerPos = bx::add(position, bx::div(dimensions, 2.0f));
  // Center position of the camera.
  bx::Vec3 camera_pos = CameraGetPosition();
  bx::Vec3 centerCameraPos(camera_pos.x, camera_pos.y, 0.0f);
  // Vector from the input to the camera.
  bx::Vec3 distVec = bx::sub(centerPos, centerCameraPos);

  // Get the depth of the collision.
  float xDepth = MIN_DISTANCE_X - bx::abs(distVec.x);
  float yDepth = MIN_DISTANCE_Y - bx::abs(distVec.y);

  // If both the depths are > 0, then we collided.
  if (xDepth > 0 && yDepth > 0) {
    // There was a collision
    return true;
  }

  return false;
}
}  // namespace CrossEngine
