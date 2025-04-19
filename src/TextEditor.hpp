#pragma once

#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <filesystem>
#include <stack>
#include <string>

class TextEditor {
private:
    std::filesystem::path fontPath;
    std::string inputText;
    int cursorIndex;
    bool selectionActive;
    int selectionStart;
    int textSize;
    SDL_Color textColor;
    SDL_Color cursorColor;
    SDL_Color bgColor;
    int wrapLength;
    bool searching;
    std::string searchQuery;

    struct CursorPos {
        int x, y, lineWidth;
    };
    CursorPos getCursorPosition(int targetIndex, int textWidth) const;

    struct UndoState {
        std::string text;
        int cursor;
        int selectionStart;
        bool selectionActive;
    };
    std::stack<UndoState> undoStack;
    std::stack<UndoState> redoStack;

    void renderText(SDL_Renderer *renderer, int textX, int textY) const;
    void renderCursor(SDL_Renderer *renderer, int textX, int textY) const;
    void renderSelection(SDL_Renderer *renderer, int textX, int textY, int textWidth) const;
    void saveStateForUndo();

public:
    TextEditor();
    ~TextEditor() = default;

    void insertText(const std::string &text);
    void backspace();
    void ctrlBackspace();
    void deleteKey();
    void ctrlDelete();
    void findSpace(bool dir);
    void moveCursor(int delta);
    void moveCursorVertical(int lines);
    void moveWord(bool right);

    void setWrapLength(int width);
    void setTextSize(int size);
    int getTextSize() const {
        return textSize;
    }
    int getCursorIndex() {
        return cursorIndex;
    }

    void startSelection();
    void updateSelection(int newCursor);
    void endSelection();
    bool isSearching() {
        return searching;
    }

    void copyToClipboard();
    void pasteFromClipboard();
    void saveToFile(const std::string &filePath);
    void loadFromFile(const std::string &filePath);
    void undo();
    void redo();

    void startSearch();
    void stopSearch();
    bool searchNext();
    void insertSearchQuery(const std::string &text);

    void render(SDL_Renderer *renderer, int textX, int textY) const;
};