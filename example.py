import llpy_swap

a = 57.2
b = 12.3

print(a, b) # 57.2 12.3
llpy_swap.swap(a, b)
print(a, b) # 12.3 57.2

print()

t1 = (2, "hello", "world")
t2 = ("hi", "world", 3.141593)

print(t1, t2) # (2, "hello", "world") ("hi", "world", 3.141593)
llpy_swap.swap(t1, t2)
print(t1, t2) # ("hi", "world", 3.141593) (2, "hello", "world")

print()

l1 = list(t1)
l2 = list(t2)

print(l1, l2) # ("hi", "world", 3.141593) (2, "hello", "world")
llpy_swap.swap(l1, l2)
print(l1, l2) # (2, "hello", "world") ("hi", "world", 3.141593)

print()

class Some:
    def __init__(self):
        self.somevar = 12.23;
    def somefunc(self):
        return "Some : " + str(self.somevar)

class Some2:
    def __init__(self):
        self.somevar = 24.23;
    def somefunc(self):
        return "Some2 : " + str(self.somevar)

sa = Some();
sb = Some2();

saf = sa.somefunc
sbf = sb.somefunc

print(saf(), sbf()) # Some: 12.23 Some2: 24.23
llpy_swap.swap(saf, sbf);
print(saf(), sbf()) # Some2: 24.23 Some: 12.23