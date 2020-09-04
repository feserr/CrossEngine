/*
 * Copyright 2020 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_CROSSERRORS_H_
#define CROSSENGINE_CROSSERRORS_H_

#include <string>

#include "cross_errors.inl"

namespace CrossEngine {

enum Result { OK = 0, FAIL = 1 };

/**
 * @brief Prints the message and shutdown the app.
 *
 * @param[in] error_string The error message.
 */
void FatalError(const std::string &error_string);
}  // namespace CrossEngine

#endif  // CROSSENGINE_CROSSERRORS_H_
