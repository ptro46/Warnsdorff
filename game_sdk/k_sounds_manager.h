#ifndef K_MUSIC_MANAGER__H
#define K_MUSIC_MANAGER__H

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

#include <map>
#include <string>
#include <cstdio>

using namespace std;

enum class SoundName {
        Click,
};

inline const char* to_string(SoundName s) {
    switch (s) {
    case SoundName::Click:         return "click";
    }
    return ""; // cas impossible
}

class KSoundsManager {
private:
    map<string, Mix_Music*>         m_musics;
    map<SoundName, Mix_Chunk*>      m_sounds;
        
public:
    KSoundsManager() ;
    ~KSoundsManager() ;

    void        init();
    void        deinit();
    
    void        add_music(const char *music_name, const char *music_path);
    void        play_music(const char *music_name);
    void        stop_music();
    void        pause_music();
    void        resume_music();
    void        delete_all_musics();

    void        load_all_sounds();
    void        add_sound(SoundName sound_name, const char *sound_path);
    void        play_sound(SoundName sound_name);
    void        delete_all_sounds();

} ;

extern KSoundsManager    g_sounds_manager ;

#endif // K_MUSIC_MANAGER__H
