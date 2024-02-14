CC=gcc

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include
BIN_DIR=bin/
SRC_DIR=src/
LIB_DIR=lib/

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
INCLUDES=-I${SDLINC_DIR} 

PROG=prototype

all: prototype

prototype: ${BIN_DIR}prototype_sdl.o ${BIN_DIR}texture.o ${BIN_DIR}EventOp.o
	${CC} -o ${BIN_DIR}${PROG} ${BIN_DIR}prototype_sdl.o ${BIN_DIR}texture.o ${BIN_DIR}EventOp.o ${LIBS} ${INCLUDES}
	
bin/prototype_sdl.o: ${SRC_DIR}prototype_sdl.c ${LIB_DIR}texture.h ${LIB_DIR}EventOp.h
	${CC} -c ${SRC_DIR}prototype_sdl.c -o $@
	
bin/texture.o: ${SRC_DIR}texture.c
	${CC} -c ${SRC_DIR}texture.c -o $@
	
bin/EventOp.o: ${SRC_DIR}EventOp.c
	${CC} -c ${SRC_DIR}EventOp.c -o $@
	

clean: 
	rm -f ${BIN_DIR}*.o
mrproper: clean
	rm -f ${BIN_DIR}${PROG}
