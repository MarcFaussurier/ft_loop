
#ifndef MACRO_DEPTH
# define MACRO_DEPTH 42
#endif


a fn (name, args)
{
	return cat 
	(
		"ft_loop_create(, ",
		name,
		!countargs(args) ? "0" : args, 
		")"
	);
}

int main(int ac, char **av)
{
	int fd;

	fd = open(av[1]);
	tokens = [];

	while (1)
	{
		token = get_token(source);
		if (!token)
			return ;
		tokens[] = token;
		if (tokens.length > 4 && tokens[len - x] .... )
			a fn (token[len - x]) ....
		
	}
}
