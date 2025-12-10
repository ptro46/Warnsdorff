
#include <k_scene_manager.h>
#include <k_scene.h>
#include <k_window.h>

#include <k_scene_loading.h>

#include <cstring>

KSceneManager::KSceneManager()  {
}

KSceneManager::~KSceneManager() {
}

void KSceneManager::init(KWindow *p_window) {
    KScene    *    p_scene ;

    p_scene = new KSceneLoading(SceneName::Loading, p_window);
    p_scene->init();
    g_scene_manager.add_k_scene(SceneName::Loading, p_scene);
}

void KSceneManager::add_k_scene(SceneName name, KScene *p_scene) {
    m_scenes[name] = p_scene ;
}

KScene* KSceneManager::get_k_scene_by_name(SceneName name) {
    auto it = m_scenes.find(name);
    if (it != m_scenes.end()) {
        return it->second;
    }
    return nullptr;
}

void KSceneManager::delete_all_scenes() {
    for (auto &entry : m_scenes) {
        delete entry.second ;
    }
    m_scenes.clear();
}
