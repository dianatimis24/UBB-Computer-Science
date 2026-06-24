"""
Solve the problem from the second set here

Problem 9: Consider a given natural number n. Determine the product p of all the proper factors of n.
"""
from math import sqrt


def proper_factors_product(x: int) -> int:
    prod = 1
    # we begin from 2 in order to avoid 1 and n, the improper factors of any number n
    for i in range(2, int(sqrt(x)) + 1):
        if x % i == 0:
            prod *= i
            if i * i != x:
                prod *= (x / i)
    return prod


def main():
    n = int(input("Insert a number: "))
    p = proper_factors_product(n)
    print(p)


main()
