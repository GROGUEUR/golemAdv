CC=gcc
SDL_DIR=$(HOME)/SDL2
SDLLIB_DIR=$(SDL_DIR)/lib
SDLINC_DIR=$(SDL_DIR)/include
BIN_DIR=bin/
SRC_DIR=src/
LIB_DIR=lib/

LIBS=-L$(SDLLIB_DIR) -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
INCLUDES=-I$(SDLINC_DIR) 

PROG=GolemAdventure

OBJS=\
$(BIN_DIR)GolemAdventure.o \
$(BIN_DIR)texture.o \
$(BIN_DIR)EventOp.o \
$(BIN_DIR)type.o \
$(BIN_DIR)lib_menu.o \
$(BIN_DIR)utils.o \
$(BIN_DIR)fmap.o \
$(BIN_DIR)fpnj.o \
$(BIN_DIR)fmobs.o \
$(BIN_DIR)combat.o \
$(BIN_DIR)fbibliotheque.o

.PHONY: all clean mrproper cinematic save run

all: $(PROG)

$(PROG): $(BIN_DIR) $(OBJS)
	$(CC) -Wall -o $(BIN_DIR)$(PROG) $(OBJS) $(LIBS) $(INCLUDES)

$(BIN_DIR)%.o: $(SRC_DIR)%.c
	$(CC) -c -o $@ $< $(INCLUDES)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

clean: 
	rm -f $(BIN_DIR)*.o

mrproper: clean
	rm -f $(BIN_DIR)$(PROG)
	rm -f Ressource/cinem*.png
	rm -f Ressource/Mapping/map/*.png

cinematic:
	@if [ ! -f "Ressource/cinem1.png" ]; then \
		wget -P Ressource/ https://raw.githubusercontent.com/GROGUEUR/golemAdv/main/Ressource/cinem1.png; \
	fi
	@if [ ! -f "Ressource/cinem2.png" ]; then \
		wget -P Ressource/ https://raw.githubusercontent.com/GROGUEUR/golemAdv/main/Ressource/cinem2.png; \
	fi
	@if [ ! -f "Ressource/cinem3.png" ]; then \
		wget -P Ressource/ https://raw.githubusercontent.com/GROGUEUR/golemAdv/main/Ressource/cinem3.png; \
	fi
	@if [ ! -f "Ressource/cinem4.png" ]; then \
		wget -P Ressource/ https://raw.githubusercontent.com/GROGUEUR/golemAdv/main/Ressource/cinem4.png; \
	fi

save: mrproper
	tar -cvzf ../Golem_Adventure.tar.gz *

run: cinematic clean all
	cd $(BIN_DIR) && ./$(PROG)
