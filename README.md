# llpy
Low-level Python extensions. DON'T USE IN PRODUCTION!11!!!

# Buiding example
```bash
gcc -shared -o llpy_util.pyd -O2 llpy_swap.c -I/path/to/Python/include -L/path/to/Python/libs -lpython3xx
```

# Usage examples
```py
import llpy

a = 57.2
b = 12.3

print(a, b) # 57.2 12.3
llpy.swap(a, b)
print(a, b) # 12.3 57.2

t1 = (2, "hello", "world")
t2 = ("hi", "world", 3.141593)

print(t1, t2) # (2, "hello", "world") ("hi", "world", 3.141593)
llpy.swap(t1, t2)
print(t1, t2) # ("hi", "world", 3.141593) (2, "hello", "world")

l1 = list(t1)[1:]
l2 = list(t2)[:-1]

print(l1, l2) # ["world", 3.141593] [2, "hello"]
llpy.swap(l1, l2)
print(l1, l2) # [2, "hello"] ["world", 3.141593]
```
```py
import llpy

my_immutable_tuples = {
    "23 45 678": (23, 45, 678),
    "hello world": ("hello world", ),
    "pi": (3.141592535897932384, 6.283185)
}

refp = llpy.ref(my_immutable_tuples["pi"])

def somefunc(r, mul):
    tup = tuple([n * mul for n in r.value])
    r.value = tup

for i in range(8):
    somefunc(refp, 1.5)
    print(my_immutable_tuples["pi"])
```