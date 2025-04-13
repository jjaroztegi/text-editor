#include "SDLException.hpp"

#include <iostream>

const char *SDLException::what() const noexcept {
    return SDL_GetError();
}

void scc(int code) {
    if (code < 0) {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        throw SDLException();
    }
}

void *scp(void *ptr) {
    if (ptr == nullptr) {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        throw SDLException();
    }
    return ptr;
}