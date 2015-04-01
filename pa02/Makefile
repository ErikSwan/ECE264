# you don't need the next line, you can just put the flags in the gcc line, but this has
# advantages when you get more complex makefiles
GCCFLAGS=-Wall -Wshadow -g

# This simple makefile just compiles everything at once, but it is very easy to write
# makefiles that only compile the C files that changed and then re-links them together
# Use web search to learn more if you have a complex project where this saves time.
all:
	gcc $(GCCFLAGS) pa02.c answer02.c -o pa02
