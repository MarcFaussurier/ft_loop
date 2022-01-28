#include "ft_loop.h"

#include "stdlib.h"
#include "assert.h"
#ifndef QUEUE_DEPTH
# define QUEUE_DEPTH 64
#endif




int main()
{
	ft_loop_create(loop, 0);
	loop.write(1, "42\n", 3, ^ void (ssize_t i){

		loop.write(1, "21\n", 3, ^ void (ssize_t i){

			printf("okok2\n");
		});
		printf("okok\n");
	});
	loop.run();
	return (0);
}
