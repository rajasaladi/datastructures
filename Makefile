RMDIR = rm -rf
LIBDIR = lib

# The order of directories must be maintained due to some of the dependencies
SUBDIRS := stack queue bst htable binheap trie disjset graph

.DEFAULT_GOAL := all

all:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(RMDIR) $(LIBDIR)

.PHONY: all clean $(SUBDIRS)
