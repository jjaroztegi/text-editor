#include "SDLException.hpp"

#include <iostream>

const char *SDLException::what() const noexcept {
    return SDL_GetError();
}

void scc(bool success) {
    if (!success) {
        const char *error = SDL_GetError();
        if (error && *error != '\0') {
            std::cerr << "SDL Error: " << error << std::endl;
        } else {
            std::cerr << "SDL Error: Unknown error" << std::endl;
        }
        throw SDLException();
    }
}

void *scp(void *ptr) {
    if (ptr == nullptr) {
        const char *error = SDL_GetError();
        if (error && *error != '\0') {
            std::cerr << "SDL Error: " << error << std::endl;
        } else {
            std::cerr << "SDL Error: Null pointer returned" << std::endl;
        }
        throw SDLException();
    }
    return ptr;
}