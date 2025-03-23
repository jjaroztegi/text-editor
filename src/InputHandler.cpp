#include "InputHandler.hpp"

InputHandler::InputHandler(TextEditor &e) : editor(e) {
}

void InputHandler::handleEvent(const SDL_Event &event) {
    switch (event.type) {
        case SDL_TEXTINPUT:
            editor.insertText(event.text.text);
            break;
        case SDL_KEYDOWN:
            SDL_Keymod modifier = SDL_GetModState();
            SDL_Keycode key = event.key.keysym.sym;
            switch (key) {
                case SDLK_BACKSPACE:
                    editor.backspace();
                    break;
                case SDLK_RETURN:
                    editor.insertText("\n");
                    break;
                // Arrow movements
                case SDLK_LEFT:
                    editor.moveCursor(-1);
                    break;
                case SDLK_RIGHT:
                    editor.moveCursor(1);
                    break;
                case SDLK_UP:
                    editor.moveCursorVertical(-1);
                    break;
                case SDLK_DOWN:
                    editor.moveCursorVertical(1);
                    break;
                // Zoom
                case SDLK_PLUS:
                    if (modifier & KMOD_CTRL) {
                        editor.setTextSize(editor.getTextSize() + 5);
                    }
                    break;
                case SDLK_MINUS:
                    if (modifier & KMOD_CTRL) {
                        editor.setTextSize(editor.getTextSize() - 5);
                    }
                    break;
            }
            break;
    }
}

bool InputHandler::shouldQuit(const SDL_Event &event) const {
    return (event.type == SDL_QUIT) ||
           (event.type == SDL_KEYDOWN && (SDL_GetModState() & KMOD_CTRL) &&
            event.key.keysym.sym == SDLK_q);
}