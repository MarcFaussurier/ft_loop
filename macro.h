#ifndef MACRO_H
# define MACRO_H
/*
 * FOR_EACH
 */
# define CONCATENATE(arg1, arg2)   CONCATENATE1(arg1, arg2)
# define CONCATENATE1(arg1, arg2)  CONCATENATE2(arg1, arg2)
# define CONCATENATE2(arg1, arg2)  arg1##arg2
# define FOR_EACH_1(macro, x)         \
    macro(x)
# define FOR_EACH_2(macro, x, ...)    \
    macro(x);                        \
    FOR_EACH_1(macro, __VA_ARGS__);
# define FOR_EACH_3(macro, x, ...)    \
    macro(x);                        \
    FOR_EACH_2(macro, __VA_ARGS__);
# define FOR_EACH_4(macro, x, ...)    \
    macro(x);                        \
    FOR_EACH_3(macro,  __VA_ARGS__);
# define FOR_EACH_5(macro, x, ...)    \
    macro(x);                        \
    FOR_EACH_4(macro,  __VA_ARGS__);
# define FOR_EACH_6(macro, x, ...)    \
  macro(x);                          \
  FOR_EACH_5(macro,  __VA_ARGS__);
# define FOR_EACH_7(macro, x, ...)    \
    macro(x);                        \
    FOR_EACH_6(macro,  __VA_ARGS__);
# define FOR_EACH_8(macro, x, ...)    \
    macro(x);                        \
    FOR_EACH_7(macro,  __VA_ARGS__);
# define FOR_EACH_NARG(...) FOR_EACH_NARG_(__VA_ARGS__, FOR_EACH_RSEQ_N())
# define FOR_EACH_NARG_(...) FOR_EACH_ARG_N(__VA_ARGS__) 
# define FOR_EACH_ARG_N(_1, _2, _3, _4, _5, _6, _7, _8, N, ...) N 
# define FOR_EACH_RSEQ_N() 8, 7, 6, 5, 4, 3, 2, 1, 0
# define FOR_EACH_(N, macro, ...) CONCATENATE(FOR_EACH_, N)(macro, __VA_ARGS__)
# define FOR_EACH(macro, ...) FOR_EACH_(FOR_EACH_NARG(__VA_ARGS__), macro, __VA_ARGS__)
#endif
