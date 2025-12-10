#ifndef K_SCENE__H
#define K_SCENE__H

#include <k_scene_manager.h>
#include <string>

class KWindow;
class KTexture;

class KScene {
protected:
    string                  m_name;
    KWindow        *        pk_window;
    
public:
    KScene(SceneName name, KWindow *p_window);
    virtual ~KScene();

    virtual    void        init()                        = 0 ;
    virtual    KScene*     perform_events(int *running)  = 0 ; // return KScene transition destination
    virtual    void        render()                      = 0 ;
    virtual    void        render_gameboard()            = 0 ;

    virtual    void        start_play_music()            = 0 ;
    virtual    void        stop_play_music()             = 0 ;
    
    virtual    KTexture*   get_background_texture()      = 0 ;

    virtual    void        game_started()                = 0 ;
    
    virtual    void        perform_gameplay() ;
    virtual    bool        win_game();
    virtual    bool        lose_game();
    // only KSceneAquaworld, KSceneFactory, KSceneDungeon, KSceneManager overload it
    virtual    void        play_split_animation(KScene *p_scene_from) ;
} ;

class KSceneSplitAnimation : public KScene {
public:
    KSceneSplitAnimation(SceneName name, KWindow *p_window);
    virtual ~KSceneSplitAnimation();
    
    virtual    KTexture*   get_texture_scene() = 0 ;
    virtual    KTexture*   get_texture_loader() = 0 ;
    // only KSceneAquaworld, KSceneFactory, KSceneDungeon, KSceneManager overload it
    virtual    void        play_split_animation(KScene *p_scene_from) ; 
} ;

#endif // K_SCENE__H
