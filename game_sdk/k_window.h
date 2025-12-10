#ifndef K_WINDOW__H
#define K_WINDOW__H

#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

class KWindow {
private:
    SDL_Window          *        p_sdl_window   ;
    SDL_Renderer        *        p_sdl_renderer ;

    int                          width  ;
    int                          height ;

public:
    KWindow(const char* title, const int width, const int height) ;
    ~KWindow();

    SDL_Renderer*        get_renderer() { return p_sdl_renderer; }
    int                  get_width()    { return width; }
    int                  get_height()   { return height; }

} ;

#endif // K_WINDOW__H
