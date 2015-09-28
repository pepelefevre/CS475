CC = gcc
OBJS = timer.o
FLAGS = -fopenmp -O3
DEBUGFLAG = -DDEBUG
SEQFLAGS = -O3 -lm

EXEC = Merge_sort Merge_sort_debug Merge_sortNP Merge_sortP Merge_sortS NPDebug

all: $(EXEC)

Merge_sort: Merge_sort.c $(OBJS)
	$(CC) $(SEQFLAGS)  -o $@ $< $(OBJS)

Merge_sort_debug:Merge_sort.c $(OBJS)
	$(CC) $(SEQFLAGS) $(DEBUGFLAG)  -o $@ $< $(OBJS)

Merge_sortNP: Merge_sortNP.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS)

NPDebug: Merge_sortNP.c $(OBJS)
	$(CC) $(FLAGS) $(DEBUGFLAG)  -o $@ $< $(OBJS)

Merge_sortP: Merge_sortP.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS)

Merge_sortS: Merge_sortS.c $(OBJS)
	$(CC) $(FLAGS) -o $@ $< $(OBJS)

timer.o: timer.c
	$(CC) -O3 -o $@ -c $<

clean:
	rm -f $(OBJS) $(EXEC)
