/*
 * Copyright 2013 Dario Manesku. All rights reserved.
 * License: https://github.com/bkaradzic/bgfx#license-bsd-2-clause
 * Modified:
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CAMERA_H_HEADER_GUARD
#define CAMERA_H_HEADER_GUARD

#include <bx/math.h>

#include "../entry/entry.h"

#define CAMERA_KEY_FORWARD UINT8_C(0x01)
#define CAMERA_KEY_BACKWARD UINT8_C(0x02)
#define CAMERA_KEY_LEFT UINT8_C(0x04)
#define CAMERA_KEY_RIGHT UINT8_C(0x08)
#define CAMERA_KEY_UP UINT8_C(0x10)
#define CAMERA_KEY_DOWN UINT8_C(0x20)

namespace CrossEngine {
///
void CameraCreate();

///
void CameraDestroy();

///
void CameraSetPosition(const bx::Vec3& _pos);

///
void CameraSetHorizontalAngle(float _horizontalAngle);

///
void CameraSetVerticalAngle(float _verticalAngle);

///
void CameraSetKeyState(uint8_t _key, bool _down);

///
void CameraGetViewMtx(float* _viewMtx);

///
bx::Vec3 CameraGetPosition();

///
bx::Vec3 CameraGetAt();

///
void CameraUpdate(float _deltaTime, const entry::MouseState& _mouseState);

/**
 * @brief Determines if box in view.
 * Simple AABB test to see if a box is in the camera view
 *
 * @param[in] position The position.
 * @param[in] dimensions The dimensions.
 * @param[in] width The width of the camera.
 * @param[in] height The height of the camera.
 * @return True if box in view, False otherwise.
 */
bool IsBoxInView(const bx::Vec3& position, const bx::Vec3& dimensions,
                 const float width, const float height);
}  // namespace CrossEngine

#endif  // CROSSENGINE_CAMERA_H_
