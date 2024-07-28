CC = gcc
OBJ = list.c

%.o: %.c 
	$(CC) -c -o $@ $< 
list: $(OBJ) 
	$(CC) -o $@ $^ 
