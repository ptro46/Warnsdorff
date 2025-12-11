# Introduction
Le problème du cavalier (ou encore polygraphie ou algorithme du cavalier ou cavalier d'Euler) est un problème mathématico-logique fondé sur les déplacements du cavalier du jeu d'échecs : un cavalier partant d'une case quelconque doit visiter chaque case sans y repasser.

l'implèmentation s'appuie sur l'heuristique de Warnsdorf.


[Problème du cavalier](https://fr.wikipedia.org/wiki/Problème_du_cavalier)

# prerequis

## Xcode Command Line Tools

```bash
$> xcode-select --install
```

## Homebrew (si pas déjà installé)

```bash
$> /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

## Installation de SDL3 (+ image + ttf)

### Installations

```bash
$> brew update
$> brew install sdl3 sdl3_image sdl3_ttf
```

### Vérifications

```bash
$> brew info sdl3
$> brew info sdl3_image
$> brew info sdl3_ttf
```

Les headers se retrouveront typiquement dans :
 - /opt/homebrew/include/SDL3/…
 - et les libs dans /opt/homebrew/lib/libSDL3*.dylib

### Installation de cmake

```bash
$> brew update
$> brew install cmake
```

### Installation de SDL3_mixer

```bash
$> git clone https://github.com/libsdl-org/SDL_mixer.git
$> cd SDL_mixer
```

```bash
$> cmake -S . -B build
$> cmake --build build
$> sudo cmake --install build --prefix /usr/local
```

# build
```bash
$> make
g++ -I/opt/homebrew/include -I/usr/local/include -Igame_sdk -Imarbles -Iscenes -I. -D_THREAD_SAFE -MMD -MP -c game_sdk/k_window.cpp -o game_sdk/k_window.o
g++ -I/opt/homebrew/include -I/usr/local/include -Igame_sdk -Imarbles -Iscenes -I. -D_THREAD_SAFE -MMD -MP -c game_sdk/k_texture.cpp -o game_sdk/k_texture.o
g++ -I/opt/homebrew/include -I/usr/local/include -Igame_sdk -Imarbles -Iscenes -I. -D_THREAD_SAFE -MMD -MP -c game_sdk/k_sounds_manager.cpp -o game_sdk/k_sounds_manager.o
g++ -I/opt/homebrew/include -I/usr/local/include -Igame_sdk -Imarbles -Iscenes -I. -D_THREAD_SAFE -MMD -MP -c scenes/k_scene.cpp -o scenes/k_scene.o
g++ -I/opt/homebrew/include -I/usr/local/include -Igame_sdk -Imarbles -Iscenes -I. -D_THREAD_SAFE -MMD -MP -c scenes/k_scene_loading.cpp -o scenes/k_scene_loading.o
g++ -I/opt/homebrew/include -I/usr/local/include -Igame_sdk -Imarbles -Iscenes -I. -D_THREAD_SAFE -MMD -MP -c scenes/k_scene_manager.cpp -o scenes/k_scene_manager.o
g++ -I/opt/homebrew/include -I/usr/local/include -Igame_sdk -Imarbles -Iscenes -I. -D_THREAD_SAFE -MMD -MP -c cheval.cpp -o cheval.o
g++ -I/opt/homebrew/include -I/usr/local/include -Igame_sdk -Imarbles -Iscenes -I. -D_THREAD_SAFE -MMD -MP -c warnsdorff.cpp -o warnsdorff.o
g++ -I/opt/homebrew/include -I/usr/local/include -Igame_sdk -Imarbles -Iscenes -I. -D_THREAD_SAFE -MMD -MP -o warnsdorff game_sdk/k_window.o game_sdk/k_texture.o game_sdk/k_sounds_manager.o scenes/k_scene.o scenes/k_scene_loading.o scenes/k_scene_manager.o cheval.o warnsdorff.o -L/opt/homebrew/lib -lSDL3 -lSDL3_image -lSDL3_ttf -L/usr/local/lib -lSDL3_mixer -framework AudioToolbox -framework AudioUnit -framework CoreFoundation -lm
```

```bash
$> ./warnsdorff
```

# demo
[Demo](https://youtu.be/WcejBXd4c3Y)


