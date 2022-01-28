#include "ft_loop.h"
#include <stdio.h>

int main()
{
	auto loop = ft_loop_create();
	auto y = 0;
	auto z = 0;

	auto i = await loop.write(1, "42\n", 3); // detect for & and = amd _(...) the vars
	y += 1;
	z -= 1;
	i = await loop.write(1, "21\n", 3);
	y += 1;
	printf("i=%lli\n", y);
	printf("okok\n");
	___
	loop.run();
	return (0);
}
