all:
	clang -g -O3  main.c ft_loop.c -fblocks -lBlocksRuntime -luring
clean:
	rm a.out
