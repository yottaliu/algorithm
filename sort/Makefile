CC 				= gcc
CFLAGS 			=

TEST_SORT 		= $(shell bash sel.sh)
ALL_SORT 		= $(shell find . -name "*_sort.c")

.PHONY: all compare test clean

all: clean compare test

compare:
	$(CC) $(CFLAGS) -o $@ $(ALL_SORT) compare.c

test:
	$(CC) $(CFLAGS) -o $@ $(TEST_SORT) test.c

clean:
	rm -f compare test
