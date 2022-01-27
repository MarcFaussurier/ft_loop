all:
	clang -g  main.c ft_loop.c -fblocks -lBlocksRuntime -luring
clean:
	rm a.out
