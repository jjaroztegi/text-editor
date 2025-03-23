#include <iostream>
#include <string>
#include <vector>

#include <SDL2/SDL.h>
#include <SDL2/SDL_main.h>
#include <SDL2/SDL_ttf.h>

class SDLException : public std::exception {
  public:
    const char *what() const noexcept override { return SDL_GetError(); }
};

void scc(int code) {
    if (code < 0) {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        throw SDLException();
    }
}

void *scp(void *ptr) {
    if (ptr == nullptr) {
        std::cerr << "SDL Error: " << SDL_GetError() << std::endl;
        throw SDLException();
    }
    return ptr;
}

void render_text(SDL_Renderer *renderer, TTF_Font *font,
                 const std::string &text, int x, int y, SDL_Color color) {
    if (text.empty())
        return; // Otherwise Error: Text has zero width

    SDL_Surface *textSurface = static_cast<SDL_Surface *>(
        scp(TTF_RenderText_Solid(font, text.c_str(), color)));
    SDL_Texture *textTexture = static_cast<SDL_Texture *>(
        scp(SDL_CreateTextureFromSurface(renderer, textSurface)));

    SDL_Rect textRect;
    textRect.x = x;
    textRect.y = y;
    SDL_QueryTexture(textTexture, nullptr, nullptr, &textRect.w, &textRect.h);

    scc(SDL_RenderCopy(renderer, textTexture, nullptr, &textRect));

    SDL_DestroyTexture(textTexture);
    SDL_FreeSurface(textSurface);
}

int main(int argc, char *argv[]) {
    try {
        std::vector<std::string> args(argv, argv + argc);

        scc(SDL_Init(SDL_INIT_VIDEO));
        scc(TTF_Init());

        SDL_Window *window = static_cast<SDL_Window *>(scp(SDL_CreateWindow(
            "Text Editor", 0, 30, 800, 600, SDL_WINDOW_RESIZABLE)));
        SDL_Renderer *renderer = static_cast<SDL_Renderer *>(
            scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)));

        TTF_Font *font = static_cast<TTF_Font *>(
            scp(TTF_OpenFont("IosevkaNerdFont-Regular.ttf", 48)));

        std::string inputText = "";
        SDL_Color textColor = {255, 255, 255, 255};

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
                    inputText += event.text.text;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_BACKSPACE &&
                        !inputText.empty()) {
                        inputText.pop_back();
                    }
                }
            }

            scc(SDL_SetRenderDrawColor(renderer, 100, 0, 0, 0));
            scc(SDL_RenderClear(renderer));

            render_text(renderer, font, inputText, 100, 100, textColor);

            SDL_RenderPresent(renderer);
        }

        SDL_StopTextInput();
        TTF_CloseFont(font);
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