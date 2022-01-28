#include "ft_loop.h"
#include <stdio.h>

/* ft_loop_create */
macro rule 
(
 	<name isname(name)>
		<x !strlen(x) || isspaces(x)>
	=
		<x !strlen(x) || isspaces(x)>
	ft_loop_create(<args countargs(args) <= 1>)
)
{
	return cat 
	(
		"ft_loop_create(, ",
		name,
		!countargs(args) ? "0" : args, 
		")"
	);
}
/* await */
macro rule
(
	{
	<before !strlen(before) || isend(before, ";")>
 		<type>
 		<name 	!strlen(name) 	|| isname(name)>
			<x !strlen(x) 	|| isspace(x)>
 		<op 	!strlen(op) 	|| !strcmp(op, "=")>
			<x !strlen(x) 	|| isspace(x)>
		await
		<fn>(<args>);
	<after>
	}
)
{
	return cat
	(
		before,
		fn,"(",	args,", ^ ",
			"(",
				"typeof(",fn,	"(",args, ", 0))",
				!strlen(name) ? "_ANONYMOUS" : name,
			")",
			"{",
				after,
			"}",
		");"
	);
}

int main()
{
	auto loop = ft_loop_create();
	{
		auto y = 0;
		auto z = 0;
		auto i = await loop.write(1, "42\n", 3); // detect = and & labels.... 
		printf("okok\n");
		y += 1;
		z -= 1;
		i = await loop.write(1, "21\n", 3);
		y += 1;
		printf("i=%lli\n", y);
	}
	loop.run();
	return (0);
}
