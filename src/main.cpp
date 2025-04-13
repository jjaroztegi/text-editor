#include "InputHandler.hpp"
#include "SDLException.hpp"
#include "TextEditor.hpp"

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <iostream>

int main(int argc, char *argv[]) {
    try {
        scc(SDL_Init(SDL_INIT_VIDEO));
        scc(TTF_Init());

        SDL_Window *window = static_cast<SDL_Window *>(scp(SDL_CreateWindow(
            "Text Editor", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_RESIZABLE)));
        SDL_Renderer *renderer =
            static_cast<SDL_Renderer *>(scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED)));

        TextEditor editor;
        if (argc > 1)
            editor.loadFromFile(argv[1]);
        InputHandler inputHandler(editor);
        SDL_StartTextInput();

        bool quit = false;
        while (!quit) {
            SDL_Event event{};
            while (SDL_PollEvent(&event)) {
                inputHandler.handleEvent(event);
                if (inputHandler.shouldQuit(event)) {
                    quit = true;
                }
            }

            int windowWidth, windowHeight;
            SDL_GetWindowSize(window, &windowWidth, &windowHeight);
            editor.setWrapLength(windowWidth);

            scc(SDL_SetRenderDrawColor(renderer, 24, 24, 24, 255));
            scc(SDL_RenderClear(renderer));
            editor.render(renderer, 20, 10);
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