CC=gcc
TARGET=ccb_exit
LIBRARY=

all: main.o
	gcc -o $(TARGET) main.o `pkg-config --libs --cflags gtk+-2.0`
main.o: main.c
	gcc -c main.c -o main.o `pkg-config --libs --cflags gtk+-2.0`

install:
	mv $(TARGET) /usr/local/bin/

deinstall:
	rm -rf /usr/local/bin/$(TARGET)

clean:
	rm -rf *.o $(TARGET) *.*~
