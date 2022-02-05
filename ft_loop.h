#ifndef FT_LOOP_H
# define FT_LOOP_H
# define _GNU_SOURCE 1
# include <sys/socket.h>
# include <unistd.h>
# include <liburing.h>
# include <stdlib.h>
# include <assert.h>
# include "macro.h"
# ifndef QUEUE_DEPTH
#  define QUEUE_DEPTH 64
# endif
# define auto __auto_type
# define fake_return return
# define capture(X) typeof(X) X = X;
# define _(...) FOR_EACH(capture, __VA_ARGS__)
typedef struct s_loop
{
        struct io_uring	*ring;
        int		(^accept)(int, struct sockaddr*, socklen_t *, void (^)(int));
        ssize_t		(^write)(int, const void *, size_t,  void (^) (ssize_t));
        ssize_t		(^read)(int, const void *, size_t,  void (^) (ssize_t));
	unsigned int	(^sleep)(unsigned int,  void(^)(unsigned int));
        useconds_t	(^usleep)(useconds_t us,  void(^)(useconds_t));
	int 		(^open)(const char *pathname, int flags, void (^) (int));
	int 		(^creat)(const char *pathname, mode_t mode,  void (^) (int));
	int 		(^openat)(int dirfd, const char *pathname, int flags, mode_t mode,		void(^) (int));
	int 		(^openat2)(int dirfd, const char *pathname, const struct open_how *how, size_t size,  void (^) (int));
	void		(^run)(void);
	void		(*s)(int);
	
}       	t_loop;
#define ft_loop_create(Y, X)						\
	t_loop Y;							\
									\
	loop.s = X;							\
	loop.ring = malloc(sizeof(struct io_uring));			\
	io_uring_queue_init(QUEUE_DEPTH, loop.ring, 0);			\
	loop.accept = ^ int (						\
				int 		sockfd, 		\
				struct sockaddr *addr, 			\
				socklen_t 	*addr_len, 		\
				void		(^fn)(int)		\
			)						\
	{								\
		auto sqe = io_uring_get_sqe(loop.ring);			\
                io_uring_prep_accept(sqe, sockfd, addr,addr_len, 0);	\
                io_uring_sqe_set_data(sqe, fn);				\
                io_uring_submit(loop.ring);				\
		fake_return 0;						\
	};								\
	loop.write = ^ ssize_t (					\
				int 		fd, 			\
				const void	*b, 			\
				size_t		n, 			\
				void		(^fn)(ssize_t r)	\
			)						\
	{								\
		auto sqe = io_uring_get_sqe(loop.ring);			\
		io_uring_prep_write(sqe, fd, b, n, 0);			\
                io_uring_sqe_set_data(sqe, fn);				\
                io_uring_submit(loop.ring);				\
		fake_return 0;						\
	};								\
	loop.run = ^ void (void)					\
	{								\
                struct io_uring_cqe 	*cqe;				\
		int			ret;				\
									\
		while (1)						\
		{							\
			assert (io_uring_wait_cqe(loop.ring, &cqe) >= 0);\
			(((void(^)(int)) cqe->user_data))(cqe->res);	\
			io_uring_cqe_seen(loop.ring, cqe);		\
		}							\
		fake_return;						\
	};								\


#import "ft_cedille/ft_cedille_spec/ç"
#include "stdio.h"
#include "string.h"
#include <ctype.h>
#define semicolon ';'

macro int 	m_state_test = 0;
macro int	m_brace_level = 0;
macro int	m_bracket_level = 0;
macro int	m_parenthesis_level = 0;

macro int f(int x)
{
	return (x);
}

/*
	<continue while ; succeed on ;>
*/

// test

macro rule
(
	<s[x + y] == "Hello "[y]				;	y == 5;>
		<(test2[y] = s[x + y]) && y < 5		;	s[x + y] == "!"[0]	&& !(test2[y] = 0);>
)
{
	m_state_test += 1;
	return(cat("Good night dear ", test2, "."));
}




macro char	*trim(char *str)
{
	int	i;
	char	*o;

	while (*str && isspace(*str))
	{
		str += 1;
	}
	i = 0;
	while (str[i] && !isspace(str[i]))
	{
		i += 1;
	}
	asprintf(&o, "%.*s", i, str);
	return (o);
}

macro char 	*lastword(char *str)
{
	char	*lastspace;
	int		i;

	i = 0;
	while (str[i])
			i += 1;
	while ((i - 1) && isspace(str[i - 1]))
		i -= 1;

	while ((i - 1) && !isspace(str[i - 1]))
		i -= 1;
	return (str + i);

}

#include <stdio.h>
/* TODO: deeper parse - f(await g(...)[await h(...) + await i(...)]) */
#define await
macro		rule
(
	<
		(prev[0] = s[x])
		&&
		(
			s[x] == '{'
			||
			s[x] == semicolon
		)
		;
		(
			!(prev[1] = 0)
		)
	;>
	<
		(assignation[y] = s[x + y])
		&& 
		(
			s[x + y] != '{' 
			&& 
			s[x + y] != semicolon)
		;
		(s[x + y] == '=' || ((s[x + y] == 'a' && s[x + y + 1] == 'w') && (--x || 1)))
		&&
		!(assignation[y] = 0)
	;>
	<x
	; 
	!isspace(s[x + y]) && (--x || 1);>
	<s[x + y] == "await"[y]							; 	y == 4;>
		<(name[y] = s[x + y]) && y < 12 && s[x + y]	
		;	
		s[x + y] == '(' 
		&&
		!(
			(name[y] = 0)
			||
			(m_parenthesis_level = 0)
		)
		;>
				<(args[y] = s[x + y]) 
				&&
				(((s[x + y] == '(')
				&&
				++m_parenthesis_level) || 1)
				;
					(
						s[x + y] == ')'
						&&
						!(m_parenthesis_level < 0)
					)
					&& 
					!(
						(args[y] = 0) 
						||
						(m_brace_level = 0)
					)
				;>
					<(body[y] = s[x + y])
						&&
						(
							(
								(s[x + y] == '{' && ++m_brace_level)
								|| 		
								(s[x + y] == '}' && (m_brace_level-- || 1))
							) 
							|| 1
						)
					;	
						(s[x + y] == '}' && m_brace_level < 0)
						&&
						!(body[y] = 0)
					;>
)
{
	char	*o;


	
	asprintf(&o, "%s\n%s(%s%s ^(typeof(%s(%s%s 0)) %s) { %s });\n}",
		cat (prev), cat(name), cat(args), strlen(cat(args)) ? "," : "", cat(name), cat(args), strlen(cat(args)) ? "," : "",  lastword(cat(assignation)), cat(body));

	return (o);
}



int 	bar( int p, void (^ptr)(int k) )
{
	ptr(21);
	return (0);
}





int 	foo( int p, char c, void (^ptr)(int k) )
{
	ptr(42);
	return (0);
}
#endif
