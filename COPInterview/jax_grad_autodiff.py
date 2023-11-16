import math

def add(x, y, dx=0, dy=0):
  return x + y, dx + dy

def mul(x, y, dx=0, dy=0):
  return x * y, y * dx + dy * x

def sin(x):
  return math.sin(x), math.cos(x)

def neg(x, dx):
  return -x, -dx

def f_grad(x, dx):
  a, da = sin(x)
  b, db = mul(a, 2, da, 0) # the grad of constant is 0 so the dy for mul is 0.
  c, dc = neg(b, db)
  d, dd = add(c, x, dc, dx)
  return d, dd

print(f_grad(3, 1))
