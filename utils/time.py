import time
from functools import wraps

# 执行时间装饰器
def fn_timer(funtion):
  @wraps(funtion)
  def function_timer(*args, **kwargs):
    t0 = time.time()
    result = funtion(*args, ** kwargs)
    t1 = time.time()
    print('Running %s: %.3f seconds' % (funtion.__name__, t1-t0))
    return result
  return function_timer