INC = -I . -I ../inc
INCDIR = ../inc
SRCDIR = .
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

htable.o: $(OBJDIR) $(SRCDIR)/htable.c $(INCDIR)/htable.h
	gcc $(INC) -o $(OBJDIR)/htable.o $(CFLAGS) $(SRCDIR)/htable.c

libhtable.a: $(LIBDIR) htable.o
	ar -cvq $(LIBDIR)/libhtable.a $(OBJDIR)/htable.o

htable_test.o: $(SRCDIR)/htable_test.c $(INCDIR)/htable.h
	gcc $(INC) -o $(OBJDIR)/htable_test.o $(CFLAGS) $(SRCDIR)/htable_test.c

frequent.o: $(SRCDIR)/frequent.c $(INCDIR)/htable.h
	gcc $(INC) -o $(OBJDIR)/frequent.o $(CFLAGS) $(SRCDIR)/frequent.c

frequent_sorted.o: $(SRCDIR)/frequent_sorted.c
	gcc $(INC) -o $(OBJDIR)/frequent_sorted.o $(CFLAGS) $(SRCDIR)/frequent_sorted.c

frequent: $(BINDIR) htable.o frequent.o
	gcc -o $(BINDIR)/frequent $(OBJDIR)/htable.o $(OBJDIR)/frequent.o

frequent_sorted: $(BINDIR) frequent_sorted.o
	gcc -o $(BINDIR)/frequent_sorted $(OBJDIR)/frequent_sorted.o

htable_test: $(BINDIR) htable.o htable_test.o
	gcc -o $(BINDIR)/htable_test $(OBJDIR)/htable*.o

libs: libhtable.a

all: libs htable_test frequent frequent_sorted
	@echo "Build successful!!"

clean:
	$(RMDIR) $(OBJDIR)
	$(RMDIR) $(BINDIR)
	$(RM) $(LIBDIR)/libhtable.a
	@echo "Clean!!"
