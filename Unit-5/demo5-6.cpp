// ============================================================================
// demo5-6.cpp  —  Load a PNG with SDL_image, convert to screen format,
//                 blit to the window, and stay open until Esc/close.
// 
// Build on macOS (Homebrew SDL2 + SDL2_image in /usr/local/opt):
//   clang++ demo5-6.cpp \
//     -I/usr/local/opt/sdl2/include/SDL2 \
//     -I/usr/local/opt/sdl2_image/include/SDL2 \
//     -L/usr/local/opt/sdl2/lib -L/usr/local/opt/sdl2_image/lib \
//     -lSDL2 -lSDL2_image -o demo5-6
//
// Run (make sure loaded.png is next to the executable):
//   ./demo5-6
// ============================================================================

#include <SDL.h>         // SDL core
#include <SDL_image.h>   // SDL_image (PNG/JPG/… loader)
#include <stdio.h>
#include <string>

// ---------------------------
// Screen dimensions
// ---------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// ---------------------------
// Forward declarations
// ---------------------------
bool init();                                // start SDL + window + SDL_image
bool loadMedia();                           // load PNG into a surface
void closeAll();                            // free resources, quit libs
SDL_Surface* loadSurface(std::string path); // helper: IMG_Load + convert

// ---------------------------
// Globals (simple demo style)
// ---------------------------
SDL_Window*  gWindow        = NULL; // main window
SDL_Surface* gScreenSurface = NULL; // window's framebuffer surface
SDL_Surface* gPNGSurface    = NULL; // converted PNG surface (ready to blit)

// ============================================================================
// init() — initialize SDL, create window, init SDL_image, get window surface
// ============================================================================
bool init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    gWindow = SDL_CreateWindow("SDL Tutorial — demo5-6 (PNG via SDL_image)",
                               SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                               SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!gWindow) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialize SDL_image for PNG support specifically
    int imgFlags = IMG_INIT_PNG;
    if ((IMG_Init(imgFlags) & imgFlags) == 0) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    gScreenSurface = SDL_GetWindowSurface(gWindow);
    if (!gScreenSurface) {
        printf("GetWindowSurface failed! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    return true;
}

// ============================================================================
// loadSurface(path) — load with IMG_Load, then convert to window format
// ============================================================================
SDL_Surface* loadSurface(std::string path) {
    // Load arbitrary image (here, PNG) into an SDL_Surface
    SDL_Surface* loaded = IMG_Load(path.c_str());
    if (!loaded) {
        printf("Unable to load image %s! SDL_image Error: %s\n",
               path.c_str(), IMG_GetError());
        return NULL;
    }

    // Convert to the window's pixel format for faster blits
    SDL_Surface* optimized = SDL_ConvertSurface(loaded, gScreenSurface->format, 0);
    if (!optimized) {
        printf("Unable to optimize image %s! SDL Error: %s\n",
               path.c_str(), SDL_GetError());
    }

    SDL_FreeSurface(loaded); // free the original temporary surface
    return optimized;
}

// ============================================================================
// loadMedia() — load our PNG (converted) into gPNGSurface
// ============================================================================
bool loadMedia() {
    gPNGSurface = loadSurface("loaded.png");
    if (!gPNGSurface) {
        printf("Failed to load PNG image!\n");
        return false;
    }
    return true;
}

// ============================================================================
// closeAll() — free everything and quit libraries in correct order
// ============================================================================
void closeAll() {
    SDL_FreeSurface(gPNGSurface); gPNGSurface = NULL;

    SDL_DestroyWindow(gWindow);   gWindow = NULL;

    IMG_Quit();   // shut down SDL_image first…
    SDL_Quit();   // …then SDL core
}

// ============================================================================
// main() — event loop keeps window alive (Esc/close to exit)
// ============================================================================
int main(int, char**) {
    if (!init())        { printf("Failed to initialize!\n"); return 1; }
    if (!loadMedia())   { printf("Failed to load media!\n"); closeAll(); return 1; }

    bool quit = false;
    SDL_Event e;

    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)                                   quit = true;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) quit = true;
        }

        // Blit the PNG surface to the full window (no scaling here)
        SDL_BlitSurface(gPNGSurface, NULL, gScreenSurface, NULL);
        SDL_UpdateWindowSurface(gWindow);

        SDL_Delay(16); // ~60 FPS
    }

    closeAll();
    return 0;
}
