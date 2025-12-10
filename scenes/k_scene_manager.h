#ifndef K_SCENE_MANAGER__H
#define K_SCENE_MANAGER__H

#include <map>
#include <string>

class KScene;
class KWindow;

using namespace std;

enum class SceneName {
        Loading      ,
} ;

inline const char* scene_name_to_string(SceneName s) {
    switch (s) {
        case SceneName::Loading:   return "loading";
            
    }
    return ""; // cas impossible
}

class KSceneManager {
private:
    map<SceneName, KScene*> m_scenes;
    
public:
    KSceneManager();
    ~KSceneManager();

    void       init(KWindow *p_window);
    KScene*    get_k_scene_by_name(SceneName name);
    void       delete_all_scenes();

private:
    void       add_k_scene(SceneName name, KScene *p_scene);
} ;

extern KSceneManager    g_scene_manager ;

#endif // K_SCENE_MANAGER__H

