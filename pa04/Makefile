GCCFLAGS=-Wall -Wshadow -g

all: echo cat grep

echo: echo-lite.c
	gcc $(GCCFLAGS) echo-lite.c -o echo-lite

cat: cat-lite.c
	gcc $(GCCFLAGS) cat-lite.c -o cat-lite

grep: grep-lite.c
	gcc $(GCCFLAGS) grep-lite.c -o grep-lite

clean:
	rm echo-lite cat-lite grep-lite
