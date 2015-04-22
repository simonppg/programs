CFLAGS = -g
OBJ=ia.o hist.o

all: hist

hist: $(OBJ)
	$(CC) $(CFLAGS) -o hist $(OBJ)

hist.o:ia.h hist.c

ia.o:ia.h ia.c

run: hist data
	./hist data
