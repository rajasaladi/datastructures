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

queue.o: $(OBJDIR) queue.c ../inc/queue.h
	gcc $(INC) -o $(OBJDIR)/queue.o $(CFLAGS) queue.c

libqueue.a: $(LIBDIR) queue.o
	ar -cvq $(LIBDIR)/libqueue.a $(OBJDIR)/queue.o

queue_array.o: $(OBJDIR) queue_array.c ../inc/queue.h
	gcc $(INC) -o $(OBJDIR)/queue_array.o $(CFLAGS) queue_array.c

libqueue_array.a: $(LIBDIR) queue_array.o
	ar -cvq $(LIBDIR)/libqueue_array.a $(OBJDIR)/queue_array.o

queue_test.o: $(OBJDIR) queue_test.c ../inc/queue.h
	gcc $(INC) -o $(OBJDIR)/queue_test.o $(CFLAGS) queue_test.c

queue_test: $(BINDIR) queue.o queue_test.o
	gcc -o $(BINDIR)/queue_test $(OBJDIR)/queue.o $(OBJDIR)/queue_test.o

queue_test2: $(BINDIR) queue_array.o queue_test.o
	gcc -o $(BINDIR)/queue_test2 $(OBJDIR)/queue_array.o $(OBJDIR)/queue_test.o

libs: libqueue.a libqueue_array.a

all: libs queue_test queue_test2
	@echo "Build successful!!"

clean:
	$(RMDIR) $(OBJDIR)
	$(RMDIR) $(BINDIR)
	$(RM) $(LIBDIR)/libqueue*.a
	@echo "Clean!!"
