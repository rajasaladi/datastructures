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

graph.o: $(OBJDIR) graph.c ../inc/graph.h
	gcc $(INC) -o $(OBJDIR)/graph.o $(CFLAGS) graph.c

gheap.o: $(OBJDIR) gheap.c ./gheap.h
	gcc $(INC) -o $(OBJDIR)/gheap.o $(CFLAGS) gheap.c

libgraph.a: $(LIBDIR) graph.o gheap.o
	ar -cvq $(LIBDIR)/libgraph.a $(OBJDIR)/graph.o $(OBJDIR)/gheap.o

graph_test.o: $(OBJDIR) graph_test.c ../inc/graph.h
	gcc $(INC) -o $(OBJDIR)/graph_test.o $(CFLAGS) graph_test.c

graph_test: $(BINDIR) graph.o graph_test.o gheap.o
	gcc -o $(BINDIR)/graph_test $(OBJDIR)/graph.o $(OBJDIR)/gheap.o $(OBJDIR)/graph_test.o -L$(LIBDIR) -lqueue -lstack -ldisjset

libs: libgraph.a

all: libs graph_test
	@echo "Build successful!!"

clean:
	$(RMDIR) $(OBJDIR)
	$(RMDIR) $(BINDIR)
	$(RM) $(LIBDIR)/libgraph.a
	@echo "Clean!!"
