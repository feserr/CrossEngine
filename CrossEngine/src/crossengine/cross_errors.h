/*
 * Copyright 2017-2019 Elías Serrano. All rights reserved.
 * License: https://github.com/feserr/crossengine#license
 */

#ifndef CROSSENGINE_CROSSERRORS_H_
#define CROSSENGINE_CROSSERRORS_H_

#include <string>

namespace CrossEngine {
/**
 * @brief Prints the erros and shudown the app.
 *
 * @param[in] error_string The error message.
 */
extern void FatalError(const std::string& error_string);
}  // namespace CrossEngine

#endif  // CROSSENGINE_CROSSERRORS_H_
