TARGET = game
CC = g++
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = -MMD

PREF_BIN = ./bin/

PREF_BUILD = ./obj/
PREF_BUILD_PROJ = ${PREF_BUILD}src/proj/
PREF_BUILD_LIBPROJ = ${PREF_BUILD}src/libproj/

PREF_SRC = ./src/
PREF_SRC_PROJ = ${PREF_SRC}proj/
PREF_SRC_LIBPROJ = ${PREF_SRC}libproj/

default : all 

all : ${TARGET}

${TARGET} : ${PREF_BUILD_PROJ}main.o ${PREF_BUILD_LIBPROJ}libproj.a
	${CC} ${CFLAGS} -o ${PREF_BIN}$@ $^

${PREF_BUILD_PROJ}main.o : ${PREF_SRC_PROJ}main.cpp
	${CC} -c ${CFLAGS} ${CPPFLAGS} -o $@ $<

${PREF_BUILD_LIBPROJ}Start.o : ${PREF_SRC_LIBPROJ}Start.cpp
	${CC} -c ${CFLAGS} ${CPPFLAGS} -o $@ $<

${PREF_BUILD_LIBPROJ}libproj.a : ${PREF_BUILD_LIBPROJ}Start.o
	ar rcs $@ $^

clean :
	rm ${PREF_BIN}${TARGET} ${PREF_BUILD_LIBPROJ}*.* ${PREF_BUILD_PROJ}*.*
