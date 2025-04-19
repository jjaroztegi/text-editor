#include "InputHandler.hpp"

#include "TextEditor.hpp"

#include <SDL3/SDL.h>

InputHandler::InputHandler(TextEditor &e) : editor(e) {
}

void InputHandler::handleEvent(const SDL_Event &event) {
    switch (event.type) {
        case SDL_EVENT_TEXT_INPUT:
            if (editor.isSearching()) {
                editor.insertSearchQuery(event.text.text);
                editor.searchNext();
            } else {
                editor.insertText(event.text.text);
            }
            break;
        case SDL_EVENT_KEY_DOWN:
            SDL_Keymod modifier = SDL_GetModState();
            SDL_Keycode key = event.key.key;
            switch (key) {
                case SDLK_BACKSPACE:
                    if (modifier & SDL_KMOD_CTRL) {
                        editor.ctrlBackspace();
                    } else {
                        editor.backspace();
                    }
                    break;
                case SDLK_DELETE:
                    if (modifier & SDL_KMOD_CTRL) {
                        editor.ctrlDelete();
                    } else {
                        editor.deleteKey();
                    }
                    break;
                case SDLK_RETURN:
                    editor.insertText("\n");
                    break;
                // Arrow movements
                case SDLK_LEFT:
                    if (modifier & SDL_KMOD_CTRL)
                        editor.moveWord(false);
                    else
                        editor.moveCursor(-1);
                    if (modifier & SDL_KMOD_SHIFT)
                        editor.updateSelection(editor.getCursorIndex());
                    break;
                case SDLK_RIGHT:
                    if (modifier & SDL_KMOD_CTRL)
                        editor.moveWord(true);
                    else
                        editor.moveCursor(1);
                    if (modifier & SDL_KMOD_SHIFT)
                        editor.updateSelection(editor.getCursorIndex());
                    break;
                case SDLK_UP:
                    editor.moveCursorVertical(-1);
                    if (modifier & SDL_KMOD_SHIFT)
                        editor.updateSelection(editor.getCursorIndex());
                    break;
                case SDLK_DOWN:
                    editor.moveCursorVertical(1);
                    if (modifier & SDL_KMOD_SHIFT)
                        editor.updateSelection(editor.getCursorIndex());
                    break;
                // Zoom
                case SDLK_PLUS:
                    if (modifier & SDL_KMOD_CTRL) {
                        editor.setTextSize(editor.getTextSize() + 5);
                    }
                    break;
                case SDLK_MINUS:
                    if (modifier & SDL_KMOD_CTRL) {
                        editor.setTextSize(editor.getTextSize() - 5);
                    }
                    break;
                // Search
                case SDLK_F:
                    if (modifier & SDL_KMOD_CTRL)
                        editor.startSearch();
                    break;
                // Save, load
                case SDLK_S:
                    if (modifier & SDL_KMOD_CTRL)
                        editor.saveToFile("output.txt");
                    break;
                case SDLK_O:
                    if (modifier & SDL_KMOD_CTRL)
                        editor.loadFromFile("example.txt");
                    break;
                // Undo, redo
                case SDLK_Z:
                    if (modifier & SDL_KMOD_CTRL)
                        editor.undo();
                    break;
                case SDLK_Y:
                    if (modifier & SDL_KMOD_CTRL)
                        editor.redo();
                    break;
                // Copy, paste
                case SDLK_C:
                    if (modifier & SDL_KMOD_CTRL)
                        editor.copyToClipboard();
                    break;
                case SDLK_V:
                    if (modifier & SDL_KMOD_CTRL)
                        editor.pasteFromClipboard();
                    break;
                case SDLK_ESCAPE:
                    editor.stopSearch();
                    editor.endSelection();
                    break;
            }
            break;
    }
}

bool InputHandler::shouldQuit(const SDL_Event &event) const {
    return (event.type == SDL_EVENT_QUIT) ||
           (event.type == SDL_EVENT_KEY_DOWN && (SDL_GetModState() & SDL_KMOD_CTRL) && event.key.key == SDLK_Q);
}