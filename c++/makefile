# - NOTE: This makefile must be located in the
#         parent directory of src, build, and bin

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
        ${SRC}/HelloWorld.cpp\
        ${SRC}/StolenCode.cpp

# Object files
OBJS = \
        ${BUILD}/HelloWorld.o\
        ${BUILD}/StolenCode.o

# Make options
all: Program

${PROGRAM}: ${OBJS}
	${CC} -o ${BIN}/${PROGRAM} ${OBJS}

# Insert object compilation code below

${BUILD}/HelloWorld.o: ${SRC}/HelloWorld.cpp
	${CC} ${FLAGS} -c $^
	mv -f HelloWorld.o ${BUILD}

${BUILD}/StolenCode.o: ${SRC}/StolenCode.cpp
	${CC} ${FLAGS} -c $^
	mv -f StolenCode.o ${BUILD}

# Cleans out the build directory
clean:
	rm -f ${BUILD}/*.*
