#include <k_sounds_manager.h>

#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>

#include <map>
#include <string>
#include <cstdio>

KSoundsManager::KSoundsManager() {
}

KSoundsManager::~KSoundsManager() {
}

void
KSoundsManager::init() {
    MIX_InitFlags inits = MIX_INIT_MP3;
    if (!(Mix_Init(inits) & inits)) {
        fprintf(stderr, "Mix_Init failed: %s\n", SDL_GetError());
        SDL_Quit();
        return ;
    }

    SDL_AudioSpec spec;

    spec.freq = MIX_DEFAULT_FREQUENCY;
    spec.format = MIX_DEFAULT_FORMAT;
    spec.channels = MIX_DEFAULT_CHANNELS;
    
    if (!Mix_OpenAudio(0, &spec)) {
        fprintf(stderr, "Mix_OpenAudioDevice failed: %s\n", SDL_GetError());
        Mix_Quit();
        SDL_Quit();
        return ;
    }    
}

void
KSoundsManager:: deinit() {
    Mix_CloseAudio();
}

void
KSoundsManager::add_music(const char *music_name, const char *music_path) {
    Mix_Music *music = Mix_LoadMUS("datas/music/energy-module-1.mp3");
    if (!music) {
        fprintf(stderr, "Mix_LoadMUS failed: %s\n", SDL_GetError());
    } else {
        m_musics.emplace(string(music_name), music);
    }
}

void
KSoundsManager::play_music(const char *music_name) {
    auto it = m_musics.find(music_name);
    if (it != m_musics.end()) {
        if (!Mix_PlayMusic(it->second, -1)) {
            std::fprintf(stderr, "Mix_PlayMusic failed: %s\n", SDL_GetError());
        }
    } else {
        std::fprintf(stderr, "Music '%s' not found\n", music_name);
    }    
}

void
KSoundsManager::stop_music() {
    Mix_HaltMusic();
}

void
KSoundsManager::pause_music() {
    Mix_PauseMusic();
}

void
KSoundsManager::resume_music() {
    Mix_ResumeMusic();
}

void
KSoundsManager::delete_all_musics() {
    for (auto &pair : m_musics) {
        Mix_FreeMusic(pair.second);
    }
    m_musics.clear();    
}

void
KSoundsManager::load_all_sounds() {
    g_sounds_manager.add_sound(SoundName::Click,"datas/sounds/click.wav");    
}

void
KSoundsManager::add_sound(SoundName sound_name, const char *sound_path) {
    Mix_Chunk   *    p_sound;
    p_sound = Mix_LoadWAV(sound_path);
    if (!p_sound) {
        fprintf(stderr, "Mix_LoadWAV failed: %s\n", SDL_GetError());
        return ;
    }
    m_sounds[sound_name] = p_sound ;
}

void
KSoundsManager::play_sound(SoundName sound_name) {
    auto it = m_sounds.find(sound_name);
    if (it != m_sounds.end()) {
        if (Mix_PlayChannel(-1, it->second, 0) < 0) {
            std::fprintf(stderr, "Mix_PlayChannel failed: %s\n", SDL_GetError());
        }
    } else {
        std::fprintf(stderr, "Sound '%s' not found\n", to_string(sound_name));
    }    
}

void
KSoundsManager::delete_all_sounds() {
    for (auto &pair : m_sounds) {
        Mix_FreeChunk(pair.second);
    }
    m_sounds.clear();    
}
