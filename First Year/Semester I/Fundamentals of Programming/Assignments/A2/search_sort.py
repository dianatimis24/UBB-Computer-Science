"""
    Interpolation Search
    Exchange Sort
    Comb Sort
"""
import random


def print_numbers(listOfNumbers):
    for i in range(len(listOfNumbers)):
        print(listOfNumbers[i], end=" ")
    print()


def generate_n_numbers(listOfNumbers, num):
    for i in range(num):
        randomNumber = random.randint(0, 1000)
        listOfNumbers.append(randomNumber)


def interpolation_search(listOfNumbers, lb, rb, x) -> int:
    if lb <= rb and listOfNumbers[lb] <= x <= listOfNumbers[rb]:
        pos = lb + (((rb - lb) // (listOfNumbers[rb] - listOfNumbers[lb])) * (x - listOfNumbers[lb]))
        if listOfNumbers[pos] == x:
            return pos
        if listOfNumbers[pos] < x:
            return interpolation_search(listOfNumbers, pos + 1, rb, x)
        if listOfNumbers[pos] > x:
            return interpolation_search(listOfNumbers, lb, pos - 1, x)
    return -1


def exchange_sort(listOfNumbers, step):
    counter_steps = 0
    for i in range(len(listOfNumbers) - 1):
        for j in range(i + 1, len(listOfNumbers)):
            if listOfNumbers[i] > listOfNumbers[j]:
                listOfNumbers[i], listOfNumbers[j] = listOfNumbers[j], listOfNumbers[i]
                counter_steps += 1
                if counter_steps % step == 0:
                    print_numbers(listOfNumbers)


def get_next_gap(n: int) -> int:
    gap = (n * 10) // 13
    if gap < 1:
        return 1
    return gap


def comb_sort(listOfNumbers, step):
    counter_steps = 0
    n = len(listOfNumbers)
    gap = n
    swapped = True
    while gap != 1 or swapped == True:
        gap = get_next_gap(gap)
        swapped = False
        for i in range(n - gap):
            if listOfNumbers[i] > listOfNumbers[i + gap]:
                listOfNumbers[i], listOfNumbers[i + gap] = listOfNumbers[i + gap], listOfNumbers[i]
                swapped = True
                counter_steps += 1
                if counter_steps % step == 0:
                    print_numbers(listOfNumbers)


def is_sorted(listOfNumbers) -> bool:
    for i in range(len(listOfNumbers) - 1):
        if listOfNumbers[i] > listOfNumbers[i + 1]:
            return False
    return True


def print_menu():
    print("1. Generate a list of n random numbers")
    print("2. Sort using Exchange Sort")
    print("3. Sort using Comb Sort")
    print("4. Search for a certain number")
    print("0. Exit")


def main():
    numbers = []
    while True:
        print_menu()
        option = int(input("Choose an option: "))
        if option == 0:
            break
        elif option == 1:
            n = int(input("Number of generated numbers: "))
            numbers.clear()
            generate_n_numbers(numbers, n)

            print_numbers(numbers)
        elif option == 2:
            step = int(input("Steps: "))
            exchange_sort(numbers, step)

            print("\nSorted List of numbers: ")
            print_numbers(numbers)
        elif option == 3:
            step = int(input("Steps: "))
            comb_sort(numbers, step)

            print("\nSorted List of numbers: ")
            print_numbers(numbers)
        elif option == 4:
            if is_sorted(numbers):
                num = int(input("Search for number: "))
                pos = interpolation_search(numbers, 0, len(numbers) - 1, num)
                if pos != -1:
                    print("The number " + str(num) + " can be found at position: " + str(pos))
                else:
                    print("The number " + str(num) + " is not in the list.")
            else:
                print("The list is not sorted. Choose a sorting method before searching for a number in the list.")


main()
