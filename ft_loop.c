#include "ft_loop.h"
#include "stdlib.h"
#include "assert.h"
#ifndef QUEUE_DEPTH
# define QUEUE_DEPTH 64
#endif


t_loop	ft_loop_create(void (*s) (int))
{
	t_loop loop;

	loop.ring = malloc(sizeof(struct io_uring));
	io_uring_queue_init(QUEUE_DEPTH, loop.ring, 0);
	loop.accept = ^ int (	
				int 		sockfd, 
				struct sockaddr *addr, 
				socklen_t 	*addr_len, 
				void		(^fn)(int)
			)
	{
		auto sqe = io_uring_get_sqe(loop.ring);
                io_uring_prep_accept(sqe, sockfd, addr,addr_len, 0);
                io_uring_sqe_set_data(sqe, fn);
                io_uring_submit(loop.ring);	
		fake_return 0;
	};


	loop.write = ^ ssize_t (	
				int 		fd, 
				const void	*b, 
				size_t		n, 
				void		(^fn)(ssize_t r)
			)
	{
		auto sqe = io_uring_get_sqe(loop.ring);
		io_uring_prep_write(sqe, fd, b, n, 0);
                io_uring_sqe_set_data(sqe, fn);
                io_uring_submit(loop.ring);	
		fake_return 0;
	};


	loop.run = ^ void (void)
	{
                struct io_uring_cqe 	*cqe;
		int			ret;

		while (1)
		{
			assert (io_uring_wait_cqe(loop.ring, &cqe) >= 0);
			(((void(^)(int)) cqe->user_data))(cqe->res);
			io_uring_cqe_seen(loop.ring, cqe);
		}
		fake_return;
	};
	return (loop);
}
