#include "ft_loop.h"
#include <stdio.h>

int main()
{
	ft_loop_create(loop, 0);
	
	int y = 0;
	int z = 0;
	loop.write(1, "42\n", 3, ^ (ssize_t i)
	{_(y, z)
		y += 1;
		z -= 1;
		loop.write(1, "21\n", 3, ^ (ssize_t i)
		{_(y)
			y += 1;
			printf("i=%i\n", y);
		});
		printf("okok\n");
	});
	loop.run();
	return (0);
}
