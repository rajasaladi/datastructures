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

disjset.o: $(OBJDIR) disjset.c ../inc/disjset.h
	gcc $(INC) -o $(OBJDIR)/disjset.o $(CFLAGS) disjset.c

libdisjset.a: $(LIBDIR) disjset.o
	ar -cvq $(LIBDIR)/libdisjset.a $(OBJDIR)/disjset.o

disjset_test.o: $(OBJDIR) disjset_test.c ../inc/disjset.h
	gcc $(INC) -o $(OBJDIR)/disjset_test.o $(CFLAGS) disjset_test.c

disjset_test: $(BINDIR) disjset.o disjset_test.o
	gcc -o $(BINDIR)/disjset_test $(OBJDIR)/disjset.o $(OBJDIR)/disjset_test.o

libs: libdisjset.a

all: libs disjset_test
	@echo "Build successful!!"

clean:
	$(RMDIR) $(OBJDIR)
	$(RMDIR) $(BINDIR)
	$(RM) $(LIBDIR)/libdisjset*.a
	@echo "Clean!!"
