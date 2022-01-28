#include "ft_loop.h"
#include <stdio.h>

macro rule 
(
 	<name is_name(name)>
		<x !strlen(x) || sisspace(x)>
	=
		<x !strlen(x) || sisspace(x)>
	ft_loop_create(<args countargs(args) <= 1>)
)
{
	return
	(
		string 
		(
			"ft_loop_create(<name>, ",
			!countargs(args) ? "0" : args, 
			")"
		)
	);
}

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
	
	___:
	loop.run();
	return (0);
}
