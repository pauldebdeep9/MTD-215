// ============================================================================
// demo5-8.cpp — Renderer primitives demo (filled rect, outline, line, points)
//               Uses SDL2 + (optionally) SDL2_image just like the slides.
//
// Build on macOS (Homebrew paths):
//   clang++ demo5-8.cpp \
//     -I/usr/local/opt/sdl2/include/SDL2 \
//     -I/usr/local/opt/sdl2_image/include/SDL2 \
//     -L/usr/local/opt/sdl2/lib -L/usr/local/opt/sdl2_image/lib \
//     -lSDL2 -lSDL2_image -o demo5-8
//
// (If you don’t have SDL2_image you can drop its include/lib and -lSDL2_image;
//  this program doesn’t actually load images.)
//
// Run:
//   ./demo5-8
//   (Close the window or press Esc to quit.)
//
// What this program shows:
//  • Initializing SDL video and creating a window + accelerated renderer
//  • (Optionally) initializing SDL_image (PNG) like the teaching material
//  • Drawing with renderer primitives: filled rect, outlined rect, line, points
//  • Presenting a frame every loop
// ============================================================================

#include <SDL.h>
#include <SDL_image.h>   // included to match the slides; not strictly needed here
#include <stdio.h>

// ---------------------------
// Screen dimensions
// ---------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// ---------------------------
// Forward declarations (slide style)
// ---------------------------
bool init();       // start SDL, create window + renderer, (optionally) init SDL_image
bool loadMedia();  // nothing to load in this demo (returns true)
void closeAll();   // destroy renderer/window and quit libs

// ---------------------------
// Globals (simple demo style)
// ---------------------------
SDL_Window*   gWindow   = NULL;  // the window we render to
SDL_Renderer* gRenderer = NULL;  // the accelerated renderer

// ============================================================================
// init() — initialize SDL video, create window + renderer, init SDL_image
// ============================================================================
bool init() {
    // Initialize SDL video
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Optional: ask for linear scale quality when textures are scaled (teaching slide)
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        // Not a fatal error; just informative like the slide does
        printf("Warning: Linear texture filtering not enabled!\n");
    }

    // Create window
    gWindow = SDL_CreateWindow("SDL Tutorial — demo5-8 (Renderer primitives)",
                               SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Create an accelerated renderer for the window
    gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
    if (gRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Set a default draw color (white); we’ll change this before each primitive
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize SDL_image for PNG support (to mirror the slides, though unused)
    int imgFlags = IMG_INIT_PNG;
    if ((IMG_Init(imgFlags) & imgFlags) == 0) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

// ============================================================================
// loadMedia() — nothing to load for this primitives demo
// ============================================================================
bool loadMedia() {
    // In the slide this function returns true (no assets).
    return true;
}

// ============================================================================
// closeAll() — destroy renderer/window and quit libraries
// ============================================================================
void closeAll() {
    // Destroy renderer and window (order doesn’t matter here)
    if (gRenderer) { SDL_DestroyRenderer(gRenderer); gRenderer = NULL; }
    if (gWindow)   { SDL_DestroyWindow(gWindow);     gWindow   = NULL; }

    // Quit SDL_image first, then SDL
    IMG_Quit();
    SDL_Quit();
}

// ============================================================================
// main() — event loop + basic renderer drawing
// ============================================================================
int main(int, char**) {
    if (!init()) {
        printf("Failed to initialize!\n");
        return 1;
    }
    if (!loadMedia()) {
        printf("Failed to load media!\n");
        closeAll();
        return 1;
    }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)                              quit = true;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) quit = true;
        }

        // -------------------------
        // Clear the screen (white)
        // -------------------------
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        // -------------------------------------
        // Render a RED filled rectangle (center)
        // -------------------------------------
        SDL_Rect fillRect = {
            SCREEN_WIDTH  / 4,   // x
            SCREEN_HEIGHT / 4,   // y
            SCREEN_WIDTH  / 2,   // w
            SCREEN_HEIGHT / 2    // h
        };
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
        SDL_RenderFillRect(gRenderer, &fillRect);

        // -------------------------------------
        // Render a GREEN outlined rectangle
        // -------------------------------------
        SDL_Rect outlineRect = {
            SCREEN_WIDTH  / 6,
            SCREEN_HEIGHT / 6,
            (SCREEN_WIDTH  * 2) / 3,
            (SCREEN_HEIGHT * 2) / 3
        };
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
        SDL_RenderDrawRect(gRenderer, &outlineRect);

        // -------------------------------------
        // Render a BLUE horizontal line
        // -------------------------------------
        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0xFF, 0xFF);
        SDL_RenderDrawLine(gRenderer,
                           0,               SCREEN_HEIGHT / 2,   // start
                           SCREEN_WIDTH,    SCREEN_HEIGHT / 2);  // end

        // -------------------------------------
        // Render YELLOW dots as a vertical line
        // -------------------------------------
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0x00, 0xFF);
        for (int y = 0; y < SCREEN_HEIGHT; y += 4) {
            SDL_RenderDrawPoint(gRenderer, SCREEN_WIDTH / 2, y);
        }

        // Present the back buffer (swap buffers)
        SDL_RenderPresent(gRenderer);

        // Small delay so the loop doesn’t spin at 100% CPU
        SDL_Delay(16); // ~60 FPS
    }

    closeAll();
    return 0;
}
