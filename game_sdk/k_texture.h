#ifndef K_TEXTURE__H
#define K_TEXTURE__H

#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>

class KWindow;

class KTexture {
private:
    SDL_Texture        *        p_sdl_texture;

    char                        name[256];
    float                       width ;
    float                       height ;

public:
    KTexture(KWindow *p_window, const char *name, const char *filename) ;
    ~KTexture();


    float                get_width()  { return width; }
    float                get_height() { return height; }   
    
    //----
    // blit part from texture (x1_src,y1_src) (x2_src,y2_src), to part renderer (x1_dst, y1_dst) (x2_dst. y2_dst)
    void    blit_texture_part(KWindow      *p_window,
                              float        x1_src,
                              float        y1_src,
                              float        x2_src,
                              float        y2_src,
                              float        x1_dst,
                              float        y1_dst,
                              float        x2_dst,
                              float        y2_dst );

    //----
    // blit full texture to part renderer (x1_dst, y1_dst) (x2_dst. y2_dst)
    void    blit_texture_full(KWindow      *p_window,
                              float        x1_dst,
                              float        y1_dst,
                              float        x2_dst,
                              float        y2_dst );

    void    set_texture_blend_mode();
    void    set_texture_alpha(Uint8 alpha);
} ;

#endif // K_TEXTURE__H
