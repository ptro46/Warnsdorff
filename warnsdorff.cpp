#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_mixer/SDL_mixer.h>

#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/errno.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdbool.h>


#include <k_window.h>
#include <k_texture.h>

#include <k_scene.h>
#include <k_scene_manager.h>
#include <k_sounds_manager.h>

KSceneManager        g_scene_manager ;
KSoundsManager       g_sounds_manager ;

int main(int argc, char *argv[]) {
    int running = 1;
    SDL_Event evt;


    srand((unsigned)time(NULL));
    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO )) {
        fprintf(stderr, "Échec de SDL_Init : %s\n", SDL_GetError());
        return 1;
    }

    if (! TTF_Init() ) {
        fprintf(stderr, "Échec de TTF_Init : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    g_sounds_manager.init();
    g_sounds_manager.load_all_sounds();
    
    g_sounds_manager.add_music("energy","datas/music/energy-module-1.mp3");
    g_sounds_manager.play_music("energy");
    
    KWindow   *    p_window = new KWindow("Warnsdorff", 2048/2, 1536/2);
    KScene    *    p_scene ;

    g_scene_manager.init(p_window);
    
    p_scene = g_scene_manager.get_k_scene_by_name(SceneName::Loading);
    
    while (running) {
        KScene *p_destination_scene = p_scene->perform_events(&running);
        if ( p_destination_scene != nullptr ) {
            p_destination_scene->play_split_animation(p_scene);
            p_scene = p_destination_scene;
            p_scene->render();
        } else {
            p_scene->render() ;
            
        }
        p_scene->game_started();
        //SDL_Delay(500); 
    }

    g_scene_manager.delete_all_scenes();
    g_sounds_manager.delete_all_musics();
    g_sounds_manager.delete_all_sounds();
    g_sounds_manager.deinit();
    delete p_window ;
    TTF_Quit();
    Mix_Quit();
    SDL_Quit();
}
