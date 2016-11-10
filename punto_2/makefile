CC=g++
CFLAGS=-O3
NAME=cuerda

all:
	$(CC) $(NAME).c -o $(NAME) $(CFLAGS)
	./$(NAME)
	python2 animacion.py
	rm *.dat *.png *.avi
clear:
	rm *.dat *.png *.avi
