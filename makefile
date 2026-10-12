cc = gcc

all:
	$(cc) main.c display.c create.c search.c inverted.c save.c update.c
clean:
	rm -f a.out