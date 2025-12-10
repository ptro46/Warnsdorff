#include <k_window.h>

KWindow::KWindow(const char * title, const int width, const int height) {

    this->width = width ;
    this->height = height ;
    
    p_sdl_window = SDL_CreateWindow(title, width, height, SDL_WINDOW_RESIZABLE);
    if ( ! p_sdl_window ) {
        fprintf(stderr, "Échec de SDL_CreateWindow : %s\n", SDL_GetError());
        SDL_Quit();
    }

    p_sdl_renderer = SDL_CreateRenderer(p_sdl_window, NULL);
    if ( ! p_sdl_renderer ) {
        fprintf(stderr, "Échec de SDL_CreateRenderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(p_sdl_window);
        p_sdl_window = NULL ;
        SDL_Quit();
    }
}

KWindow::~KWindow() {
    if ( p_sdl_renderer != NULL ) {
        SDL_DestroyRenderer( p_sdl_renderer );
    }
    if ( p_sdl_window != NULL ) {
        SDL_DestroyWindow( p_sdl_window );
    }
}
