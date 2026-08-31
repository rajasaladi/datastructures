RMDIR = rm -rf
LIBDIR = lib
SHELL := /bin/bash

# The order of directories must be maintained due to some of the dependencies
SUBDIRS := stack queue bst htable binheap sortselect trie disjset graph

.DEFAULT_GOAL := all

all:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir; \
	done

test:
	@fail=0; total_pass=0; total_fail=0; tmpfile=$$(mktemp); \
	for dir in $(SUBDIRS); do \
		echo "=== $$dir ==="; \
		$(MAKE) -C $$dir test 2>&1 | tee $$tmpfile; \
		status=$${PIPESTATUS[0]}; \
		[ $$status -ne 0 ] && fail=1; \
		line=$$(grep '^Results:' $$tmpfile | tail -1); \
		p=$$(echo "$$line" | awk '{print $$2}'); \
		f=$$(echo "$$line" | awk '{print $$4}'); \
		total_pass=$$((total_pass + $${p:-0})); \
		total_fail=$$((total_fail + $${f:-0})); \
		echo; \
	done; \
	rm -f $$tmpfile; \
	echo "==================================="; \
	echo "TOTAL: $$((total_pass + total_fail)) tests run, $$total_pass passed, $$total_fail failed"; \
	exit $$fail

clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	$(RMDIR) $(LIBDIR)

.PHONY: all test clean $(SUBDIRS)
