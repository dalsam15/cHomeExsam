cc=gcc
cflags=-g -Wall 
cflags2= -lm

TARGET = main
all: $(clean);make  $(TARGET) 

$(TARGET): main.o board.o player.o
	$(cc) $(cflags) -o $(TARGET) $(cflags) main.o board.o player.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

board.o:
	$(CC) $(CFLAGS) -c -o board.o board.c

player.o:
	$(cc) $(CFLAGS) -c -o player.o player.c

$(clean):
	rm $(TARGET) *.o 

trash:
	rm $(TARGET) *.o

memCheck:
	valgrind --tool=memcheck --leak-check=yes ./main


