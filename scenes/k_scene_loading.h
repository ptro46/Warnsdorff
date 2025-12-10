#ifndef K_SCENE_LOADING__H
#define K_SCENE_LOADING__H

#include <k_scene.h>
#include <k_scene_manager.h>
#include <SDL3_ttf/SDL_ttf.h>

class KTexture;

class KSceneLoading : public KScene {
private:
    KTexture    *    p_texture_loading ;
    TTF_Font    *    p_font;
    TTF_Font    *    p_font_mark;
    KTexture    *    p_texture_horse ;

    int         **   echiquier ;

    int              round ;
    int              x_horse ;
    int              y_horse ;
    bool             continue_game ;

    bool             horse_is_moving ;
    int              move_index ;
    
    int              x_horse_moving_from ;
    int              y_horse_moving_from ;

    bool             start_pressed ;
    bool             reset_pressed ;

    bool             running_game ;
public:
    KSceneLoading(SceneName name, KWindow *p_window);
    ~KSceneLoading();

    virtual    void            init() ;
    virtual    void            render() ;
    virtual    void            render_gameboard() ;

    virtual    KScene*         perform_events(int *running) ; // return KScene transition destination
    
    virtual    void            start_play_music() ;
    virtual    void            stop_play_music() ;

    virtual    KTexture*       get_background_texture() ;
    virtual    KTexture*       get_texture_scene() ;

    virtual    void            game_started() ;

private:
    void                       draw_text_center(SDL_Renderer *renderer, TTF_Font *font, const char *text, int cx, int cy) ;
    void                       draw_text_mark(SDL_Renderer *renderer, TTF_Font *font, const char *text, int cx, int cy) ;

    void                       reset_game() ;
    void                       mark_all_positions();

    void                       fill_rounded_rect(SDL_Renderer *renderer, const SDL_FRect *rect, float radius) ;
    void                       render_button(const char* label, SDL_Renderer *renderer, TTF_Font *font,  const SDL_FRect *rect, bool pressed, bool disabled) ;
    void                       render_start_button_released() ;
    void                       render_start_button_pushed() ;
    void                       render_start_button_disabled() ;

    void                       render_reset_button_released() ;
    void                       render_reset_button_pushed() ;
    void                       render_reset_button_disabled() ;
} ;    

#endif // K_SCENE_LOADING__H
