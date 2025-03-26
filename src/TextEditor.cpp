#include "TextEditor.hpp"
#include "SDLException.hpp"
#include <iostream>

TextEditor::TextEditor()
    : inputText(""), cursorIndex(0), textSize(20), textColor{244, 244, 244, 255},
      cursorColor{255, 221, 51, 255}, bgColor{24, 24, 24, 255}, wrapLength(0) {
}

void TextEditor::insertText(const std::string &text) {
    if (cursorIndex >= 0 && cursorIndex <= inputText.length()) {
        inputText.insert(cursorIndex, text);
        cursorIndex += text.length();
    }
}

TextEditor::CursorPos TextEditor::getCursorPosition(int targetIndex, int textWidth) const {
    CursorPos pos = {0, 0, 0};
    int lastSpaceIndex = -1;

    int textLen = static_cast<int>(inputText.length());
    int maxIndex = (targetIndex <= textLen) ? targetIndex : textLen;

    int i = 0;
    while (i < maxIndex) {
        if (inputText[i] == '\n') {
            pos.x = 0;
            pos.y++;
            pos.lineWidth = 0;
            lastSpaceIndex = -1; // Reset index for a new line
            i++;
            continue;
        }

        // Handle word wrap by backtracking to last space index
        if (pos.lineWidth + textWidth > wrapLength) {
            if (lastSpaceIndex >= 0) {
                i = lastSpaceIndex + 1;
                pos.lineWidth = 0;
                lastSpaceIndex = -1;
                pos.x = 0;
            } else {
                pos.lineWidth = textWidth;
                pos.x = 1;
                i++;
            }
            pos.y++;
            continue;
        }

        pos.x++;
        pos.lineWidth += textWidth;
        if (inputText[i] == ' ') {
            lastSpaceIndex = i;
        }

        i++;
    }

    return pos;
}

void TextEditor::backspace() {
    if (!inputText.empty() && cursorIndex > 0) {
        cursorIndex--;
        inputText.erase(cursorIndex, 1);
    }
}

void TextEditor::ctrlBackspace() {
    int originalIndex = cursorIndex;
    findSpace(false);
    int count = originalIndex - cursorIndex;

    if (count > 0) {
        inputText.erase(cursorIndex, count);
    }
}

void TextEditor::deleteKey() {
    if (!inputText.empty() && cursorIndex < inputText.length()) {
        inputText.erase(cursorIndex, 1);
        if (cursorIndex > inputText.length()) {
            cursorIndex = (inputText.length());
        }
    }
}

void TextEditor::ctrlDelete() {
    int originalIndex = cursorIndex;
    findSpace(true);
    int count = cursorIndex - originalIndex;

    if (count > 0) {
        inputText.erase(originalIndex, count);
        if (cursorIndex > (inputText.length())) {
            cursorIndex = (inputText.length());
        } else {
            cursorIndex = originalIndex;
        }
    }
}

void TextEditor::findSpace(bool dir) {
    if (!inputText.empty()) {
        if (dir == true) {
            // Search forward
            if (cursorIndex < inputText.length()) {
                int count = 1;
                for (int i = cursorIndex; i < inputText.length(); i++) {
                    if (i < inputText.length() - 1 && inputText[i] == ' ' &&
                        inputText[i + 1] == ' ') {
                        ;
                    } else if (inputText[i] == ' ' || inputText[i] == '\n') {
                        break;
                    }
                    count++;
                }
                cursorIndex = (cursorIndex + count >= inputText.length()) ? inputText.length()
                                                                          : (cursorIndex + count);
            }
        } else {
            // Search backward
            if (cursorIndex > 0) {
                int count = 1;
                for (int i = cursorIndex - 2; i >= 0; i--) {
                    if (i > 0 && inputText[i] == ' ' && inputText[i - 1] == ' ') {
                        ;
                    } else if (inputText[i] == ' ' || inputText[i] == '\n') {
                        break;
                    }
                    count++;
                }
                cursorIndex = (cursorIndex < 0) ? 0 : (cursorIndex - count);
            }
        }
    }
}

void TextEditor::setTextSize(int size) {
    textSize = (size < 15) ? 15 : ((size > 180) ? 180 : size);
}

void TextEditor::moveCursor(int delta) {
    cursorIndex = std::max(0, std::min(static_cast<int>(inputText.length()), cursorIndex + delta));
}

void TextEditor::moveCursorVertical(int lines) {
    TTF_Font *font =
        static_cast<TTF_Font *>(scp(TTF_OpenFont("IosevkaNerdFont-Regular.ttf", textSize)));
    int textWidth, textHeight;
    scc(TTF_SizeText(font, " ", &textWidth, &textHeight)); // Monospace assumption
    TTF_CloseFont(font);

    CursorPos currentPos = getCursorPosition(cursorIndex, textWidth);
    int currentLine = currentPos.y;
    int currentColumn = currentPos.x;
    int textLen = static_cast<int>(inputText.length());

    int targetLine = currentLine + lines;
    if (targetLine < 0) {
        targetLine = 0;
    }

    int validIndex = cursorIndex;

    for (int i = 0; i < textLen; i++) {
        CursorPos pos = getCursorPosition(i, textWidth);
        if (pos.y == targetLine) {
            validIndex = i;
            if (pos.x >= currentColumn) {
                cursorIndex = i;
                return;
            }
        } else if (pos.y > targetLine) {
            cursorIndex = validIndex;
            return;
        }
    }
    cursorIndex = validIndex;
}

void TextEditor::setWrapLength(int width) {
    wrapLength = width - 40;
}

void TextEditor::renderText(SDL_Renderer *renderer, int textX, int textY) const {
    if (inputText.empty())
        return;

    TTF_Font *font =
        static_cast<TTF_Font *>(scp(TTF_OpenFont("IosevkaNerdFont-Regular.ttf", textSize)));
    SDL_Surface *textSurface = static_cast<SDL_Surface *>(
        scp(TTF_RenderUTF8_LCD_Wrapped(font, inputText.c_str(), textColor, bgColor, wrapLength)));
    SDL_Texture *textTexture =
        static_cast<SDL_Texture *>(scp(SDL_CreateTextureFromSurface(renderer, textSurface)));

    SDL_Rect textRect = {textX, textY, 0, 0};
    scc(SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h));
    scc(SDL_RenderCopy(renderer, textTexture, nullptr, &textRect));

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

// TODO: curosr inside wrapped word jumps to prev line
void TextEditor::renderCursor(SDL_Renderer *renderer, int textX, int textY) const {
    TTF_Font *font =
        static_cast<TTF_Font *>(scp(TTF_OpenFont("IosevkaNerdFont-Regular.ttf", textSize)));
    int textWidth, textHeight;
    scc(TTF_SizeText(font, " ", &textWidth, &textHeight)); // Monospace assumption
    TTF_CloseFont(font);

    CursorPos pos = getCursorPosition(cursorIndex, textWidth);

    int pixelCursorX = textX + pos.x * textWidth;
    int pixelCursorY = textY + pos.y * textHeight;
    SDL_Rect cursorRect = {pixelCursorX, pixelCursorY, textWidth, textHeight};
    scc(SDL_SetRenderDrawColor(renderer, cursorColor.r, cursorColor.g, cursorColor.b, 255));
    scc(SDL_RenderFillRect(renderer, &cursorRect));
}

void TextEditor::render(SDL_Renderer *renderer, int textX, int textY) const {
    renderText(renderer, textX, textY);
    renderCursor(renderer, textX, textY);
}