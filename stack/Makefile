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

stack.o: $(OBJDIR) stack.c ../inc/stack.h
	gcc $(INC) -o $(OBJDIR)/stack.o $(CFLAGS) stack.c

libstack.a: $(LIBDIR) stack.o
	ar -cvq $(LIBDIR)/libstack.a $(OBJDIR)/stack.o

stack_test.o: $(OBJDIR) stack_test.c ../inc/stack.h
	gcc $(INC) -o $(OBJDIR)/stack_test.o $(CFLAGS) stack_test.c

stack_test: $(BINDIR) stack.o stack_test.o
	gcc -o $(BINDIR)/stack_test $(OBJDIR)/stack.o $(OBJDIR)/stack_test.o



stack_array.o: $(OBJDIR) stack_array.c ../inc/stack.h
	gcc $(INC) -o $(OBJDIR)/stack_array.o $(CFLAGS) stack_array.c

libstack_array.a: $(LIBDIR) stack_array.o
	ar -cvq $(LIBDIR)/libstack_array.a $(OBJDIR)/stack_array.o

stack_array_test: $(BINDIR) stack_array.o stack_test.o
	gcc -o $(BINDIR)/stack_array_test $(OBJDIR)/stack_array.o $(OBJDIR)/stack_test.o




stack2.o: $(OBJDIR) stack2.c ../inc/stack2.h
	gcc $(INC) -o $(OBJDIR)/stack2.o $(CFLAGS) stack2.c

libstack2.a: $(LIBDIR) stack2.o
	ar -cvq $(LIBDIR)/libstack2.a $(OBJDIR)/stack2.o

stack2_test.o: $(OBJDIR) stack2_test.c ../inc/stack.h
	gcc $(INC) -o $(OBJDIR)/stack2_test.o $(CFLAGS) stack2_test.c

stack2_test: $(BINDIR) stack.o stack2_test.o
	gcc -o $(BINDIR)/stack2_test $(OBJDIR)/stack2.o $(OBJDIR)/stack2_test.o




check_paranthesis.o: $(OBJDIR) check_paranthesis.c ../inc/stack.h
	gcc $(INC) -o $(OBJDIR)/check_paranthesis.o $(CFLAGS) check_paranthesis.c

check_paranthesis: $(BINDIR) stack.o check_paranthesis.o
	gcc -o $(BINDIR)/check_paranthesis $(OBJDIR)/stack.o $(OBJDIR)/check_paranthesis.o

check_paranthesis2: $(BINDIR) stack_array.o check_paranthesis.o
	gcc -o $(BINDIR)/check_paranthesis2 $(OBJDIR)/stack_array.o $(OBJDIR)/check_paranthesis.o

libs: libstack.a libstack2.a libstack_array.a

all: libs stack_test stack2_test stack_array_test check_paranthesis check_paranthesis2
	@echo "Build successful!!"

clean:
	$(RMDIR) $(OBJDIR)
	$(RMDIR) $(BINDIR)
	$(RM) $(LIBDIR)/libstack*.a
	@echo "Clean!!"
