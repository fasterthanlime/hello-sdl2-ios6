#include <hello/hello.h>
#include <stdbool.h>

static const int screen_width = 320;
static const int screen_height = 480;

static SDL_Window *win;
static SDL_GLContext ctx;

void sdl_error_die()
{
    printf("Error: %s\n", SDL_GetError());
    exit(1);
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        sdl_error_die();

    win = SDL_CreateWindow(NULL, 0, 0, screen_width, screen_height,
                           SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_BORDERLESS);
    if (!win)
        sdl_error_die();

    ctx = SDL_GL_CreateContext(win);
    SDL_GL_SetSwapInterval(1);

    bool running = true;
    SDL_Event event;

    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        glClearColor(1.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        SDL_GL_SwapWindow(win);
    }

    SDL_GL_DeleteContext(ctx);
    SDL_DestroyWindow(win);
    SDL_Quit();
	
    return 0;
}


