// ============================================================================
// demo5-7.cpp  —  Renderer/Texture version (preferred for animation/scaling)
//
// What it does:
//   * Initializes SDL2 + SDL2_image (PNG support)
//   * Creates a window + an accelerated renderer
//   * Loads "texture.png" into an SDL_Texture
//   * Each frame: clear -> render the texture -> present
//   * Stays open until Esc or window close
//
// Build on macOS (Homebrew in /usr/local/opt; Intel Macs):
//   clang++ demo5-7.cpp \
//     -I/usr/local/opt/sdl2/include/SDL2 \
//     -I/usr/local/opt/sdl2_image/include/SDL2 \
//     -L/usr/local/opt/sdl2/lib -L/usr/local/opt/sdl2_image/lib \
//     -Wl,-rpath,/usr/local/opt/sdl2/lib \
//     -Wl,-rpath,/usr/local/opt/sdl2_image/lib \
//     -lSDL2 -lSDL2_image -o demo5-7
//
// (Apple Silicon would typically use /opt/homebrew instead of /usr/local.)
//
// Run (make sure texture.png is next to the executable or adjust the path):
//   ./demo5-7
// ============================================================================

#include <SDL.h>         // Core SDL
#include <SDL_image.h>   // SDL_image (for PNG/JPG/etc.)
#include <stdio.h>       // printf
#include <string>        // std::string

// ---------------------------
// 1) Compile-time constants
// ---------------------------
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// ---------------------------
// 2) Forward declarations
// ---------------------------
// Start SDL + window + renderer + SDL_image
bool init();
// Load all media used by this demo (one PNG as a texture)
bool loadMedia();
// Free all resources and quit subsystems
void closeAll();
// Helper: load an image file into an SDL_Texture*
SDL_Texture* loadTexture(std::string path);

// ---------------------------
// 3) Globals (tiny demo style)
// ---------------------------
SDL_Window*   gWindow   = NULL;  // The window we'll render to
SDL_Renderer* gRenderer = NULL;  // The hardware-accelerated renderer
SDL_Texture*  gTexture  = NULL;  // The texture we display each frame

// ============================================================================
// init() — initialize SDL core, create window + renderer, init SDL_image
// ============================================================================
bool init() {
    // Initialize SDL video subsystem
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Optional: request linear texture filtering for scaled textures.
    // If it fails, we just warn — it's not fatal.
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        printf("Warning: Linear texture filtering not enabled!\n");
    }

    // Create the window
    gWindow = SDL_CreateWindow(
        "SDL Tutorial — demo5-7 (Renderer + Texture)",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (!gWindow) {
        printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Create a hardware-accelerated renderer (VSYNC optional — uncomment the flag)
    gRenderer = SDL_CreateRenderer(
        gWindow,
        -1,
        SDL_RENDERER_ACCELERATED /*| SDL_RENDERER_PRESENTVSYNC*/
    );
    if (!gRenderer) {
        printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Set an initial draw color (this is the "clear" color each frame)
    // RGBA = white here; change to taste.
    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

    // Initialize SDL_image and specifically request PNG support
    int imgFlags = IMG_INIT_PNG;
    if ((IMG_Init(imgFlags) & imgFlags) == 0) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    return true;
}

// ============================================================================
// loadTexture(path) — load file into an SDL_Surface, then create SDL_Texture
// ============================================================================
SDL_Texture* loadTexture(std::string path) {
    // Load the image into a temporary surface (supports many formats via SDL_image)
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (!loadedSurface) {
        printf("Unable to load image %s! SDL_image Error: %s\n",
               path.c_str(), IMG_GetError());
        return NULL;
    }

    // Create a texture from that surface (moves pixels to GPU memory)
    SDL_Texture* newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
    if (!newTexture) {
        printf("Unable to create texture from %s! SDL Error: %s\n",
               path.c_str(), SDL_GetError());
    }

    // We no longer need the CPU-side surface
    SDL_FreeSurface(loadedSurface);
    return newTexture;
}

// ============================================================================
// loadMedia() — load our PNG texture into gTexture
// ============================================================================
bool loadMedia() {
    // Put a PNG named "texture.png" next to the executable (or adjust the path)
    gTexture = loadTexture("texture.png");
    if (!gTexture) {
        printf("Failed to load texture image!\n");
        return false;
    }
    return true;
}

// ============================================================================
// closeAll() — destroy texture/renderer/window, quit SDL_image/SDL
// ============================================================================
void closeAll() {
    // Destroy the texture if it exists
    if (gTexture) { SDL_DestroyTexture(gTexture); gTexture = NULL; }

    // Destroy renderer and window (order doesn’t matter here, this is safe)
    if (gRenderer) { SDL_DestroyRenderer(gRenderer); gRenderer = NULL; }
    if (gWindow)   { SDL_DestroyWindow(gWindow);     gWindow   = NULL; }

    // Shut down libraries (image first, then SDL core)
    IMG_Quit();
    SDL_Quit();
}

// ============================================================================
// main() — classic render loop: clear → draw → present → repeat
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
        // --------- handle input/events ----------
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT)                                quit = true;
            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE) quit = true;
        }

        // --------- render a frame ----------
        // (1) Clear the backbuffer to the current draw color (white)
        SDL_RenderClear(gRenderer);

        // (2) Copy the entire texture to the entire window (no scaling/rotation)
        //     - 2nd arg (src) = NULL ⇒ use full texture
        //     - 4th arg (dst) = NULL ⇒ fill the whole render target (window)
        SDL_RenderCopy(gRenderer, gTexture, NULL, NULL);

        // (3) Present the backbuffer to the screen (swap buffers)
        SDL_RenderPresent(gRenderer);

        // Be kind to the CPU (if not using present vsync)
        SDL_Delay(16); // ~60 FPS
    }

    closeAll();
    return 0;
}
