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

bst.o: $(OBJDIR) bst.c ../inc/bst.h
	gcc $(INC) -o $(OBJDIR)/bst.o $(CFLAGS) bst.c

avl.o: $(OBJDIR) avl.c ../inc/avl.h
	gcc $(INC) -o $(OBJDIR)/avl.o $(CFLAGS) avl.c

libbst.a: $(LIBDIR) bst.o
	ar -cvq $(LIBDIR)/libbst.a $(OBJDIR)/bst.o

libavl.a: $(LIBDIR) avl.o
	ar -cvq $(LIBDIR)/libavl.a $(OBJDIR)/avl.o

bst_test.o: $(OBJDIR) bst_test.c ../inc/bst.h
	gcc $(INC) -o $(OBJDIR)/bst_test.o $(CFLAGS) bst_test.c

avl_test.o: $(OBJDIR) avl_test.c ../inc/avl.h
	gcc $(INC) -o $(OBJDIR)/avl_test.o $(CFLAGS) avl_test.c

bst_test: $(BINDIR) bst.o bst_test.o
	gcc -o $(BINDIR)/bst_test $(OBJDIR)/bst.o $(OBJDIR)/bst_test.o -L$(LIBDIR) -lqueue -lstack

bst_test2: $(BINDIR) bst.o bst_test.o
	gcc -o $(BINDIR)/bst_test2 $(OBJDIR)/bst.o $(OBJDIR)/bst_test.o -L$(LIBDIR) -lqueue_array -lstack_array

avl_test: $(BINDIR) avl.o avl_test.o
	gcc -o $(BINDIR)/avl_test $(OBJDIR)/avl.o $(OBJDIR)/avl_test.o -L$(LIBDIR) -lqueue -lstack

avl_test2: $(BINDIR) avl.o avl_test.o
	gcc -o $(BINDIR)/avl_test2 $(OBJDIR)/avl.o $(OBJDIR)/avl_test.o -L$(LIBDIR) -lqueue_array -lstack_array

libs: libbst.a libavl.a

all: libs bst_test bst_test2 avl_test avl_test2
	@echo "Build successful!!"

clean:
	$(RMDIR) $(OBJDIR)
	$(RMDIR) $(BINDIR)
	$(RM) $(LIBDIR)/libbst.a
	$(RM) $(LIBDIR)/libavl.a
	@echo "Clean!!"
