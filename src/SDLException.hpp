#pragma once

#include <SDL3/SDL.h>
#include <exception>

class SDLException : public std::exception {
public:
    const char *what() const noexcept override;
};

void scc(bool success);     // Check return success
void *scp(void *ptr);       // Check null pointer
