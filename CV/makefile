# Program name
PROGRAM = Program

# Compiler
CC = g++

# Flags
# -g -> Used with gdb
# -Wall -> Shows all errors
FLAGS = -g -Wall

# Directories
SRC = ./src
BUILD = ./build
BIN = ./bin

# Source files
FILES = \
        ${SRC}/Driver.cpp\
        ${SRC}/Game.cpp\
        ${SRC}/Poster.cpp\
        ${SRC}/Tracker.cpp\
        ${SRC}/main.cpp

# Object files
OBJS = \
        ${BUILD}/Driver.o\
        ${BUILD}/Game.o\
        ${BUILD}/Poster.o\
        ${BUILD}/Tracker.o\
        ${BUILD}/main.o

# Make options
all: Program

${PROGRAM}: ${OBJS}
	${CC} -o ${BIN}/${PROGRAM} ${OBJS} `pkg-config opencv --libs` `pkg-config curlpp --libs`

# Insert object compilation code below

${BUILD}/Driver.o: ${SRC}/Driver.cpp
	${CC} ${FLAGS} -c $^ 
	mv -f Driver.o ${BUILD}

${BUILD}/Game.o: ${SRC}/Game.cpp
	${CC} ${FLAGS} -c $^ 
	mv -f Game.o ${BUILD}

${BUILD}/Poster.o: ${SRC}/Poster.cpp
	${CC} ${FLAGS} -c $^ 
	mv -f Poster.o ${BUILD}

${BUILD}/SimInput.o: ${SRC}/SimInput.cpp
	${CC} ${FLAGS} -c $^ 
	mv -f SimInput.o ${BUILD}

${BUILD}/Tracker.o: ${SRC}/Tracker.cpp
	${CC} ${FLAGS} -c $^ 
	mv -f Tracker.o ${BUILD}

${BUILD}/main.o: ${SRC}/main.cpp
	${CC} ${FLAGS} -c $^ 
	mv -f main.o ${BUILD}

# Cleans out the build directory
clean:
	rm -f ${BUILD}/*.*
