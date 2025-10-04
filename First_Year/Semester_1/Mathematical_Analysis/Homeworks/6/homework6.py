
import matplotlib.pyplot as plt

def f(x): return x**2

def the_first_derivative_of_f(x): return 2 * x

def alternative_formula_1_for_calculating_the_first_derivative_of_f(x, h): return (f(x + h) - f(x)) / h

def alternative_formula_2_for_calculating_the_first_derivative_of_f(x, h): return (f(x + h) - f(x - h)) / (2 * h)


h = [i for i in range(-20, 21)]
h.remove(0)
value = 0
plt.plot([f(x) for x in range(-20, 21)], label="f(x)")
plt.plot([the_first_derivative_of_f(x) for x in range(-20, 21)], label="f`(x)")
plt.plot([alternative_formula_1_for_calculating_the_first_derivative_of_f(value, num) for num in h],
         label="(f(x + h) - f(x)) / h")
plt.plot([alternative_formula_2_for_calculating_the_first_derivative_of_f(value, num) for num in h],
         label="(f(x + h) - f(x - h)) / (2 * h)")

plt.xlabel("x")
plt.ylabel("functions")
plt.title("f(x), f`(x) and alternative ways of calculating the first derivative of f")
plt.legend()
plt.grid(True)
plt.show()

