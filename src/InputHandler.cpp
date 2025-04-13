#include "InputHandler.hpp"

InputHandler::InputHandler(TextEditor &e) : editor(e) {
}

void InputHandler::handleEvent(const SDL_Event &event) {
    switch (event.type) {
        case SDL_TEXTINPUT:
            if (editor.isSearching()) {
                editor.insertSearchQuery(event.text.text);
                editor.searchNext();
            } else {
                editor.insertText(event.text.text);
            }
            break;
        case SDL_KEYDOWN:
            SDL_Keymod modifier = SDL_GetModState();
            SDL_Keycode key = event.key.keysym.sym;
            switch (key) {
                case SDLK_BACKSPACE:
                    if (modifier & KMOD_CTRL) {
                        editor.ctrlBackspace();
                    } else {
                        editor.backspace();
                    }
                    break;
                case SDLK_DELETE:
                    if (modifier & KMOD_CTRL) {
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
                    if (modifier & KMOD_CTRL)
                        editor.moveWord(false);
                    else
                        editor.moveCursor(-1);
                    if (modifier & KMOD_SHIFT)
                        editor.updateSelection(editor.getCursorIndex());
                    break;
                case SDLK_RIGHT:
                    if (modifier & KMOD_CTRL)
                        editor.moveWord(true);
                    else
                        editor.moveCursor(1);
                    if (modifier & KMOD_SHIFT)
                        editor.updateSelection(editor.getCursorIndex());
                    break;
                case SDLK_UP:
                    editor.moveCursorVertical(-1);
                    if (modifier & KMOD_SHIFT)
                        editor.updateSelection(editor.getCursorIndex());
                    break;
                case SDLK_DOWN:
                    editor.moveCursorVertical(1);
                    if (modifier & KMOD_SHIFT)
                        editor.updateSelection(editor.getCursorIndex());
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
                // Search
                case SDLK_f:
                    if (modifier & KMOD_CTRL)
                        editor.startSearch();
                    break;
                // Save, load
                case SDLK_s:
                    if (modifier & KMOD_CTRL)
                        editor.saveToFile("output.txt");
                    break;
                case SDLK_o:
                    if (modifier & KMOD_CTRL)
                        editor.loadFromFile("example.txt");
                    break;
                // Undo, redo
                case SDLK_z:
                    if (modifier & KMOD_CTRL)
                        editor.undo();
                    break;
                case SDLK_y:
                    if (modifier & KMOD_CTRL)
                        editor.redo();
                    break;
                // Copy, paste
                case SDLK_c:
                    if (modifier & KMOD_CTRL)
                        editor.copyToClipboard();
                    break;
                case SDLK_v:
                    if (modifier & KMOD_CTRL)
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
    return (event.type == SDL_QUIT) ||
           (event.type == SDL_KEYDOWN && (SDL_GetModState() & KMOD_CTRL) && event.key.keysym.sym == SDLK_q);
}