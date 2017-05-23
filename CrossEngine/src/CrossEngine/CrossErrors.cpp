/*
    Copyright [2016] [Elías Serrano]

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#include "CrossEngine/CrossErrors.h"

#include <SDL/SDL.h>
#include <string>
#include <cstdlib>
#include <iostream>

namespace CrossEngine {
    /// Prints out an error message and exits the game
    void FatalError(std::string errorString) {
        std::cout << errorString << std::endl;
        std::cout << "Enter any key to quit...";
        int tmp;
        std::cin >> tmp;
        SDL_Quit();
        exit(69);
    }
}  // namespace CrossEngine
