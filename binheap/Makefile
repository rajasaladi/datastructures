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

binheap.o: $(OBJDIR) binheap.c ../inc/binheap.h
	gcc $(INC) -o $(OBJDIR)/binheap.o $(CFLAGS) binheap.c

libbinheap.a: $(LIBDIR) binheap.o
	ar -cvq $(LIBDIR)/libbinheap.a $(OBJDIR)/binheap.o

binheap_test.o: $(OBJDIR) binheap_test.c ../inc/binheap.h
	gcc $(INC) -o $(OBJDIR)/binheap_test.o $(CFLAGS) binheap_test.c

binheap_test: $(BINDIR) binheap.o binheap_test.o
	gcc -o $(BINDIR)/binheap_test $(OBJDIR)/binheap*.o

libs: libbinheap.a

all: libs binheap_test
	@echo "Build successful!!"

clean:
	$(RMDIR) $(OBJDIR)
	$(RMDIR) $(BINDIR)
	$(RM) $(LIBDIR)/libbinheap.a
	@echo "Clean!!"
