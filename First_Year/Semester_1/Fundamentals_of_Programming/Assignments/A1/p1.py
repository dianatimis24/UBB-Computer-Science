"""
Solve the problem from the first set here

Problem 5: Generate the largest prime number smaller than a given natural number n.
If such a number does not exist, a message should be displayed.
"""
from math import sqrt


def is_prime(n: int):
    if n == 0 or n == 1:
        return 0
    if n == 2:
        return 1
    if n % 2 == 0:
        return 0
    for d in range(3, int(sqrt(n)) + 1):
        if n % d == 0:
            return 0
    return 1


def main():
    n = int(input("Insert a number: "))
    num = -1
    for i in range(n - 1, 0, -1):
        if is_prime(i) and num == -1:
            num = i
            break
    if num != -1:
        print(num)
    else:
        print("There is no prime number smaller than " + str(n))


main()
