all:
	clang -g -O3  main.c -fblocks -lBlocksRuntime -luring
clean:
	rm a.out
