#include <SDL2/SDL.h>
#include <stdio.h>

#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480

static void loop(SDL_Window *win, SDL_Surface *sc_surf);
static void draw_frame(SDL_Surface *sc_surf);
static void set_pixel(SDL_Surface *surf, int x, int y, Uint32 c);

int main(void) {
    SDL_Window *win = NULL;
    SDL_Surface *sc_surf = NULL;
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: Could not initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }
    if ((win = SDL_CreateWindow("test", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL) {
        printf("Error: Could not create window: %s\n", SDL_GetError());
        exit(2);
    }
    sc_surf = SDL_GetWindowSurface(win);

    loop(win, sc_surf);

    SDL_DestroyWindow(win);
    SDL_Quit();
    return 0;
}

static void loop(SDL_Window *win, SDL_Surface *sc_surf) {
    char quit = 0;
    SDL_Event e;

    /* main loop */
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT)
                quit = 1;
        }
        draw_frame(sc_surf);
        SDL_UpdateWindowSurface(win);
    }
}

static void draw_frame(SDL_Surface *sc_surf) {
    int x, y;
    for (y = 0; y < 100; y++)
        for (x = 0; x < 100; x++)
            set_pixel(sc_surf, 10 + x * 2, 10 + y * 2, 0x00FF00FF);
}

static void set_pixel(SDL_Surface *surf, int x, int y, Uint32 c) {
    SDL_LockSurface(surf); /* lock to prevent concurrent modification */
    ((Uint32 *) (surf->pixels))[x + y * surf->w] = c;
    SDL_UnlockSurface(surf);
}
