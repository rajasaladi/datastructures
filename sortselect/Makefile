INC = -I . -I ../inc
OBJDIR = obj
BINDIR = bin
LIBDIR = ../lib
OBJ = $(OBJDIR)/*.o
RM = rm -f
RMDIR = rm -rf
MKDIR = mkdir -p
CFLAGS = -c -g

vpath %.o $(OBJDIR)

.DEFAULT_GOAL := all

$(OBJDIR):
	$(MKDIR) $(OBJDIR)

$(BINDIR):
	$(MKDIR) $(BINDIR)

$(LIBDIR):
	$(MKDIR) $(LIBDIR)

bubblesort.o: $(OBJDIR) bubblesort.c ../inc/sort.h
	gcc $(INC) -o $(OBJDIR)/bubblesort.o $(CFLAGS) bubblesort.c

insertionsort.o: $(OBJDIR) insertionsort.c ../inc/sort.h
	gcc $(INC) -o $(OBJDIR)/insertionsort.o $(CFLAGS) insertionsort.c

heapsort.o: $(OBJDIR) heapsort.c ../inc/binheap.h ../inc/sort.h
	gcc $(INC) -o $(OBJDIR)/heapsort.o $(CFLAGS) heapsort.c

mergesort.o: $(OBJDIR) mergesort.c ../inc/sort.h
	gcc $(INC) -o $(OBJDIR)/mergesort.o $(CFLAGS) mergesort.c

quicksort.o: $(OBJDIR) quicksort.c ../inc/sort.h
	gcc $(INC) -o $(OBJDIR)/quicksort.o $(CFLAGS) quicksort.c

radixsort.o: $(OBJDIR) radixsort.c ../inc/sort.h
	gcc $(INC) -o $(OBJDIR)/radixsort.o $(CFLAGS) radixsort.c

libsort.a: $(LIBDIR) bubblesort.o insertionsort.o heapsort.o mergesort.o quicksort.o radixsort.o
	ar -cvq $(LIBDIR)/libsort.a $(OBJDIR)/bubblesort.o $(OBJDIR)/insertionsort.o $(OBJDIR)/heapsort.o $(OBJDIR)/mergesort.o $(OBJDIR)/quicksort.o $(OBJDIR)/radixsort.o

sort_test.o: $(OBJDIR) sort_test.c ../inc/sort.h
	gcc $(INC) -o $(OBJDIR)/sort_test.o $(CFLAGS) sort_test.c

kth_largest.o: $(OBJDIR) kth_largest.c ../inc/sort.h
	gcc $(INC) -o $(OBJDIR)/kth_largest.o $(CFLAGS) kth_largest.c

sort_test: $(BINDIR) sort_test.o bubblesort.o insertionsort.o heapsort.o mergesort.o quicksort.o radixsort.o
	gcc -o $(BINDIR)/sort_test $(OBJDIR)/sort_test.o $(OBJDIR)/bubblesort.o $(OBJDIR)/insertionsort.o $(OBJDIR)/heapsort.o $(OBJDIR)/mergesort.o $(OBJDIR)/quicksort.o $(OBJDIR)/radixsort.o -L$(LIBDIR) -lbinheap

kth_largest: $(BINDIR) kth_largest.o heapsort.o quicksort.o
	gcc -o $(BINDIR)/kth_largest $(OBJDIR)/kth_largest.o $(OBJDIR)/heapsort.o $(OBJDIR)/quicksort.o -L$(LIBDIR) -lbinheap

libs: libsort.a

all: libs sort_test kth_largest
	@echo "Build successful!!"

test: all
	@../scripts/run_tests.sh \
		"Sort Algorithms:$(BINDIR)/sort_test:test/input15.txt" \
		"Kth Largest (heap/quick select):$(BINDIR)/kth_largest:test/kth_input15.txt"

clean:
	$(RMDIR) $(OBJDIR)
	$(RMDIR) $(BINDIR)
	$(RM) $(LIBDIR)/libsort.a
	@echo "Clean!!"
