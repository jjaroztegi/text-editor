#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextEditor {
private:
    std::string inputText;
    int cursorIndex;
    int textSize;
    SDL_Color textColor;
    SDL_Color cursorColor;
    SDL_Color bgColor;
    int wrapLength;

    void renderText(SDL_Renderer *renderer, int textX, int textY) const;
    void renderCursor(SDL_Renderer *renderer, int textX, int textY) const;

public:
    TextEditor();
    ~TextEditor() = default;

    void insertText(const std::string &text);
    void backspace();
    void moveCursor(int delta);         // For LEFT/RIGHT
    void moveCursorVertical(int lines); // For UP/DOWN (TODO)

    void setWrapLength(int width);
    void setTextSize(int size);
    int getTextSize() const {
        return textSize;
    }

    // Rendering
    void render(SDL_Renderer *renderer, int textX, int textY) const;

    // TODO: Add methods for selection, save/load, undo/redo, etc.
};
