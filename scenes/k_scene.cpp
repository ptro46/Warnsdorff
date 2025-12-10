#include <k_scene.h>
#include <k_window.h>
#include <k_texture.h>

KScene::KScene(SceneName name, KWindow *p_window) {
    m_name = scene_name_to_string(name) ;
    pk_window = p_window ;
}

KScene::~KScene() {
}

void
KScene::play_split_animation(KScene *p_scene_from) {
}


void
KScene::perform_gameplay() {
    // override in KSceneAbstractWorld
}

bool
KScene::win_game() {
    // override in KSceneAbstractWorld
    return false ;
}

bool
KScene::lose_game() {
    // override in KSceneAbstractWorld
    return false ;
}


KSceneSplitAnimation::KSceneSplitAnimation(SceneName name, KWindow *p_window)
    :KScene(name, p_window) {
}

KSceneSplitAnimation::~KSceneSplitAnimation() {
}

void
KSceneSplitAnimation::play_split_animation(KScene *p_scene_from) {
    int winW = pk_window->get_width();
    int winH = pk_window->get_height();
    
    const int delayMs = 16;

    printf("play_split_animation :: aquaworld %d %d\n",winW, winH);

    float y2=winH/2;
    float step = 5.0;
    float y2_dst = 0.0;
    for(float y1=winH/2; y1>=0; y1-=step, y2+=step) {
        SDL_SetRenderDrawColor(pk_window->get_renderer(), 30,30,30,255);
        SDL_RenderClear(pk_window->get_renderer());

        p_scene_from->get_background_texture()->blit_texture_full(pk_window,
                                                                  0, 0, (float)winW, (float)winH) ;

        get_texture_loader()->blit_texture_part(pk_window,
                                                0.0f, y1,   (float)winW, (float)winH/2,
                                                0.0f, 0.0f, (float)winW, y2_dst) ;
        get_texture_loader()->blit_texture_part(pk_window,
                                                0.0f, (float)winH/2,        (float)winW, y2,
                                                0.0f, (float)(winH-y2_dst), (float)winW, (float)winH);

        SDL_RenderPresent(pk_window->get_renderer());
        SDL_Delay(delayMs);
        y2_dst += step ;
        
    }
    for(float y1=0; y1<winH/2; y1+=step, y2-=step) {
        SDL_SetRenderDrawColor(pk_window->get_renderer(), 30,30,30,255);
        SDL_RenderClear(pk_window->get_renderer());

        get_texture_scene()->blit_texture_full(pk_window,
                                               0, 0, (float)winW, (float)winH) ;

        render_gameboard();
        
        get_texture_loader()->blit_texture_part(pk_window,
                                                0.0f, y1,   (float)winW, (float)winH/2,
                                                0.0f, 0.0f, (float)winW, y2_dst) ;
        get_texture_loader()->blit_texture_part(pk_window,
                                                0.0f, (float)winH/2,        (float)winW, y2,
                                                0.0f, (float)(winH-y2_dst), (float)winW, (float)winH);
        SDL_RenderPresent(pk_window->get_renderer());
        SDL_Delay(delayMs);
        y2_dst -= step ;
        
    }
    
}
