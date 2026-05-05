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

trie.o: $(OBJDIR) trie.c ../inc/trie.h
	gcc $(INC) -o $(OBJDIR)/trie.o $(CFLAGS) trie.c

libtrie.a: $(LIBDIR) trie.o
	ar -cvq $(LIBDIR)/libtrie.a $(OBJDIR)/trie.o

trie_test.o: $(OBJDIR) trie_test.c ../inc/trie.h
	gcc $(INC) -o $(OBJDIR)/trie_test.o $(CFLAGS) trie_test.c

trie_test: $(BINDIR) trie.o trie_test.o
	gcc -o $(BINDIR)/trie_test $(OBJDIR)/trie.o $(OBJDIR)/trie_test.o

libs: libtrie.a

all: libs trie_test
	@echo "Build successful!!"

clean:
	$(RMDIR) $(OBJDIR)
	$(RMDIR) $(BINDIR)
	$(RM) $(LIBDIR)/libtrie.a
	@echo "Clean!!"
