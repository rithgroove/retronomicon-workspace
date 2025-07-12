#include <iostream>
#include "retronomicon/lib/math/point.h"
#include "retronomicon/lib/math/rect.h"
#include "retronomicon/lib/graphic/window.h"
using namespace retronomicon::lib::math;
using retronomicon::lib::graphic::Window;
int main() {
    Point pos(10.0f, 20.0f);
    Rect rect(pos, 100.0f, 50.0f);

    std::cout << "Rect Position: (" << rect.getX() << ", " << rect.getY() << ")\n";
    std::cout << "Rect Size: " << rect.getWidth() << "x" << rect.getHeight() << std::endl;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
        std::cerr << "SDL INIT failed: "<<SDL_GetError() << std::endl;

    try {
        Window window("Retronomicon Sandbox", 800, 600);
        bool running = true;
        while (running) {
            SDL_Event wEvent;   
            while(SDL_PollEvent(&wEvent)) {
                switch (wEvent.type) {
                    case SDL_QUIT:
                        running = false; 
                        break;
                    case SDL_KEYDOWN:
                        running = false; 
                        break;
                    case SDL_MOUSEBUTTONDOWN:   
                        running = false; 
                        break;
                    case SDL_WINDOWEVENT_CLOSE: 
                        running = false; 
                        break;
                    default:
                        //SDL_Log("Window %d got unknown event %d\n", wEvent.window.windowID, wEvent.window.event);
                        break;
                }
            }

            SDL_Delay(200); // Keep < 500 [ms]
        }
    } catch (const std::exception& ex) {
        std::cerr << "Exception: " << ex.what() << '\n';
        return 1;
    }

    return 0;
}