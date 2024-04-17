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

prototype: ${BIN_DIR}prototype_sdl.o ${BIN_DIR}texture.o ${BIN_DIR}EventOp.o ${BIN_DIR}type.o ${BIN_DIR}lib_menu.o ${BIN_DIR}utils.o ${BIN_DIR}fmap.o ${BIN_DIR}fpnj.o ${BIN_DIR}fmobs.o ${BIN_DIR}combat.o ${BIN_DIR}fbibliotheque.o
	${CC} -Wall -o ${BIN_DIR}${PROG} ${BIN_DIR}prototype_sdl.o ${BIN_DIR}texture.o ${BIN_DIR}EventOp.o  ${BIN_DIR}type.o ${BIN_DIR}lib_menu.o ${BIN_DIR}utils.o ${BIN_DIR}fmap.o ${BIN_DIR}fpnj.o ${BIN_DIR}fmobs.o ${BIN_DIR}combat.o ${BIN_DIR}fbibliotheque.o ${LIBS} ${INCLUDES}

test_unit: ${BIN_DIR}test_unit.o ${BIN_DIR}texture.o ${BIN_DIR}EventOp.o ${BIN_DIR}type.o ${BIN_DIR}lib_menu.o
	${CC} -Wall -o ${BIN_DIR}$@ ${BIN_DIR}test_unit.o ${BIN_DIR}texture.o ${BIN_DIR}EventOp.o  ${BIN_DIR}type.o ${BIN_DIR}lib_menu.o ${LIBS} ${INCLUDES} -lcunit
	
bin/test_unit.o: ${SRC_DIR}test_unit.c ${LIB_DIR}texture.h ${LIB_DIR}EventOp.h ${LIB_DIR}type.h ${LIB_DIR}init_menu.h
	${CC} -c ${SRC_DIR}test_unit.c -o $@

bin/prototype_sdl.o: ${SRC_DIR}prototype_sdl.c ${LIB_DIR}texture.h ${LIB_DIR}EventOp.h ${LIB_DIR}type.h ${LIB_DIR}init_menu.h ${LIB_DIR}combat.h ${LIB_DIR}fpnj.h ${LIB_DIR}fmobs.h ${LIB_DIR}fmap.h
	${CC} -c ${SRC_DIR}prototype_sdl.c -o $@
	
bin/texture.o: ${SRC_DIR}texture.c
	${CC} -c ${SRC_DIR}texture.c -o $@
	
bin/EventOp.o: ${SRC_DIR}EventOp.c ${LIB_DIR}fpnj.h ${LIB_DIR}fmobs.h ${LIB_DIR}fmap.h ${LIB_DIR}fbibliotheque.h ${LIB_DIR}EventOp.h
	${CC} -c ${SRC_DIR}EventOp.c -o $@

bin/type.o: ${SRC_DIR}type.c
	${CC} -c ${SRC_DIR}type.c -o $@
	
bin/lib_menu.o: ${SRC_DIR}lib_menu.c ${LIB_DIR}texture.h ${LIB_DIR}init_menu.h
	${CC} -c ${SRC_DIR}lib_menu.c -o $@
	
bin/utils.o: ${SRC_DIR}utils.c ${LIB_DIR}type.h ${LIB_DIR}utils.h
	${CC} -c ${SRC_DIR}utils.c -o $@
	
bin/fmap.o: ${SRC_DIR}fmap.c ${LIB_DIR}fmap.h
	${CC} -c ${SRC_DIR}fmap.c -o $@
	
bin/fpnj.o: ${SRC_DIR}fpnj.c ${LIB_DIR}fpnj.h 
	${CC} -c ${SRC_DIR}fpnj.c -o $@
	
bin/fmobs.o: ${SRC_DIR}fmobs.c ${LIB_DIR}fmobs.h
	${CC} -c ${SRC_DIR}fmobs.c -o $@
	
bin/combat.o: ${SRC_DIR}combat.c ${LIB_DIR}EventOp.h ${LIB_DIR}combat.h
	${CC} -c ${SRC_DIR}combat.c -o $@
	
bin/fbibliotheque.o: ${SRC_DIR}fbibliotheque.c ${LIB_DIR}fbibliotheque.h ${LIB_DIR}fmap.h
	${CC} -c ${SRC_DIR}fbibliotheque.c -o $@

clean: 
	rm -f ${BIN_DIR}*.o

mrproper: clean
	rm -f ${BIN_DIR}${PROG}

run: clean all
	cd $(BIN_DIR) && ./$(PROG)