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

void TextEditor::backspace() {
    if (!inputText.empty() && cursorIndex > 0) {
        cursorIndex--;
        inputText.erase(cursorIndex, 1);
    }
}

void TextEditor::setTextSize(int size) {
    textSize = (size < 15) ? 15 : ((size > 180) ? 180 : size);
}

void TextEditor::moveCursor(int delta) {
    cursorIndex = std::max(0, std::min(static_cast<int>(inputText.length()), cursorIndex + delta));
}

void TextEditor::moveCursorVertical(int lines) {
    // TODO: Implement UP/DOWN logic using font metrics and wrapLength
    std::cerr << "moveCursorVertical not implemented yet" << std::endl;
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

void TextEditor::renderCursor(SDL_Renderer *renderer, int textX, int textY) const {
    TTF_Font *font =
        static_cast<TTF_Font *>(scp(TTF_OpenFont("IosevkaNerdFont-Regular.ttf", textSize)));
    int textWidth, textHeight;
    scc(TTF_SizeText(font, " ", &textWidth, &textHeight)); // Monospace assumption
    TTF_CloseFont(font);

    int cursorX = 0, cursorY = 0;
    int lineWidth = 0;
    int lastSpaceIndex = -1;

    int textLen = static_cast<int>(inputText.length());
    int maxIndex = (cursorIndex <= textLen) ? cursorIndex : textLen;

    int i = 0;
    while (i < maxIndex) {
        if (inputText[i] == '\n') {
            cursorX = 0;
            cursorY++;
            lineWidth = 0;
            lastSpaceIndex = -1; // Reset index for a new line
            i++;
            continue;
        }

        // Handle word wrap by backtracking to last space index
        if (lineWidth + textWidth > wrapLength) {
            if (lastSpaceIndex >= 0) {
                i = lastSpaceIndex + 1;
                lineWidth = 0;
                lastSpaceIndex = -1;
                cursorX = 0;
            } else {
                lineWidth = textWidth;
                cursorX = 1;
                i++;
            }
            cursorY++;
            continue;
        }

        cursorX++;
        lineWidth += textWidth;
        if (inputText[i] == ' ') {
            lastSpaceIndex = i;
        }

        i++;
    }

    int pixelCursorX = textX + cursorX * textWidth;
    int pixelCursorY = textY + cursorY * textHeight;
    SDL_Rect cursorRect = {pixelCursorX, pixelCursorY, textWidth, textHeight};
    scc(SDL_SetRenderDrawColor(renderer, cursorColor.r, cursorColor.g, cursorColor.b, 255));
    scc(SDL_RenderFillRect(renderer, &cursorRect));
}

void TextEditor::render(SDL_Renderer *renderer, int textX, int textY) const {
    renderText(renderer, textX, textY);
    renderCursor(renderer, textX, textY);
}