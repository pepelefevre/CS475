
CC = gcc
OBJS = timer.o
FLAGS = -O3 -fopenmp
SEQFLAGS = -O3

EXEC = knapSeq knap knapBSeq knapB knapB2

all: $(EXEC)

knapSeq: knap.c timer.o
	$(CC) $(SEQFLAGS) -o knapSeq knap.c $(OBJS) 

knap: knap.c timer.o
	$(CC)  $(FLAGS) -o $@ knap.c $(OBJS) 

knapB: knapB.c timer.o
	$(CC)  $(FLAGS) -o $@ knapB.c $(OBJS) 

knapBSeq: knapB.c timer.o
	$(CC)  $(SEQFLAGS) -o $@ knapB.c $(OBJS) 

knapB2: knapB2.c timer.o
	$(CC)  $(FLAGS)  -o $@ knapB2.c $(OBJS) 

timer.o: timer.c
	$(CC) -o $@ -c timer.c

clean:
	rm -f $(EXEC) $(OBJS)
