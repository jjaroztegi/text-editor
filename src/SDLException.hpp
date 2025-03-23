#pragma once

#include <SDL2/SDL.h>
#include <exception>

class SDLException : public std::exception {
public:
    const char *what() const noexcept override;
};

void scc(int code);   // Check return code
void *scp(void *ptr); // Check null pointer
