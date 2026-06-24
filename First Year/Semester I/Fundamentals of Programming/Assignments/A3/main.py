import random
import timeit
import texttable

GENERATE_A_LIST_OF_NUMBERS = 1
SEARCH_FOR_A_NUMBER_WITH_INTERPOLATION = 2
SORT_A_LIST_WITH_EXCHANGE_SORT = 3
SORT_A_LIST_WITH_COMB_SORT = 4
DISPLAY_BEST_CASE = 5
DISPLAY_AVERAGE_CASE = 6
DISPLAY_WORST_CASE = 7
EXIT_THE_MENU = 8
POSITION_NOT_EXISTENT = -1


def print_a_list_of_numbers(listOfNumbers):
    for i in range(len(listOfNumbers)):
        print(listOfNumbers[i], end=" ")
    print()


def generate_a_list_of_numbers(listOfNumbers, numberOfElements):
    try:
        for i in range(numberOfElements):
            randomNumber = random.randint(0, 1000)
            listOfNumbers.append(randomNumber)
    except ValueError:
        print("Invalid input")


def interpolation_search(listOfNumbers, leftBound, rightBound, value) -> int:
    while leftBound <= rightBound and listOfNumbers[leftBound] <= value <= listOfNumbers[rightBound]:
        position = leftBound + (((rightBound - leftBound) // (listOfNumbers[rightBound] - listOfNumbers[leftBound]))
                                * (value - listOfNumbers[leftBound]))
        if listOfNumbers[position] == value:
            return position
        if listOfNumbers[position] < value:
            leftBound = position + 1
        elif listOfNumbers[position] > value:
            rightBound = position - 1
    return POSITION_NOT_EXISTENT


def exchange_sort_ascending(listOfNumbers):
    for i in range(len(listOfNumbers) - 1):
        for j in range(i + 1, len(listOfNumbers)):
            if listOfNumbers[i] > listOfNumbers[j]:
                listOfNumbers[i], listOfNumbers[j] = listOfNumbers[j], listOfNumbers[i]


def exchange_sort_descending(listOfNumbers):
    for i in range(len(listOfNumbers) - 1):
        for j in range(i + 1, len(listOfNumbers)):
            if listOfNumbers[i] < listOfNumbers[j]:
                listOfNumbers[i], listOfNumbers[j] = listOfNumbers[j], listOfNumbers[i]


def get_next_gap(initialGap: int) -> int:
    gap = (initialGap * 10) // 13
    if gap < 1:
        return 1
    return gap


def comb_sort(listOfNumbers):
    length = len(listOfNumbers)
    gap = length
    swapped = True
    while gap != 1 or swapped == True:
        gap = get_next_gap(gap)
        swapped = False
        for i in range(length - gap):
            if listOfNumbers[i] > listOfNumbers[i + gap]:
                listOfNumbers[i], listOfNumbers[i + gap] = listOfNumbers[i + gap], listOfNumbers[i]
                swapped = True


def is_the_list_sorted(listOfNumbers) -> bool:
    for i in range(len(listOfNumbers) - 1):
        if listOfNumbers[i] > listOfNumbers[i + 1]:
            return False
    return True


def build_best_case_for_interpolation_search(listOfNumbers: list) -> float:
    comb_sort(listOfNumbers)
    searchedNumber = random.randint(0, 1000)
    searchedPosition = (((len(listOfNumbers) - 1) // (listOfNumbers[len(listOfNumbers) - 1] - listOfNumbers[0]))
           * (searchedNumber - listOfNumbers[0]))
    searchedNumber = listOfNumbers[searchedPosition]
    startTime = timeit.default_timer()
    interpolation_search(listOfNumbers, 0, len(listOfNumbers) - 1, searchedNumber)
    endTime = timeit.default_timer()
    return endTime - startTime


def build_best_case_for_exchange_sort(listOfNumbers: list) -> float:
    exchange_sort_ascending(listOfNumbers)
    startTime = timeit.default_timer()
    exchange_sort_ascending(listOfNumbers)
    endTime = timeit.default_timer()
    return endTime - startTime


def build_best_case_for_comb_sort(listOfNumbers: list) -> float:
    exchange_sort_ascending(listOfNumbers)
    startTime = timeit.default_timer()
    comb_sort(listOfNumbers)
    endTime = timeit.default_timer()
    return endTime - startTime


# this function displays a table for the best case time of each searching and sorting algorithm
def create_table_for_best_case_times():
    numberOfElements = 500
    timeTable = texttable.Texttable()
    timeTable.add_row(["Number of Elements from list", "Comb Sort", "Exchange Sort", "Interpolation Search"])
    timeTable.set_precision(8)
    for i in range(5):
        listOfNumbers = []
        generate_a_list_of_numbers(listOfNumbers, numberOfElements)
        copyOfListOfNumbers = listOfNumbers.copy()
        timeCombSort = build_best_case_for_comb_sort(copyOfListOfNumbers)
        copyOfListOfNumbers = listOfNumbers.copy()
        timeExchangeSort = build_best_case_for_exchange_sort(copyOfListOfNumbers)
        copyOfListOfNumbers = listOfNumbers.copy()
        timeInterpolationSearch = build_best_case_for_interpolation_search(copyOfListOfNumbers)
        timeTable.add_row([numberOfElements, timeCombSort, timeExchangeSort, timeInterpolationSearch])
        numberOfElements = numberOfElements * 2
    print(timeTable.draw())


def build_average_case_for_interpolation_search(listOfNumbers: list) -> float:
    comb_sort(listOfNumbers)
    startTime = timeit.default_timer()
    searchedNumber = random.randint(0, 1000)
    interpolation_search(listOfNumbers, 0, len(listOfNumbers) - 1, searchedNumber)
    endTime = timeit.default_timer()
    return endTime - startTime


def build_average_case_for_exchange_sort(listOfNumbers: list) -> float:
    startTime = timeit.default_timer()
    exchange_sort_ascending(listOfNumbers)
    endTime = timeit.default_timer()
    return endTime - startTime


def build_average_case_for_comb_sort(listOfNumbers: list) -> float:
    startTime = timeit.default_timer()
    comb_sort(listOfNumbers)
    endTime = timeit.default_timer()
    return endTime - startTime


# this function displays a table for the average case time of each searching and sorting algorithm
def create_table_for_average_case_times():
    numberOfElements = 500
    timeTable = texttable.Texttable()
    timeTable.add_row(["Number of Elements from list", "Comb Sort", "Exchange Sort", "Interpolation Search"])
    timeTable.set_precision(8)
    for i in range(5):
        listOfNumbers = []
        generate_a_list_of_numbers(listOfNumbers, numberOfElements)
        copyOfListOfNumbers = listOfNumbers.copy()
        timeCombSort = build_average_case_for_comb_sort(copyOfListOfNumbers)
        copyOfListOfNumbers = listOfNumbers.copy()
        timeExchangeSort = build_average_case_for_exchange_sort(copyOfListOfNumbers)
        copyOfListOfNumbers = listOfNumbers.copy()
        timeInterpolationSearch = build_average_case_for_interpolation_search(copyOfListOfNumbers)
        timeTable.add_row([numberOfElements, timeCombSort, timeExchangeSort, timeInterpolationSearch])
        numberOfElements = numberOfElements * 2
    print(timeTable.draw())


def build_worst_case_for_interpolation_search(listOfNumbers: list) -> float:
    comb_sort(listOfNumbers)
    startTime = timeit.default_timer()
    searchedNumber = (listOfNumbers[-3] + listOfNumbers[-1]) // 2
    interpolation_search(listOfNumbers, 0, len(listOfNumbers) - 1, searchedNumber)
    endTime = timeit.default_timer()
    return endTime - startTime


def build_worst_case_for_exchange_sort(listOfNumbers: list) -> float:
    exchange_sort_descending(listOfNumbers)
    startTime = timeit.default_timer()
    exchange_sort_ascending(listOfNumbers)
    endTime = timeit.default_timer()
    return endTime - startTime


def build_worst_case_for_comb_sort(listOfNumbers: list) -> float:
    exchange_sort_descending(listOfNumbers)
    startTime = timeit.default_timer()
    comb_sort(listOfNumbers)
    endTime = timeit.default_timer()
    return endTime - startTime


# this function displays a table for the worst case time of each searching and sorting algorithm
def create_table_for_worst_case_times():
    numberOfElements = 500
    timeTable = texttable.Texttable()
    timeTable.add_row(["Number of Elements from list", "Comb Sort", "Exchange Sort", "Interpolation Search"])
    timeTable.set_precision(8)
    for i in range(5):
        listOfNumbers = []
        generate_a_list_of_numbers(listOfNumbers, numberOfElements - 2)
        listOfNumbers.append(listOfNumbers[-1] ** 2)
        listOfNumbers.append(listOfNumbers[-1] ** 2)

        copyOfListOfNumbers = listOfNumbers.copy()
        timeCombSort = build_worst_case_for_comb_sort(copyOfListOfNumbers)
        copyOfListOfNumbers = listOfNumbers.copy()
        timeExchangeSort = build_worst_case_for_exchange_sort(copyOfListOfNumbers)
        copyOfListOfNumbers = listOfNumbers.copy()
        timeInterpolationSearch = build_worst_case_for_interpolation_search(copyOfListOfNumbers)
        timeTable.add_row([numberOfElements, timeCombSort, timeExchangeSort, timeInterpolationSearch])
        numberOfElements = numberOfElements * 2
    print(timeTable.draw())


def print_menu():
    print(str(GENERATE_A_LIST_OF_NUMBERS) +
          ". Generate a list of n random natural numbers. Generated numbers must be between 0 and 1000.")
    print(str(SEARCH_FOR_A_NUMBER_WITH_INTERPOLATION) + ". Search for an item in the list using Interpolation Search.")
    print(str(SORT_A_LIST_WITH_EXCHANGE_SORT) + ". Sort the list using Exchange Sort.")
    print(str(SORT_A_LIST_WITH_COMB_SORT) + ". Sort the list using Comb Sort.")
    print(str(DISPLAY_BEST_CASE) +
          ". Table of the times for best case for Comb Sort, Exchange Sort and Interpolation Search.")
    print(str(DISPLAY_AVERAGE_CASE) +
          ". Table of the times for average case for Comb Sort, Exchange Sort and Interpolation Search.")
    print(str(DISPLAY_WORST_CASE) +
          ". Table of the times for worst case for Comb Sort, Exchange Sort and Interpolation Search.")
    print(str(EXIT_THE_MENU) + ". Exit the menu.")


def main():
    listOfNumbers = []
    while True:
        print_menu()
        try:
            userOption = int(input("Choose an option from the list above: "))
            if userOption == GENERATE_A_LIST_OF_NUMBERS:
                numberOfElements = int(input("Enter a value for n: "))
                listOfNumbers = []
                generate_a_list_of_numbers(listOfNumbers, numberOfElements)
                print(listOfNumbers)

            elif userOption == SEARCH_FOR_A_NUMBER_WITH_INTERPOLATION:
                if is_the_list_sorted(listOfNumbers):
                    searchedNumber = int(input("Enter the number you want to search for in the list: "))
                    searchedNumberPosition = interpolation_search(
                        listOfNumbers,
                        0,
                        len(listOfNumbers) - 1,
                        searchedNumber
                    )
                    if searchedNumberPosition != -1:
                        print("The number " + str(searchedNumber) + " can be found at position: " + str(
                            searchedNumberPosition))
                    else:
                        print("The number " + str(searchedNumber) + " is not in the current list.")
                else:
                    print("The list is not sorted. "
                          "Please choose a method of sorting before searching for an item in the list. ")

            elif userOption == SORT_A_LIST_WITH_EXCHANGE_SORT:
                exchange_sort_ascending(listOfNumbers)

            elif userOption == SORT_A_LIST_WITH_COMB_SORT:
                comb_sort(listOfNumbers)

            elif userOption == DISPLAY_BEST_CASE:
                create_table_for_best_case_times()

            elif userOption == DISPLAY_AVERAGE_CASE:
                create_table_for_average_case_times()

            elif userOption == DISPLAY_WORST_CASE:
                create_table_for_worst_case_times()

            elif userOption == EXIT_THE_MENU:
                break

            else:
                print("Choose another option from the list.")
        except ValueError:
            print("Invalid input")


main()
