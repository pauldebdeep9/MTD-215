// ============================================================================
// SDL2 Key-press Surfaces Demo (Surfaces + Window Surface, not Renderer/Texture)
// ----------------------------------------------------------------------------
// What this program does:
//   * Initializes SDL's video subsystem
//   * Creates a 640x480 window
//   * Loads five .BMP images from disk into SDL_Surface objects
//       - "press.bmp"  (default)
//       - "up.bmp"
//       - "down.bmp"
//       - "left.bmp"
//       - "right.bmp"
//   * Enters an event loop:
//       - When you press arrow keys, it swaps which image (surface) is shown
//       - When you close the window (or press Cmd/WIN close), the app quits
//   * Cleans up all loaded resources and quits SDL
//
// Why SDL_Surface (software blit) instead of SDL_Texture (GPU)?
//   - This mirrors "lazy foo" style tutorials and your screenshots precisely.
//   - It uses the window's screen surface and calls SDL_BlitSurface + SDL_UpdateWindowSurface.
//   - For teaching fundamentals, this "2D blitting" path is simple and sufficient.
//   - If you later want hardware acceleration, migrate to SDL_Renderer + SDL_Texture.
//
// Files needed next to the executable (or set absolute paths below):
//   - press.bmp, up.bmp, down.bmp, left.bmp, right.bmp
//
// Build notes are after the code.
// ============================================================================

#include <SDL.h>     // Core SDL2 header (must be available in your include path)
#include <stdio.h>   // printf
#include <string>    // std::string

// ----------------------------
// 1) Compile-time constants
// ----------------------------

// Window dimensions (change as you like)
const int SCREEN_WIDTH  = 640;
const int SCREEN_HEIGHT = 480;

// We create an enum to index our "key-press surfaces" array.
// The final value KEY_PRESS_SURFACE_TOTAL is a count of how many entries.
enum KeyPressSurfaces {
    KEY_PRESS_SURFACE_DEFAULT = 0,
    KEY_PRESS_SURFACE_UP,
    KEY_PRESS_SURFACE_DOWN,
    KEY_PRESS_SURFACE_LEFT,
    KEY_PRESS_SURFACE_RIGHT,
    KEY_PRESS_SURFACE_TOTAL  // <-- not a real surface, just the length marker
};

// ----------------------------
// 2) Globals (simple teaching)
// ----------------------------
// For a tiny teaching demo, globals are fine (clear, compact).
// In production, prefer a small struct/class to own these and RAII-manage lifetime.

// The created OS window we render to
SDL_Window*   gWindow         = nullptr;

// The window's screen surface (OS-managed backbuffer when using "surfaces" path)
SDL_Surface*  gScreenSurface  = nullptr;

// One surface per key-state (we load 5 BMPs)
SDL_Surface*  gKeyPressSurfaces[KEY_PRESS_SURFACE_TOTAL] = {nullptr};

// Pointer to the "current" surface (what we blit each frame)
SDL_Surface*  gCurrentSurface = nullptr;

// ----------------------------
// 3) Forward declarations
// ----------------------------
bool init();                              // Initialize SDL, create window, grab screen surface
bool loadMedia();                         // Load all surfaces (BMP files)
void close();                             // Free every resource and quit SDL (always call!)
SDL_Surface* loadSurface(const std::string& path); // Helper: loads a single BMP as SDL_Surface

// ----------------------------
// 4) init()
// ----------------------------
bool init() {
    bool success = true;

    // Initialize only the video subsystem (keeps things focused)
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        // SDL_GetError() returns a human-readable message for the last SDL error
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    } else {
        // Create a window. Flags = SDL_WINDOW_SHOWN to display immediately.
        gWindow = SDL_CreateWindow(
            "SDL2 Tutorial: Key Surfaces (Surfaces path)",
            SDL_WINDOWPOS_UNDEFINED,   // Let OS decide initial X
            SDL_WINDOWPOS_UNDEFINED,   // Let OS decide initial Y
            SCREEN_WIDTH,
            SCREEN_HEIGHT,
            SDL_WINDOW_SHOWN
        );

        if (gWindow == nullptr) {
            printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            // Get the window's screen surface. This is the backbuffer we're going to blit onto.
            gScreenSurface = SDL_GetWindowSurface(gWindow);
            if (gScreenSurface == nullptr) {
                printf("SDL_GetWindowSurface failed! SDL Error: %s\n", SDL_GetError());
                success = false;
            }
        }
    }

    return success;
}

// ----------------------------
// 5) loadSurface(path)
// ----------------------------
// Loads a .BMP image from disk into an SDL_Surface*.
// If you need PNG/JPG, you must use SDL_image (IMG_Load) instead of SDL_LoadBMP.
// For this demo we stick to BMP to avoid extra deps.
SDL_Surface* loadSurface(const std::string& path) {
    SDL_Surface* loadedSurface = SDL_LoadBMP(path.c_str());
    if (loadedSurface == nullptr) {
        // Common failure: wrong working directory → file not found.
        // Try printing absolute path when debugging.
        printf("Unable to load image '%s'! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return nullptr;
    }

    // Optional: Convert the loaded surface to the same pixel format as the window surface
    //           for faster blits (avoids per-blit conversion).
    //           If conversion fails, we fall back to the original.
    SDL_Surface* optimized = SDL_ConvertSurface(loadedSurface, gScreenSurface->format, 0);
    if (optimized == nullptr) {
        // If conversion fails, still return the loadedSurface so the program continues.
        printf("Warning: Unable to optimize image '%s'! SDL Error: %s\n", path.c_str(), SDL_GetError());
        return loadedSurface; // (caller must SDL_FreeSurface it)
    } else {
        SDL_FreeSurface(loadedSurface); // free the unoptimized copy
        return optimized;
    }
}

// ----------------------------
// 6) loadMedia()
// ----------------------------
// Loads all five key-press surfaces into our global array.
// If any load fails, we set success=false but still try to load others so you get
// a full error report in one run.
bool loadMedia() {
    bool success = true;

    // NOTE: If your images live in another folder, include the relative/absolute path here.
    // e.g., "assets/press.bmp"
    gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] = loadSurface("press.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT] == nullptr) {
        printf("Failed to load default image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] = loadSurface("up.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_UP] == nullptr) {
        printf("Failed to load up image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] = loadSurface("down.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN] == nullptr) {
        printf("Failed to load down image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] = loadSurface("left.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT] == nullptr) {
        printf("Failed to load left image!\n");
        success = false;
    }

    gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] = loadSurface("right.bmp");
    if (gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT] == nullptr) {
        printf("Failed to load right image!\n");
        success = false;
    }

    return success;
}

// ----------------------------
// 7) close()
// ----------------------------
// Releases every resource we created. ALWAYS call before your app exits.
void close() {
    // Free every loaded key-press surface
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i) {
        if (gKeyPressSurfaces[i]) {
            SDL_FreeSurface(gKeyPressSurfaces[i]);
            gKeyPressSurfaces[i] = nullptr;
        }
    }

    // Destroy window
    if (gWindow) {
        SDL_DestroyWindow(gWindow);
        gWindow = nullptr;
    }

    // Quit all initialized SDL subsystems
    SDL_Quit();
}

// ----------------------------
// 8) main()
// ----------------------------
int main(int /*argc*/, char* /*argv*/[]) {
    // 1) Initialize SDL and create the window + screen surface
    if (!init()) {
        printf("Failed to initialize!\n");
        return 1;
    }

    // 2) Load images from disk
    if (!loadMedia()) {
        printf("Failed to load media!\n");
        // We still proceed so you can see what loaded / what did not.
        // In production you might bail out here.
    }

    // 3) Set the initial surface to "default"
    gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];

    // 4) Main event loop
    bool quit = false;
    while (!quit) {
        SDL_Event e;

        // Poll all pending events (non-blocking). Use SDL_WaitEvent to block instead.
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                // User clicked the close button on the window
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                // A key was pressed; check which one
                switch (e.key.keysym.sym) {
                    case SDLK_UP:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_UP];
                        break;
                    case SDLK_DOWN:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DOWN];
                        break;
                    case SDLK_LEFT:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_LEFT];
                        break;
                    case SDLK_RIGHT:
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_RIGHT];
                        break;
                    default:
                        // Any other key → default image
                        gCurrentSurface = gKeyPressSurfaces[KEY_PRESS_SURFACE_DEFAULT];
                        break;
                }
            }
        }

        // 5) "Render" the current image:
        //    SDL_BlitSurface copies pixel data from source surface to destination surface.
        //    Passing NULL for src/dst rect means "use full source, full destination at (0,0)".
        if (gCurrentSurface != nullptr && gScreenSurface != nullptr) {
            SDL_BlitSurface(gCurrentSurface, nullptr, gScreenSurface, nullptr);
        }

        // 6) Ask SDL to update the OS window with our modified backbuffer
        SDL_UpdateWindowSurface(gWindow);

        // Optional: small delay to avoid pegging CPU at 100% in a simple loop
        SDL_Delay(1);
    }

    // 7) Cleanup
    close();
    return 0;
}
