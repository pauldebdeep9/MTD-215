// ============================================================================
// demo5-2.cpp  —  SDL2 “Hello World” splash example
//
// Purpose:
//   * Demonstrates the classic SDL2 initialization / load image / display / wait / exit cycle.
//   * Displays a BMP image in a window and keeps the window up until
//     the user presses Esc, closes the window, or an optional timeout is reached.
//
// Build on Intel Mac with Homebrew SDL2:
//   clang++ demo5-2.cpp \
//       -I/usr/local/opt/sdl2/include/SDL2 \
//       -L/usr/local/opt/sdl2/lib \
//       -lSDL2 -o demo5-2
//
// Run (place hello_world.bmp in the same directory):
//   ./demo5-2
// ============================================================================

#include <SDL.h>      // Core SDL2 API
#include <stdio.h>    // For printf logging

// ------------------------------
// 1) Window size
// ------------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// ------------------------------
// 2) Function prototypes
// ------------------------------
bool init();          // Starts SDL, creates window, grabs screen surface
bool loadMedia();     // Loads the BMP image
void closeAll();      // Frees resources and shuts SDL down

// ------------------------------
// 3) Global SDL handles
// ------------------------------
// These are the core resources we’ll manage.
// For a small demo, global variables are fine. Larger apps should wrap them in a class.
SDL_Window*  gWindow        = NULL;  // The main OS window
SDL_Surface* gScreenSurface = NULL;  // The framebuffer (software) attached to the window
SDL_Surface* gHelloWorld    = NULL;  // The loaded BMP image we’ll display

// ============================================================================
// 4) init() — initialize SDL and create a window
// ============================================================================
bool init() {
    // Initialize only the video subsystem (enough for this demo)
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // SDL_GetError() gives a human-readable reason
        printf("SDL init error: %s\n", SDL_GetError());
        return false;
    }

    // Create a visible 640×480 window centered on screen
    gWindow = SDL_CreateWindow(
        "SDL Tutorial — demo5-2",          // Title bar text
        SDL_WINDOWPOS_CENTERED,            // Horizontal screen position
        SDL_WINDOWPOS_CENTERED,            // Vertical screen position
        SCREEN_WIDTH,                      // Window width in pixels
        SCREEN_HEIGHT,                     // Window height in pixels
        SDL_WINDOW_SHOWN                   // Show immediately (no hidden/minimized)
    );
    if (!gWindow) {
        printf("CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit();                         // Clean up SDL if window failed
        return false;
    }

    // Obtain a pointer to the window’s pixel buffer (software surface)
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    if (!gScreenSurface) {
        printf("GetWindowSurface error: %s\n", SDL_GetError());
        SDL_DestroyWindow(gWindow);
        SDL_Quit();
        return false;
    }

    return true; // Success
}

// ============================================================================
// 5) loadMedia() — load the BMP image to display
// ============================================================================
bool loadMedia() {
    // Load a Windows-style BMP image from file
    gHelloWorld = SDL_LoadBMP("hello_world.bmp");

    if (!gHelloWorld) {
        // This error usually means: file missing, wrong path, or not a BMP format SDL understands
        printf("Unable to load image hello_world.bmp! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    return true; // Success
}

// ============================================================================
// 6) closeAll() — clean up resources before exiting
// ============================================================================
void closeAll() {
    // Free the loaded image surface
    SDL_FreeSurface(gHelloWorld);
    gHelloWorld = NULL;

    // Destroy the window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Shut down all SDL subsystems that were initialized
    SDL_Quit();
}

// ============================================================================
// 7) main() — program entry point
// ============================================================================
int main(int, char**) {
    // ---- Step 1: initialize SDL and create the window ----
    if (!init()) {
        printf("Failed to initialize!\n");
        return 1;
    }

    // ---- Step 2: load the image to be displayed ----
    if (!loadMedia()) {
        printf("Failed to load media!\n");
        closeAll();       // Clean up before exiting
        return 1;
    }

    // ---- Step 3: draw the image once ----
    // SDL_BlitSurface copies pixels from the source surface to the destination
    // Passing NULL for both source and destination rectangles means
    // “copy entire image to the top-left corner of the screen surface”
    SDL_BlitSurface(gHelloWorld, NULL, gScreenSurface, NULL);

    // Present the updated surface in the OS window
    SDL_UpdateWindowSurface(gWindow);

    // ---- Step 4: keep window alive until Esc, close, or timeout ----
    const Uint32 SHOW_MS = 30000;      // Show up to 30 seconds; set 0 for no timeout
    Uint32 start = SDL_GetTicks();     // Time when we started showing
    bool quit = false;

    while (!quit) {
        // Process all pending events
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)                 // User clicked the close button
                quit = true;
            if (e.type == SDL_KEYDOWN &&            // Key pressed
                e.key.keysym.sym == SDLK_ESCAPE)    // Specifically Esc
                quit = true;
        }

        // If a timeout is set, leave after the duration elapses
        if (SHOW_MS && SDL_TICKS_PASSED(SDL_GetTicks(), start + SHOW_MS))
            quit = true;

        // Tiny delay so we don’t spin at 100% CPU
        SDL_Delay(10);
    }

    // ---- Step 5: clean up before exiting ----
    closeAll();
    return 0;
}
