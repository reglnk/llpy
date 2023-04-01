# llpy
Low-level Python extensions

# Buiding example
```bash
gcc -shared -o llpy_swap.pyd -O2 llpy_swap.c -I/path/to/Python/include -L/path/to/Python/libs -lpython3xx
```

# Using
```py
import llpy_swap

a = 57.2
b = 12.3

print(a, b) # 57.2 12.3
llpy_swap.swap(a, b)
print(a, b) # 12.3 57.2

t1 = (2, "hello", "world")
t2 = ("hi", "world", 3.141593)

print(t1, t2) # (2, "hello", "world") ("hi", "world", 3.141593)
llpy_swap.swap(t1, t2)
print(t1, t2) # ("hi", "world", 3.141593) (2, "hello", "world")

l1 = list(t1)
l2 = list(t2)

print(l1, l2) # ("hi", "world", 3.141593) (2, "hello", "world")
llpy_swap.swap(l1, l2)
print(l1, l2) # (2, "hello", "world") ("hi", "world", 3.141593)
```
