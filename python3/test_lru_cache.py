import functools 
import time 
'''
Demo codes to show the ablity of lru_cache 
lru_cache is really good for dynamic programming. 
'''
__author__ = "Hanzhou Tang"
__email__  = "hanzhoutang@gmail.com"

def timeit(times = 1):
    timeit.total = 0 
    def decorator(f):
        def g(*args,**kwargs):
            start = time.time()
            for _ in range(times):
                ret = f(*args,**kwargs)
            end = time.time()
            timeit.total += (end-start)/times
            return ret 
        return g 
    return decorator



@timeit()
#@functools.lru_cache(None)
def fib(n):
    if n == 0:
        return 1 
    elif n == 1:
        return 1 
    return fib(n-1) + fib(n-2)

print(fib(25))
print("time {}".format(timeit.total))


    

    