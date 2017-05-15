# Macros

CC = g++
CFLAGS = -g -Wall
SRC = probador.cpp
OBJ = probador.o 


# Reglas expl�citas

all:	$(SRC)
	$(CC) $(SRC) -o probador
	$(CC) ./../src/principal.cpp -o main
clean:
	$(RM) $(OBJ) probador
	$(RM) $(OBJ) main
