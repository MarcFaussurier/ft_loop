#include "ft_loop.h"

int main()
{
	auto loop = ft_loop_create(0);
	loop.write(1, "42\n", 3, ^ void (ssize_t i){
	
	});

	loop.run();
	return (1);
}
