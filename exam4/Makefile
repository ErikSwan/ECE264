# compiler & options
CC=gcc
CCFLAGS=-Wall -Wshadow -g

# source files & binaries
HIDE_BIN=hidestrings
HIDE_SRC=$(HIDE_BIN).c
REST_BIN=restorestrings
REST_SRC=$(REST_BIN).c
LIST_BIN=listmain
LIST_SRC=listfunctions.c $(LIST_BIN).c

# usage message
help:
	@echo 'Usage:'
	@echo '	make $(HIDE_BIN)	-or-'
	@echo '	make $(REST_BIN)	-or-'
	@echo '	make $(LIST_BIN)'
	@echo ''
	@echo 'To build either part of the exam.'

# compile directives
$(HIDE_BIN): $(HIDE_SRC)
	$(CC) $(CCFLAGS) $^ -o $@

$(REST_BIN): $(REST_SRC)
	$(CC) $(CCFLAGS) $^ -o $@

$(LIST_BIN): $(LIST_SRC)
	$(CC) $(CCFLAGS) $^ -o $@

# clean up
clean:
	rm -rf $(HIDE_BIN) $(REST_BIN) $(LIST_BIN)
