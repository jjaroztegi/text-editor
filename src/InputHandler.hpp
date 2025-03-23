#pragma once

#include "TextEditor.hpp"
#include <SDL2/SDL.h>

class InputHandler {
private:
    TextEditor &editor;

public:
    InputHandler(TextEditor &e);
    ~InputHandler() = default;

    void handleEvent(const SDL_Event &event);
    bool shouldQuit(const SDL_Event &event) const;
};