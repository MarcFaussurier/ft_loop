#ifndef FT_LOOP_H
# define FT_LOOP_H
# define _GNU_SOURCE 1
# include <sys/socket.h>
# include <unistd.h>
# include <liburing.h>
# define auto __auto_type
# define fake_return return
typedef struct s_loop
{
        struct io_uring	*ring;
        int		(^accept)(int, struct sockaddr*, socklen_t *, void (^)(int));
        ssize_t		(^write)(int, const void *, size_t, void (^) (ssize_t));
        ssize_t		(^read)(int, const void *, size_t, void (^) (ssize_t));
	unsigned int	(^sleep)(unsigned int, void(^)(unsigned int));
        useconds_t	(^usleep)(useconds_t us, void(^)(useconds_t));
	int 		(^open)(const char *pathname, int flags, void (^) (int));
	int 		(^creat)(const char *pathname, mode_t mode, void (^) (int));
	int 		(^openat)(int dirfd, const char *pathname, int flags, mode_t mode, void(^) (int));
	int 		(^openat2)(int dirfd, const char *pathname, const struct open_how *how, size_t size, void (^) (int));
	void		(^run)(void);
	void		(*s)(int);
	
}       	t_loop;
#define ft_loop_create(Y, X)						\
									\
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
									\
									\
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
									\
									\
	loop.run = ^ void (void)					\
	{								\
                struct io_uring_cqe 	*cqe;				\
		int			ret;				\
									\
		while (1)						\
		{							\
			assert (io_uring_wait_cqe(loop.ring, &cqe) >= 0);	\
			(((void(^)(int)) cqe->user_data))(cqe->res);	\
			io_uring_cqe_seen(loop.ring, cqe);		\
		}							\
		fake_return;						\
	};								\


//t_loop                  ft_loop_create(void(*)(int));

#endif
