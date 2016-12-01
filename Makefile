cc=gcc
cflags=-g -Wall 
cflags2= -lm

TARGET = main
all: $(TARGET)

$(TARGET): main.o board.o
	$(cc) $(cflags) -o $(TARGET) $(cflags) main.o board.o

main.o: main.c
	$(CC) $(CFLAGS) -c -o main.o main.c

board.o:
	$(CC) $(CFLAGS) -c -o board.o board.c

clean:
	rm $(TARGET) *.o 


memCheck:
	valgrind --tool=memcheck --leak-check=yes ./main


