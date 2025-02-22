CC = clang
CFLAGS= -std=c17 -Wall -Wextra -ggdb
LIBS= -lraylib -lm -ldl -lpthread -lglfw -lc

bin/main: src/main.c src/config.h 
	${CC} ${CFLAGS} -o bin/main src/main.c ${LIBS}

run: bin/main
	./bin/main

clean: 
	mkdir -p bin
	rm bin/main

all: clean
