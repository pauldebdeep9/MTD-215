// Q4(a) — SDL2 bouncing square with Pause/Resume button
// Build (macOS/Homebrew):
//   clang++ q4a_bounce.cpp \
//     -I/usr/local/opt/sdl2/include/SDL2 \
//     -L/usr/local/opt/sdl2/lib -lSDL2 -o q4a_bounce

#include <SDL.h>
#include <cstdio>

// ------------------ Constants ------------------
const int  WIN_W = 800;
const int  WIN_H = 600;
const int  SQ    = 50;           // square size
const float SPEED = 300.0f;      // pixels per second (horizontal)

const SDL_Rect BTN = {20, WIN_H - 60, 160, 40}; // Pause/Resume button area

// ------------------ Helpers --------------------
static bool pointInRect(int x, int y, const SDL_Rect& r) {
    return x >= r.x && x < r.x + r.w && y >= r.y && y < r.y + r.h;
}

int main(int, char**) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::printf("SDL init error: %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "SDL Animation — Running",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        WIN_W, WIN_H, SDL_WINDOW_SHOWN);
    if (!window) {
        std::printf("CreateWindow error: %s\n", SDL_GetError());
        SDL_Quit(); return 1;
    }

    SDL_Renderer* ren = SDL_CreateRenderer(window, -1,
                                           SDL_RENDERER_ACCELERATED |
                                           SDL_RENDERER_PRESENTVSYNC);
    if (!ren) {
        std::printf("CreateRenderer error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit(); return 1;
    }

    // --- simulation state ---
    float x = (WIN_W - SQ) / 2.0f;  // start centered
    float y = (WIN_H - SQ) / 2.0f;
    float vx = SPEED;               // moving right initially
    bool paused = false;

    Uint32 prevTicks = SDL_GetTicks();
    bool quit = false;

    while (!quit) {
        // ----- Events -----
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_QUIT) quit = true;

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_ESCAPE)
                quit = true;

            if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) {
                paused = !paused;
                SDL_SetWindowTitle(window, paused ?
                    "SDL Animation — Paused" : "SDL Animation — Running");
            }

            if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT) {
                if (pointInRect(e.button.x, e.button.y, BTN)) {
                    paused = !paused;
                    SDL_SetWindowTitle(window, paused ?
                        "SDL Animation — Paused" : "SDL Animation — Running");
                }
            }
        }

        // ----- Update (dt in seconds) -----
        Uint32 now = SDL_GetTicks();
        float dt = (now - prevTicks) / 1000.0f;
        prevTicks = now;

        if (!paused) {
            x += vx * dt;

            // Bounce on left/right edges
            if (x <= 0.0f) { x = 0.0f; vx = +SPEED; }
            if (x + SQ >= WIN_W) { x = (float)(WIN_W - SQ); vx = -SPEED; }
        }

        // ----- Render -----
        // Clear to white
        SDL_SetRenderDrawColor(ren, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(ren);

        // Draw the moving square (red)
        SDL_Rect box = { (int)x, (int)y, SQ, SQ };
        SDL_SetRenderDrawColor(ren, 0xE6, 0x2A, 0x2A, 0xFF);
        SDL_RenderFillRect(ren, &box);

        // Draw the toggle button:
        //   Green = "Resume", Red = "Pause"
        if (paused) SDL_SetRenderDrawColor(ren, 0x2E, 0xCC, 0x71, 0xFF); // green: resume
        else        SDL_SetRenderDrawColor(ren, 0xE7, 0x4C, 0x3C, 0xFF); // red: pause
        SDL_RenderFillRect(ren, &BTN);
        // Outline
        SDL_SetRenderDrawColor(ren, 0x33, 0x33, 0x33, 0xFF);
        SDL_RenderDrawRect(ren, &BTN);

        // (Optional) button hint line
        // SDL_RenderDrawLine(ren, BTN.x, BTN.y, BTN.x + BTN.w, BTN.y + BTN.h);

        SDL_RenderPresent(ren);
    }

    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
