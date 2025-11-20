"""
Solve the problem from the third set here

Problem 15: Generate the largest perfect number smaller than a given natural number n.
If such a number does not exist, a message should be displayed.
A number is perfect if it is equal to the sum of its divisors, except itself.(e.g. 6 is a perfect number, as 6=1+2+3)
"""
from math import sqrt


def sum_divisors(x: int) -> int:
    sum = 0
    for i in range(1, int(sqrt(x)) + 1):
        if x % i == 0:
            if i != x:
                sum += i
            if i * i != x and (x / i) != x:
                sum += (x / i)
    return sum


def main():
    n = int(input("Insert a number: "))
    perfNum = -1
    for i in range(n, 0, -1):
        if sum_divisors(i) == i and perfNum == -1:
            perfNum = i
            break
    if perfNum != -1:
        print(perfNum)
    else:
        print("There is no perfect number smaller than " + str(n))


main()
