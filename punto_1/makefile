CC=gcc
CFLAGS=-O3
NAME=placas

all:
	$(CC) $(NAME).c -o $(NAME) $(CFLAGS)
	./$(NAME)
	python2 grafica.py
	rm *.dat
clear:
	rm *.dat
