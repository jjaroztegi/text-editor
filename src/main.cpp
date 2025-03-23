#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>

// Handle errors
class SDLException : public std::exception {
public:
    const char *what() const noexcept override { return SDL_GetError(); }
};

// Check return code
void scc(int code) {
    if (code < 0) {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        throw SDLException();
    }
}

// Check null pointer
void *scp(void *ptr) {
    if (ptr == nullptr) {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        throw SDLException();
    }
    return ptr;
}

void render_text(SDL_Renderer *renderer, const std::string &text, int textSize, int x, int y,
                 SDL_Color color, int wrapLength) {
    if (text.empty())
        return; // Prevent zero-width text error at start

    TTF_Font *font =
        static_cast<TTF_Font *>(scp(TTF_OpenFont("IosevkaNerdFont-Regular.ttf", textSize)));
    SDL_Surface *textSurface = static_cast<SDL_Surface *>(
        scp(TTF_RenderText_Blended_Wrapped(font, text.c_str(), color, wrapLength)));
    SDL_Texture *textTexture =
        static_cast<SDL_Texture *>(scp(SDL_CreateTextureFromSurface(renderer, textSurface)));

    SDL_Rect textRect;
    textRect.x = x;
    textRect.y = y;
    scc(SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h));
    scc(SDL_RenderCopy(renderer, textTexture, nullptr, &textRect));

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
    TTF_CloseFont(font);
}

void render_cursor(SDL_Renderer *renderer, const std::string &inputText, int cursorIndex,
                   int textSize, int textX, int textY, SDL_Color cursorColor, int wrapLength) {
    int textWidth, textHeight;
    TTF_Font *font =
        static_cast<TTF_Font *>(scp(TTF_OpenFont("IosevkaNerdFont-Regular.ttf", textSize)));
    scc(TTF_SizeText(font, " ", &textWidth, &textHeight)); // Assume monospace for now
    TTF_CloseFont(font);

    // Calculate characters per line based on wrapLength
    int charsPerLine = wrapLength / textWidth;

    // Calculate cursorX and cursorY based on cursorIndex
    int cursorX = 0;
    int cursorY = 0;
    for (int i = 0; i < cursorIndex && i < static_cast<int>(inputText.length()); i++) {
        if (inputText[i] == '\n') {
            cursorX = 0;
            cursorY++;
        } else {
            cursorX++;
            if (cursorX >= charsPerLine) {
                cursorX = 0;
                cursorY++;
            }
        }
    }

    // Convert to pixel coordinates
    int pixelCursorX = textX + cursorX * textWidth;
    int pixelCursorY = textY + cursorY * textHeight;

    SDL_Rect cursorRect = {pixelCursorX, pixelCursorY, textWidth, textHeight};
    scc(SDL_SetRenderDrawColor(renderer, cursorColor.r, cursorColor.g, cursorColor.b, 255));
    scc(SDL_RenderFillRect(renderer, &cursorRect));
}

int main(int argc, char *argv[]) {
    try {
        std::vector<std::string> args(argv, argv + argc);

        scc(SDL_Init(SDL_INIT_VIDEO));
        scc(TTF_Init());

        SDL_Window *window = static_cast<SDL_Window *>(
            scp(SDL_CreateWindow("Text Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800,
                                 600, SDL_WINDOW_RESIZABLE)));
        SDL_Renderer *renderer = static_cast<SDL_Renderer *>(
            scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)));

        std::string inputText;
        int textSize = 20;
        int cursorIndex = 0;
        SDL_Color textColor = {244, 244, 244, 255};
        SDL_Color cursorColor = {255, 221, 51, 255};

        SDL_StartTextInput();

        bool quit = false;
        while (!quit) {
            SDL_Event event{};
            while (SDL_PollEvent(&event)) {
                switch (event.type) {
                case SDL_QUIT:
                    quit = true;
                    break;
                case SDL_TEXTINPUT:
                    if (cursorIndex >= 0 && cursorIndex <= inputText.length()) {
                        inputText.insert(cursorIndex, event.text.text);
                        cursorIndex++;
                    }
                    break;
                case SDL_KEYDOWN:
                    SDL_Keymod modifier = SDL_GetModState();
                    SDL_Keycode key = event.key.keysym.sym;

                    if (key == SDLK_BACKSPACE && !inputText.empty() && cursorIndex > 0) {
                        cursorIndex--;
                        if (inputText[cursorIndex] == '\n') {
                            // Move cursor to end of previous line if removing newline
                            inputText.erase(cursorIndex, 1);
                            int lastNewline = inputText.rfind('\n', cursorIndex - 1);
                            int lineStart =
                                (lastNewline == std::string::npos) ? 0 : lastNewline + 1;
                            int charsPerLine = (SDL_GetWindowSurface(window)->w - 10) /
                                               TTF_FontHeight(TTF_OpenFont(
                                                   "IosevkaNerdFont-Regular.ttf", textSize));
                            cursorIndex = lineStart + ((cursorIndex - lineStart) % charsPerLine);
                        } else {
                            inputText.erase(cursorIndex, 1);
                        }
                    } else if (key == SDLK_RETURN) {
                        inputText.insert(cursorIndex, "\n");
                        cursorIndex++;
                    } else if (key == SDLK_RIGHT && cursorIndex < inputText.length()) {
                        cursorIndex++;
                    } else if (key == SDLK_LEFT && cursorIndex > 0) {
                        cursorIndex--;
                    } else if (key == SDLK_UP) {
                        // UP arrow logic
                    } else if (key == SDLK_DOWN) {
                        // DOWN arrow logic
                    } else if ((modifier & KMOD_CTRL) && key == SDLK_PLUS) {
                        textSize += 4;
                    } else if ((modifier & KMOD_CTRL) && key == SDLK_MINUS) {
                        textSize -= 4;
                    } else if ((modifier & KMOD_CTRL) && key == SDLK_q) {
                        quit = true;
                    }
                }
            }

            int windowWidth, windowHeight;
            SDL_GetWindowSize(window, &windowWidth, &windowHeight);

            scc(SDL_SetRenderDrawColor(renderer, 24, 24, 24, 255));
            scc(SDL_RenderClear(renderer));

            int textX = 10;
            int textY = 10;
            int wrapLength = windowWidth - textX;
            render_text(renderer, inputText, textSize, textX, textY, textColor,
                        windowWidth - textX);
            render_cursor(renderer, inputText, cursorIndex, textSize, textX, textY, cursorColor,
                          wrapLength);

            SDL_RenderPresent(renderer);
        }

        SDL_StopTextInput();
        TTF_Quit();
        SDL_Quit();
    } catch (const SDLException &e) {
        std::cerr << "SDL Exception: " << e.what() << std::endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    return 0;
}