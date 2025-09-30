// ============================================================================
// demo5-1.cpp  —  Minimal SDL2 surface example
//
// Build on Intel Mac with Homebrew SDL2:
//   clang++ demo5-1.cpp \
//      -I/usr/local/opt/sdl2/include/SDL2 \
//      -L/usr/local/opt/sdl2/lib \
//      -lSDL2 -o demo5-1
//
// Run:
//   ./demo5-1
// ============================================================================

#include <SDL.h>      // SDL core header
#include <stdio.h>    // for printf()

// -----------------------------
// Screen dimension constants
// -----------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

int main() {
    // ------------------------------------------------------------------------
    // 1) Initialize SDL video subsystem
    // ------------------------------------------------------------------------
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // If initialization fails, print diagnostic message and quit
        printf("SDL init error: %s\n", SDL_GetError());
        return 1;
    }

    // ------------------------------------------------------------------------
    // 2) Create a window
    // ------------------------------------------------------------------------
    SDL_Window* win = SDL_CreateWindow(
        "SDL surface test (press Esc to quit)",  // Window title
        SDL_WINDOWPOS_CENTERED,                  // Center window on screen (X)
        SDL_WINDOWPOS_CENTERED,                  // Center window on screen (Y)
        SCREEN_WIDTH,                             // Window width
        SCREEN_HEIGHT,                            // Window height
        SDL_WINDOW_SHOWN                          // Flag: show immediately
    );
    if (!win) {
        printf("CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Query window size (useful to confirm what OS created)
    int w, h;
    SDL_GetWindowSize(win, &w, &h);
    printf("Window size: %d x %d\n", w, h);

    // ------------------------------------------------------------------------
    // 3) Get the window's screen surface (back buffer)
    // ------------------------------------------------------------------------
    SDL_Surface* screen = SDL_GetWindowSurface(win);
    if (!screen) {
        printf("GetWindowSurface error: %s\n", SDL_GetError());
        SDL_DestroyWindow(win);
        SDL_Quit();
        return 1;
    }
    printf("Screen surface fmt=0x%x, pitch=%d, w=%d, h=%d\n",
           screen->format->format, screen->pitch, screen->w, screen->h);

    // ------------------------------------------------------------------------
    // 4) Main event/render loop
    //    - Keeps window open
    //    - Handles events
    //    - Draws each frame
    // ------------------------------------------------------------------------
    bool quit = false;
    while (!quit) {
        // ---- Handle events ----
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)                  // Window close button
                quit = true;
            if (e.type == SDL_KEYDOWN &&             // Key pressed
                e.key.keysym.sym == SDLK_ESCAPE)     // specifically Esc key
                quit = true;
        }

        // ---- Fill screen with white every frame ----
        Uint32 white = SDL_MapRGB(screen->format, 0xFF, 0xFF, 0xFF);
        if (SDL_FillRect(screen, nullptr, white) != 0) {
            printf("FillRect error: %s\n", SDL_GetError());
        }

        // ---- Update (present) the surface to the OS window ----
        if (SDL_UpdateWindowSurface(win) != 0) {
            printf("UpdateWindowSurface error: %s\n", SDL_GetError());
        }

        // ---- Sleep briefly to avoid maxing CPU (≈60 frames/sec) ----
        SDL_Delay(16);
    }

    // ------------------------------------------------------------------------
    // 5) Cleanup before exit
    // ------------------------------------------------------------------------
    SDL_DestroyWindow(win);  // Free window and associated surface
    SDL_Quit();              // Shut down SDL subsystems
    return 0;
}
