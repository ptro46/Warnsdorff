#include <k_window.h>
#include <k_texture.h>

KTexture::KTexture(KWindow *p_window, const char *name, const char *filename) {
    strcpy(this->name, name);
    p_sdl_texture = IMG_LoadTexture(p_window->get_renderer(), filename);
    if (! p_sdl_texture ) {
        fprintf(stderr, "IMG_LoadTexture failed: %s\n", SDL_GetError());
    } else {
        if (!SDL_GetTextureSize(p_sdl_texture, &width, &height)) {
            fprintf(stderr, "SDL_GetTextureSize failed: %s\n", SDL_GetError());
        }        
    }
}

KTexture::~KTexture() {
    SDL_DestroyTexture( p_sdl_texture ) ;
}


//----
// blit part from texture (x1_src,y1_src) (x2_src,y2_src), to part renderer (x1_dst, y1_dst) (x2_dst. y2_dst)
void
KTexture::blit_texture_part(KWindow      *p_window,
                            float        x1_src,
                            float        y1_src,
                            float        x2_src,
                            float        y2_src,
                            float        x1_dst,
                            float        y1_dst,
                            float        x2_dst,
                            float        y2_dst ) {
    SDL_FRect src      = { x1_src, y1_src , x2_src - x1_src, y2_src - y1_src };
    SDL_FRect dst      = { x1_dst, y1_dst , x2_dst - x1_dst, y2_dst - y1_dst };
    SDL_RenderTexture(p_window->get_renderer(), p_sdl_texture, &src, &dst);
}

//----
// blit full texture to part renderer (x1_dst, y1_dst) (x2_dst. y2_dst)
void
KTexture::blit_texture_full(KWindow      *p_window,
                            float        x1_dst,
                            float        y1_dst,
                            float        x2_dst,
                            float        y2_dst ) {
    SDL_FRect dst      = { x1_dst, y1_dst , x2_dst - x1_dst, y2_dst - y1_dst };
    SDL_RenderTexture(p_window->get_renderer(), p_sdl_texture, NULL, &dst);
}

void
KTexture::set_texture_blend_mode() {
    SDL_SetTextureBlendMode(p_sdl_texture, SDL_BLENDMODE_BLEND);
}

void
KTexture::set_texture_alpha(Uint8 alpha) {
    SDL_SetTextureAlphaMod(p_sdl_texture, alpha);
}
