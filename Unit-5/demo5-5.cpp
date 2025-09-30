// demo5-5.cpp
// Demonstrates loading a BMP, converting it to the screen format,
// and stretching it to fill the window.
// Compile & Run (macOS with Homebrew SDL2):
//   clang++ demo5-5.cpp \
//     -I/usr/local/opt/sdl2/include/SDL2 \
//     -L/usr/local/opt/sdl2/lib \
//     -lSDL2 -o demo5-5
//   ./demo5-5

#include <SDL.h>
#include <stdio.h>
#include <string>

// Screen size
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// Globals
SDL_Window*  gWindow          = NULL;   // main window
SDL_Surface* gScreenSurface   = NULL;   // window surface
SDL_Surface* gStretchedSurface= NULL;   // loaded + converted image

// Forward declarations
bool init();                               // set up SDL and window
bool loadMedia();                          // load & prepare BMP
void closeAll();                           // clean up
SDL_Surface* loadSurface(std::string path);// load + optimize image

// ------------------------------
bool init() {
    // Start SDL Video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Create centered window
    gWindow = SDL_CreateWindow("SDL Tutorial — demo5-5",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT,
                               SDL_WINDOW_SHOWN);
    if (!gWindow) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Get the surface attached to the window
    gScreenSurface = SDL_GetWindowSurface(gWindow);
    if (!gScreenSurface) {
        printf("GetWindowSurface failed! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

// ------------------------------
bool loadMedia() {
    // Load and optimize BMP
    gStretchedSurface = loadSurface("stretch.bmp");
    if (!gStretchedSurface) {
        printf("Failed to load stretching image!\n");
        return false;
    }
    return true;
}

// ------------------------------
SDL_Surface* loadSurface(std::string path) {
    // Load BMP from disk
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (!loadedSurface) {
        printf("Unable to load image %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
        return NULL;
    }

    // Convert loaded surface to screen format
    SDL_Surface* optimizedSurface = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (!optimizedSurface) {
        printf("Unable to optimize image %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
    }

    // We can free the original now
    SDL_FreeSurface(loadedSurface);
    return optimizedSurface;
}

// ------------------------------
void closeAll() {
    // Free the stretched image
    SDL_FreeSurface(gStretchedSurface);
    gStretchedSurface = NULL;

    // Destroy window
    SDL_DestroyWindow(gWindow);
    gWindow = NULL;

    // Quit SDL
    SDL_Quit();
}

// ------------------------------
int main(int argc, char* args[]) {
    if (!init()) {
        printf("Failed to initialize!\n");
        return 1;
    }

    if (!loadMedia()) {
        printf("Failed to load media!\n");
        closeAll();
        return 1;
    }

    // Main loop
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) quit = true;
        }

        // Define rectangle covering entire window
        SDL_Rect stretchRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};

        // Blit the BMP stretched to the full window
        SDL_BlitScaled(gStretchedSurface, NULL, gScreenSurface, &stretchRect);

        // Update the window
        SDL_UpdateWindowSurface(gWindow);

        SDL_Delay(16); // ~60fps refresh
    }

    closeAll();
    return 0;
}
