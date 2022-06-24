# ft_loop
[WIP] liburing based event loop using clang blocks features

# compilation

- tested under linux 5.15 (Alpine linux 3.15)
- tested under clang 12.0.1 (target: x86_64-alpine-linux-musl)

compile main.c using :
``` make ``` 

main.ç is an idea of a new 'await' keyword for C to use kernel async ability without nested lambda functions, that can be implemented using preprocessing only. The ft_cedille preprocessor that should preprocess this new keyword it is still a work in progress.


TODOS:
- [X] ft_loop mvp using clang blocks
- [X] ft_cedille mvp 
- [ ] await keyword 
- [ ] more awaitable syscalls
- [ ] http server
- [ ] pgpool
- [ ] clang blocks implementation using ft_cedille 
