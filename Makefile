all: emotion

emotion: emotion.c
	gcc -Wall -Werror -o emotion emotion.c

clean:
	rm -rf emotion.o
