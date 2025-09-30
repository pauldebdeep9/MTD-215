// ================================================================
// demo5-3.cpp
// ------------------------------------------------
// SDL2 sample: load a BMP image and show it in a window.
// Window stays open until user presses Esc or closes the window.
//
// ---------------------------
// Build & Run (macOS / Homebrew SDL2)
// ---------------------------
// clang++ demo5-3.cpp \
//   -I/usr/local/opt/sdl2/include/SDL2 \
//   -L/usr/local/opt/sdl2/lib \
//   -lSDL2 -o demo5-3
//
// ./demo5-3
//
// Make sure a valid Windows BMP file named x.bmp
// is in the same directory as this program.
// ================================================================

#include <SDL.h>
#include <stdio.h>

// -----------------------------------------------------
// 1) Compile-time constants
// -----------------------------------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// -----------------------------------------------------
// 2) Function prototypes
// -----------------------------------------------------
bool init();          // initialize SDL and create window
bool loadMedia();     // load BMP image
void closeAll();      // free resources and quit SDL

// -----------------------------------------------------
// 3) Globals (for teaching simplicity)
// -----------------------------------------------------
SDL_Window*  gWindow        = NULL;   // main application window
SDL_Surface* gScreenSurface = NULL;   // surface belonging to the window
SDL_Surface* gXOut          = NULL;   // the loaded image we’ll show

// -----------------------------------------------------
// 4) init(): initialize SDL, create window, fetch surface
// -----------------------------------------------------
bool init() {
    bool success = true;

    // Initialize SDL’s video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create application window
        gWindow = SDL_CreateWindow(
            "SDL Tutorial — demo5-3",
            SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            SCREEN_WIDTH, SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );
        if (gWindow == NULL) {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Get the surface that the window displays
            gScreenSurface = SDL_GetWindowSurface(gWindow);
            if (gScreenSurface == NULL) {
                printf("Could not get window surface! SDL_Error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }
    return success;
}

// -----------------------------------------------------
// 5) loadMedia(): load our BMP image
// -----------------------------------------------------
bool loadMedia() {
    bool success = true;

    // Load splash image
    gXOut = SDL_LoadBMP("x.bmp");
    if (gXOut == NULL) {
        printf("Unable to load image x.bmp! SDL_Error: %s\n", SDL_GetError());
        success = false;
    }
    return success;
}

// -----------------------------------------------------
// 6) closeAll(): free resources and quit SDL
// -----------------------------------------------------
void closeAll() {
    // Free the loaded image
    SDL_FreeSurface(gXOut);
    gXOut = NULL;

    // Destroy the window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit all SDL subsystems
    SDL_Quit();
}

// -----------------------------------------------------
// 7) main(): program entry point
// -----------------------------------------------------
int main(int argc, char* args[]) {
    // Initialize SDL
    if (!init()) {
        printf("Failed to initialize!\n");
        return 1;
    }

    // Load image
    if (!loadMedia()) {
        printf("Failed to load media!\n");
    } else {
        // Main loop control
        bool quit = false;
        SDL_Event e;

        // Keep running until Esc key or window close
        while (!quit) {
            // Handle events
            while (SDL_PollEvent(&e) != 0) {
                // Window close button
                if (e.type == SDL_QUIT) {
                    quit = true;
                }
                // Escape key
                else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) {
                    quit = true;
                }
            }

            // Draw the BMP onto the window’s surface
            SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);

            // Update the window to reflect new drawing
            SDL_UpdateWindowSurface(gWindow);

            // Small delay to limit CPU usage (~60 FPS)
            SDL_Delay(16);
        }
    }

    // Clean up and exit
    closeAll();
    return 0;
}
