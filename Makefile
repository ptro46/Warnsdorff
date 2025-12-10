SHELL := /bin/bash

CC      := g++

CFLAGS  := -I/opt/homebrew/include \
			-I/usr/local/include \
			-Igame_sdk \
			-Imarbles \
			-Iscenes \
			-I.
CFLAGS  += -D_THREAD_SAFE -MMD -MP

CLIBS   := -L/opt/homebrew/lib -lSDL3 -lSDL3_image -lSDL3_ttf \
			-L/usr/local/lib -lSDL3_mixer \
			-framework AudioToolbox -framework AudioUnit -framework CoreFoundation \
			-lm 

#CFLAGS  := -I/opt/homebrew/include -I/usr/local/include -D_THREAD_SAFE -MMD -MP -fsanitize=address -g
#CLIBS   := -L/opt/homebrew/lib -lSDL3 -lSDL3_image -L/usr/local/lib -lSDL3_mixer -framework AudioToolbox -framework AudioUnit -framework CoreFoundation  -lm -fsanitize=address

SDK_DIR := game_sdk
SDK_SRC := $(SDK_DIR)/k_window.cpp \
			$(SDK_DIR)/k_texture.cpp \
			$(SDK_DIR)/k_sounds_manager.cpp

SCENES_DIR  := scenes
SCENES_SRC  := $(SCENES_DIR)/k_scene.cpp \
				$(SCENES_DIR)/k_scene_loading.cpp \
				$(SCENES_DIR)/k_scene_manager.cpp

SRC := $(SDK_SRC) $(SCENES_SRC) cheval.cpp

OBJ     := $(SRC:.cpp=.o)
DEP       := $(SRC:.cpp=.d)

MAIN      := warnsdorff.cpp
OBJ_MAIN  := warnsdorff.o
DEP_MAIN  := $(MAIN:.cpp=.d)

BIN       := warnsdorff

.PHONY: all clean depend

all: $(BIN)

# Link des .o pour créer l'exécutable
$(BIN): $(OBJ) $(OBJ_MAIN)
	$(CC) $(CFLAGS) -o $@ $^ $(CLIBS)

# Règle générique : .c → .o
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

-include $(DEP) $(DEP_MAIN)

depend: ;

clean:
	rm -f $(BIN) $(OBJ) $(OBJ_MAIN)

clean_all:
	rm -f $(BIN) $(OBJ) $(OBJ_MAIN) *.d $(SDK_DIR)/*.d $(MARBLES_DIR)/*.d $(SCENES_DIR)/*.d $(TILES_DIR)/*.d $(TRACK_CHANGE_COLOR_DIR)/*.d $(TRACK_DIODE_WAY_DIR)/*.d $(TRACK_DIODE_COLOR_DIR)/*.d $(TRACK_START_DIR)/*.d $(TRACK_STOP_DIR)/*.d $(TRACK_TELEPORT_DIR)/*.d $(TRACKS_DIR)/*.d $(BASES_DIR)/*.d *~

