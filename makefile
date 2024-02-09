
CC=gcc

SDL_DIR=${HOME}/SDL2
SDLLIB_DIR=${SDL_DIR}/lib
SDLINC_DIR=${SDL_DIR}/include

LIBS=-L${SDLLIB_DIR} -lSDL2 -lSDL2_ttf -lSDL2_image -lSDL2_mixer
INCLUDES=-I${SDLINC_DIR} 

PROG=prototype

all: prototype

prototype: prototype_sdl.o texture.o EventOp.o
	${CC} -o ${PROG} prototype_sdl.o texture.o EventOp.o ${LIBS} ${INCLUDES}
prototype_sdl.o: prototype_sdl.c texture.h EventOp.h
	${CC} -c prototype_sdl.c
texture.o: texture.c
	${CC} -c texture.c
EventOp.o: EventOp.c
	${CC} -c EventOp.c

clean: 
	rm -f *.o
mrproper: clean
	rm -f ${PROG}

