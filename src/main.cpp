#include <SDL2/SDL.h>
#include <iostream>
#include <glad/glad.h>

const uint32_t WIDTH = 1024;
const uint32_t HEIGHT = 768;

using namespace std;

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        exit(1);
    }
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

    SDL_Window *mainWindow = SDL_CreateWindow("main", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext glMainWindowContext = SDL_GL_CreateContext(mainWindow);

    SDL_Window *secondaryWindow = SDL_CreateWindow("secondary", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_OPENGL);
    SDL_GLContext glSeconraryWindowContext = SDL_GL_CreateContext(secondaryWindow);

    if (!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)) {
        cout << "Failed to initialize the OpenGL context." << endl;
        exit(1);
    }
    cout << "OpenGL " << GLVersion.major << "." << GLVersion.minor << endl;

    bool quit = false;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.window.event == SDL_WINDOWEVENT_CLOSE) {
                quit = true;
            }
        }
        SDL_GL_MakeCurrent(mainWindow, glMainWindowContext);
        glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(mainWindow);

        SDL_GL_MakeCurrent(secondaryWindow, glSeconraryWindowContext);
        glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(secondaryWindow);
    }
    SDL_Quit();
    return 0;
}
