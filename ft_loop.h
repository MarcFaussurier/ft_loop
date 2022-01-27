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
}       	t_loop;


t_loop                  ft_loop_create(void(*)(int));

#endif
