.PHONY: all

all:
	gcc -g -o xdemo xdemo.c -lX11


clean:
	rm -rf xdemo xdemo.o
