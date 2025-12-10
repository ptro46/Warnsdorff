#include <k_scene_loading.h>

#include <k_texture.h>
#include <k_window.h>

#include <k_scene_manager.h>
#include <k_sounds_manager.h>

#include <SDL3_ttf/SDL_ttf.h>

#include <math.h>

#include <cheval.h>

#define SCREEN_WIDTH       1024
#define SCREEN_HEIGHT      768

#define SQUARE_WIDTH       64 
#define SQUARE_HEIGHT      64 

#define BOARD_WIDTH         8
#define BOARD_HEIGHT        8


#define    START_BUTTON_X        10.0f
#define    START_BUTTON_Y        100.0f
#define    START_BUTTON_W        150.0f
#define    START_BUTTON_H        75.0f

#define    RESET_BUTTON_X        10.0f
#define    RESET_BUTTON_Y        200.0f
#define    RESET_BUTTON_W        150.0f
#define    RESET_BUTTON_H        75.0f

KSceneLoading::KSceneLoading(SceneName name, KWindow *p_window)
    :KScene(name, p_window) {
    p_font = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 18);
    p_font_mark = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 38);

    echiquier = (int **)malloc(8 * sizeof(int*)) ;
    for(int i=0;i<8;i++) {
        echiquier[i] = (int *)malloc(8 * sizeof(int));
        for(int j=0;j<8;j++) {
            echiquier[i][j] = 0 ; // initialise toutes les cases comme etant libre (0) 
        }
    }
    reset_game();
}

KSceneLoading::~KSceneLoading() {
    if ( p_texture_loading ) {
        delete p_texture_loading ;
    }
    if ( p_font ) {
        TTF_CloseFont(p_font);
    }
    if ( p_font_mark ) {
        TTF_CloseFont(p_font_mark);
    }
    if ( p_texture_horse ) {
        delete p_texture_horse ;
    }

    for(int i=0;i<8;i++) {
        free( echiquier[i] );
    }
    free( echiquier ) ;

}

void
KSceneLoading::init() {
    p_texture_loading   = new KTexture(pk_window, "loading", "datas/gfx/backgrounds/fondaqua.png");
    p_texture_horse = new KTexture(pk_window, "Horse", "datas/gfx/cheval.png");
}

KScene*
KSceneLoading::perform_events(int *running) {
    SDL_Event evt;

    while (SDL_PollEvent(&evt)) {
        switch (evt.type) {
        case SDL_EVENT_QUIT:
            *running = 0;
            break;

        case SDL_EVENT_MOUSE_BUTTON_DOWN:
        {
            int mx = evt.button.x;
            int my = evt.button.y;
            if ( mx >= START_BUTTON_X && mx <= START_BUTTON_X+START_BUTTON_W &&
                 my >= START_BUTTON_Y && my <= START_BUTTON_Y+START_BUTTON_H ) {
                g_sounds_manager.play_sound(SoundName::Click);
                start_pressed = true;
                
            } else if ( mx >= RESET_BUTTON_X && mx <= RESET_BUTTON_X+RESET_BUTTON_W &&
                        my >= RESET_BUTTON_Y && my <= RESET_BUTTON_Y+RESET_BUTTON_H ) {
                g_sounds_manager.play_sound(SoundName::Click);
                reset_pressed = true;
                reset_game();
                
            }
                
        }
        }
    }
    return nullptr ;
}

void
KSceneLoading::render() {
    float xStart = SCREEN_WIDTH/2 - ((BOARD_WIDTH+1)*SQUARE_WIDTH)/2 ; 
    float yStart = SCREEN_HEIGHT/2 - ((BOARD_HEIGHT+1)*SQUARE_HEIGHT)/2 ; 
    SDL_SetRenderDrawColor(pk_window->get_renderer(), 30, 30, 30, 255);
    SDL_RenderClear(pk_window->get_renderer());
    SDL_SetRenderDrawColor(pk_window->get_renderer(), 255, 255, 255, 255);
        
    p_texture_loading->blit_texture_full(pk_window, 0, 0, 2048/2, 1536/2);

    for(int i=0;i<BOARD_HEIGHT;i++) {
        for(int j=0;j<BOARD_WIDTH;j++) {
            float x = xStart + j * SQUARE_WIDTH  ;
            float y = yStart + i * SQUARE_HEIGHT ;

            if ((i + j) % 2 == 0) {
                SDL_SetRenderDrawColor(pk_window->get_renderer(), 255, 255, 255, 128);
            } else {
                SDL_SetRenderDrawColor(pk_window->get_renderer(), 0, 0, 0, 128);
            }
            
            SDL_FRect r = { x, y, SQUARE_WIDTH, SQUARE_HEIGHT };
            SDL_RenderFillRect(pk_window->get_renderer(), &r);            
        }
    }

    // Lettres A–H
    for (int j = 0; j < BOARD_WIDTH; ++j) {
        char label[2] = { char('A' + j), '\0' };
        int cx = xStart + j * SQUARE_WIDTH + SQUARE_WIDTH / 2;
        int cy = yStart - 20;
        draw_text_center(pk_window->get_renderer(), p_font, label, cx, cy);

        cx = xStart + j * SQUARE_WIDTH + SQUARE_WIDTH / 2;
        cy = yStart + 8 * SQUARE_HEIGHT + 20;
        draw_text_center(pk_window->get_renderer(), p_font, label, cx, cy);
        
    }

    // Chiffres 8–1 (8 en haut, 1 en bas)
    for (int i = 0; i < BOARD_HEIGHT; ++i) {
        int rank = (i+1);
        char label[2];
        snprintf(label, sizeof(label), "%d", rank);
        int cx = xStart - 20;
        int cy = yStart + i * SQUARE_HEIGHT + SQUARE_HEIGHT / 2;
        draw_text_center(pk_window->get_renderer(), p_font, label, cx, cy);

        cx = xStart + 8 * SQUARE_WIDTH + 20;
        cy = yStart + i * SQUARE_HEIGHT + SQUARE_HEIGHT / 2;
        draw_text_center(pk_window->get_renderer(), p_font, label, cx, cy);

    }    

    if ( running_game ) {
        if ( case_libre(echiquier) && continue_game == true ) {
            if ( horse_is_moving ) {
                //mark_all_positions();
                float x_from = xStart + x_horse_moving_from * SQUARE_WIDTH ;
                float y_from = yStart + y_horse_moving_from * SQUARE_HEIGHT ;
                float x_to = xStart + x_horse * SQUARE_WIDTH ;
                float y_to = yStart + y_horse * SQUARE_HEIGHT ;

                float dx = (x_to - x_from) / 20 ;
                float dy = (y_to - y_from) / 20 ;

                float x_current = x_from + move_index * dx ;
                float y_current = y_from + move_index * dy ;
                p_texture_horse->blit_texture_part(pk_window,
                                                   0, 0, p_texture_horse->get_width(), p_texture_horse->get_height() ,
                                                   x_current, y_current, x_current+SQUARE_WIDTH, y_current+SQUARE_HEIGHT);
                if ( move_index < 20 ) {
                    move_index ++ ;
                } else {
                    echiquier[x_horse][y_horse] = round++ ;
                    horse_is_moving = false ;
                    move_index = 0 ;
                }
            
            
            } else {
                sPosition nouvelle_position = calcule_position_suivante(echiquier, x_horse, y_horse) ;
                x_horse_moving_from = x_horse ;
                y_horse_moving_from = y_horse ;
                x_horse = nouvelle_position.x ;
                y_horse = nouvelle_position.y ;
                move_index = 0 ;
                horse_is_moving = true ;
            }
        } else {
            continue_game = false ;
            running_game = false ;
        }
    }
    mark_all_positions();

    if ( running_game == false ) {
        if ( start_pressed ) {
            render_start_button_pushed();
            start_pressed = false ;
            running_game = true ;
        } else {
            render_start_button_released();
        }

        if ( reset_pressed ) {
            render_reset_button_pushed();
            reset_pressed = false ;
        } else {
            render_reset_button_released();
        }
    } else {
        render_start_button_disabled() ;
        render_reset_button_disabled() ;        
    }
    SDL_Delay(20);
    SDL_RenderPresent(pk_window->get_renderer());
}

void
KSceneLoading::render_gameboard() {
}

void
KSceneLoading::start_play_music() {
}

void
KSceneLoading::stop_play_music() {
}

KTexture*
KSceneLoading::get_background_texture() {
    return p_texture_loading ;
}

KTexture*
KSceneLoading::get_texture_scene() {
    return p_texture_loading ;
}

void
KSceneLoading::game_started() {
}

void
KSceneLoading::draw_text_center(SDL_Renderer *renderer, TTF_Font *font, const char *text, int cx, int cy) {
    SDL_Color color = { 220, 220, 220, 255 };

    // length = 0 => texte UTF-8 terminé par '\0'
    SDL_Surface *surf = TTF_RenderText_Blended(font, text, 0, color);
    if (!surf) {
        fprintf(stderr, "TTF_RenderText_Blended error: %s\n", SDL_GetError());
        return;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    if (!tex) {
        fprintf(stderr, "SDL_CreateTextureFromSurface error: %s\n", SDL_GetError());
        SDL_DestroySurface(surf);
        return;
    }

    SDL_FRect dst = {
        (float)(cx - surf->w / 2),
        (float)(cy - surf->h / 2),
        (float)surf->w,
        (float)surf->h
    };

    SDL_RenderTexture(renderer, tex, NULL, &dst);

    SDL_DestroyTexture(tex);
    SDL_DestroySurface(surf);
}

void
KSceneLoading::draw_text_mark(SDL_Renderer *renderer, TTF_Font *font, const char *text, int cx, int cy) {
    SDL_Color color = { 255, 0, 0, 255 };

    // length = 0 => texte UTF-8 terminé par '\0'
    SDL_Surface *surf = TTF_RenderText_Blended(font, text, 0, color);
    if (!surf) {
        fprintf(stderr, "TTF_RenderText_Blended error: %s\n", SDL_GetError());
        return;
    }

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    if (!tex) {
        fprintf(stderr, "SDL_CreateTextureFromSurface error: %s\n", SDL_GetError());
        SDL_DestroySurface(surf);
        return;
    }

    SDL_FRect dst = {
        (float)(cx - surf->w / 2),
        (float)(cy - surf->h / 2),
        (float)surf->w,
        (float)surf->h
    };

    SDL_RenderTexture(renderer, tex, NULL, &dst);

    SDL_DestroyTexture(tex);
    SDL_DestroySurface(surf);
}


void
KSceneLoading::reset_game() {
    srand(time(NULL));
    x_horse = rand() % 8 ;
    y_horse = rand() % 8 ;
    continue_game = true ;
    horse_is_moving = false ;
    move_index = 0 ;
    round = 1 ;
    start_pressed = false ;
    reset_pressed = false ;
    running_game = false ;

    for(int i=0;i<8;i++) {
        for(int j=0;j<8;j++) {
            echiquier[i][j] = 0 ; // initialise toutes les cases comme etant libre (0) 
        }
    }
    
}

void
KSceneLoading::mark_all_positions() {
    float xStart = SCREEN_WIDTH/2 - ((BOARD_WIDTH+1)*SQUARE_WIDTH)/2 ; 
    float yStart = SCREEN_HEIGHT/2 - ((BOARD_HEIGHT+1)*SQUARE_HEIGHT)/2 ; 
    char label[3];

    for(int i=0;i<BOARD_HEIGHT; i++) {
        for(int j=0; j<BOARD_WIDTH; j++) {
            if ( echiquier[i][j] != 0 ) {
                int cx = xStart + i * SQUARE_WIDTH  + SQUARE_WIDTH/2;
                int cy = yStart + j * SQUARE_HEIGHT + SQUARE_HEIGHT/2;
                snprintf(label, sizeof(label), "%d", echiquier[i][j]);
                draw_text_mark(pk_window->get_renderer(), p_font_mark, label, cx, cy);
            }
        }
    }
    
}

void
KSceneLoading::fill_rounded_rect(SDL_Renderer *renderer, const SDL_FRect *rect, float radius) {
    float x = rect->x;
    float y = rect->y;
    float w = rect->w;
    float h = rect->h;

    for (int iy = 0; iy < (int)h; ++iy) {
        float dx = 0.0f;

        if (iy < radius) {
            float dy = radius - (float)iy;
            dx = radius - sqrtf(radius * radius - dy * dy);
        } else if (iy >= h - radius) {
            float dy = (float)iy - (h - radius - 1.0f);
            dx = radius - sqrtf(radius * radius - dy * dy);
        }

        float x1 = x + dx;
        float x2 = x + w - dx;

        SDL_RenderLine(renderer, x1, y + (float)iy, x2, y + (float)iy);
    }
}

void
KSceneLoading::render_button(const char *label, SDL_Renderer *renderer, TTF_Font *font,  const SDL_FRect *rect, bool pressed, bool disabled) {
    const float radius = 40.0f;

    SDL_Color baseNormal           = { 60,  60,  60, 255 };
    SDL_Color basePressed          = { 40,  40,  40, 255 };
    SDL_Color light                = { 220, 220, 220, 255 };
    SDL_Color dark                 = {  20,  20,  20, 255 };
    SDL_Color textColor            = { 255, 255, 255, 255 };
    SDL_Color textColorPressed     = { 255, 0, 0, 255 };
    SDL_Color textColorDisabled    = { 127, 127, 127, 255 };

    SDL_Color base = pressed ? basePressed : baseNormal;

    // Remplissage du fond arrondi
    SDL_SetRenderDrawColor(renderer, base.r, base.g, base.b, base.a);
    fill_rounded_rect(renderer, rect, radius);

    SDL_Surface *surf = NULL;
    if ( disabled ) {
        surf = TTF_RenderText_Blended(font, label, 0, textColorDisabled);
    } else {
        if ( pressed ) {
            surf = TTF_RenderText_Blended(font, label, 0, textColorPressed);
        } else {
            surf = TTF_RenderText_Blended(font, label, 0, textColor);
        }
    }
    if (!surf) return;

    float tw = (float)surf->w;
    float th = (float)surf->h;

    SDL_Texture *tex = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_DestroySurface(surf);
    if (!tex) return;

    // Légère translation quand le bouton est enfoncé
    float offset = pressed ? 2.0f : 0.0f;

    SDL_FRect dst;
    dst.w = tw;
    dst.h = th;
    dst.x = rect->x + (rect->w - tw) / 2.0f + offset;
    dst.y = rect->y + (rect->h - th) / 2.0f + offset;

    SDL_RenderTexture(renderer, tex, NULL, &dst);
    SDL_DestroyTexture(tex);
    
}

void
KSceneLoading::render_start_button_released() {
    SDL_FRect btnRectStart = { START_BUTTON_X, START_BUTTON_Y, START_BUTTON_W, START_BUTTON_H };
    render_button("Start", pk_window->get_renderer(), p_font_mark, &btnRectStart, false, false);
}

void
KSceneLoading::render_start_button_pushed() {
    SDL_FRect btnRectStart = { START_BUTTON_X, START_BUTTON_Y, START_BUTTON_W, START_BUTTON_H };
    render_button("Start", pk_window->get_renderer(), p_font_mark, &btnRectStart, true, false);
}

void
KSceneLoading::render_start_button_disabled() {
    SDL_FRect btnRectStart = { START_BUTTON_X, START_BUTTON_Y, START_BUTTON_W, START_BUTTON_H };
    render_button("Start", pk_window->get_renderer(), p_font_mark, &btnRectStart, false, true);
}

void
KSceneLoading::render_reset_button_released() {
    SDL_FRect btnRectReset = { RESET_BUTTON_X, RESET_BUTTON_Y, RESET_BUTTON_W, RESET_BUTTON_H };
    render_button("Reset", pk_window->get_renderer(), p_font_mark, &btnRectReset, false, false);
}

void
KSceneLoading::render_reset_button_pushed() {
    SDL_FRect btnRectReset = { RESET_BUTTON_X, RESET_BUTTON_Y, RESET_BUTTON_W, RESET_BUTTON_H };
    render_button("Reset", pk_window->get_renderer(), p_font_mark, &btnRectReset, true, false);
}

void
KSceneLoading::render_reset_button_disabled() {
    SDL_FRect btnRectReset = { RESET_BUTTON_X, RESET_BUTTON_Y, RESET_BUTTON_W, RESET_BUTTON_H };
    render_button("Reset", pk_window->get_renderer(), p_font_mark, &btnRectReset, false, true);
}
