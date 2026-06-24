

import numpy as np

def f(x):
    return np.exp(-x**2)

def trapezoidal_rule(func, a, b, n):
    h = (b - a) / n
    sum = func(a) + func(b)

    for i in range(1, n):
        sum += 2 * func(a + i * h)

    return (h / 2) * sum


for a in range(1, 21):
    result = trapezoidal_rule(f, -a, a, 1000)
    print(f"For a={a}, integral value is approximately {result} and we know that sqrt(pi) is approximately {np.sqrt(np.pi)}")

