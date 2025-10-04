#
# Write the implementation for A5 in this file
#

import random
from math import sqrt

READ_A_LIST_OF_COMPLEX_NUMBERS = 1
DISPLAY_THE_LIST_OF_COMPLEX_NUMBERS = 2
DISPLAY_THE_SOLUTIONS_TO_THE_GIVEN_PROBLEMS = 3
EXIT_THE_MENU = 4
NUMBER_OF_COMPLEX_NUMBERS_AVAILABLE_AT_PROGRAM_STARTUP = 10
NOT_FOUND_VALUE = -1
INITIALIZATION_VALUE_ZERO = 0
INITIALIZATION_VALUE_ONE = 1
VALUE_OF_THE_INDEX_FOR_THE_REAL_PART = 0
VALUE_OF_THE_INDEX_FOR_THE_IMAGINARY_PART = 1
LOWER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER = 0
UPPER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER = 1000

#
# Write below this comment 
# Functions to deal with complex numbers -- list representation
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


def create_complex_number(theRealPartOfTheComplexNumber: int, theImaginaryPartOfTheNumber: int) -> list:
    return [theRealPartOfTheComplexNumber, theImaginaryPartOfTheNumber]


def get_the_real_part_of_a_complex_number(complexNumber: list) -> int:
    return complexNumber[VALUE_OF_THE_INDEX_FOR_THE_REAL_PART]


def get_the_imaginary_part_of_a_complex_number(complexNumber: list) -> int:
    return complexNumber[VALUE_OF_THE_INDEX_FOR_THE_IMAGINARY_PART]


def set_the_real_part_of_a_complex_number(complexNumber: list, valueForTheRealPartOfAComplexNumber: int):
    complexNumber[VALUE_OF_THE_INDEX_FOR_THE_REAL_PART] = valueForTheRealPartOfAComplexNumber


def set_the_imaginary_part_of_a_complex_number(complexNumber: list, valueForTheImaginaryPartOfAComplexNumber: int):
    complexNumber[VALUE_OF_THE_INDEX_FOR_THE_IMAGINARY_PART] = valueForTheImaginaryPartOfAComplexNumber


def compute_the_modulus_of_a_complex_number(complexNumber: list) -> int:
    return int(sqrt(
        get_the_real_part_of_a_complex_number(complexNumber) * get_the_real_part_of_a_complex_number(complexNumber) +
        get_the_imaginary_part_of_a_complex_number(complexNumber) * get_the_imaginary_part_of_a_complex_number(
            complexNumber)))


def transform_a_complex_number_into_string(complexNumber: list):
    if get_the_imaginary_part_of_a_complex_number(complexNumber) == 0:
        return f"{get_the_real_part_of_a_complex_number(complexNumber)}"
    if get_the_real_part_of_a_complex_number(complexNumber) == 0:
        return f"{get_the_imaginary_part_of_a_complex_number(complexNumber)}i"
    return (f"{get_the_real_part_of_a_complex_number(complexNumber)} + "
            f"{get_the_imaginary_part_of_a_complex_number(complexNumber)}i")


#
# Write below this comment
# Functions to deal with complex numbers -- dict representation
# -> There should be no print or input statements in this section
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#
"""
def create_complex_number(theRealPartOfTheComplexNumber: int, theImaginaryPartOfTheNumber: int):
    return {"theRealPartOfTheComplexNumber": theRealPartOfTheComplexNumber,
            "theImaginaryPartOfTheComplexNumber": theImaginaryPartOfTheNumber}


def get_the_real_part_of_a_complex_number(complexNumber: dict) -> int:
    return complexNumber["theRealPartOfTheComplexNumber"]


def get_the_imaginary_part_of_a_complex_number(complexNumber: dict) -> int:
    return complexNumber["theImaginaryPartOfTheComplexNumber"]


def set_the_real_part_of_a_complex_number(complexNumber: dict, valueForTheRealPartOfAComplexNumber: int):
    complexNumber["theRealPartOfTheComplexNumber"] = valueForTheRealPartOfAComplexNumber


def set_the_imaginary_part_of_a_complex_number(complexNumber: dict, valueForTheImaginaryPartOfAComplexNumber: int):
    complexNumber["theImaginaryPartOfTheComplexNumber"] = valueForTheImaginaryPartOfAComplexNumber


def compute_the_modulus_of_a_complex_number(complexNumber: dict) -> int:
    return int(sqrt(
        get_the_real_part_of_a_complex_number(complexNumber) * get_the_real_part_of_a_complex_number(complexNumber) +
        get_the_imaginary_part_of_a_complex_number(complexNumber) * get_the_imaginary_part_of_a_complex_number(
            complexNumber)))


def transform_a_complex_number_into_string(complexNumber: dict):
    if get_the_imaginary_part_of_a_complex_number(complexNumber) == 0:
        return f"{get_the_real_part_of_a_complex_number(complexNumber)}"
    if get_the_real_part_of_a_complex_number(complexNumber) == 0:
        return f"{get_the_imaginary_part_of_a_complex_number(complexNumber)}i"
    return (f"{get_the_real_part_of_a_complex_number(complexNumber)} + "
            f"{get_the_imaginary_part_of_a_complex_number(complexNumber)}i")

"""
#
# Write below this comment 
# Functions that deal with subarray/subsequence properties
# -> There should be no print or input statements in this section 
# -> Each function should do one thing only
# -> Functions communicate using input parameters and their return values
#


def is_a_prime_number(numberCheckedToBePrime: int):
    """
    A function that checks if a given number is prime.
    :param numberCheckedToBePrime: integer
    :return: True if the given number is prime
             False if the given number is not prime
    """

    if numberCheckedToBePrime == 0 or numberCheckedToBePrime == 1:
        return False
    if numberCheckedToBePrime == 2:
        return True
    if numberCheckedToBePrime % 2 == 0:
        return False
    for divisor in range(3, int(sqrt(numberCheckedToBePrime)) + 1):
        if numberCheckedToBePrime % divisor == 0:
            return False
    return True


def longest_subarray_of_complex_numbers_having_the_difference_between_modulus_of_consecutive_elements_a_prime_number(listOfComplexNumbers):
    """
    A function that finds the length of the longest subarray of complex numbers that have the difference between the modulus
    of consecutive elements a prime number.
    :param listOfComplexNumbers: list of complex numbers
    :return: the length of the subarray - integer (int)
             the elements of the subarray - list of complex numbers
    """

    maximumLengthOfASubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber = INITIALIZATION_VALUE_ONE
    currentLengthOfASubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber = INITIALIZATION_VALUE_ONE
    longestSubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber = [listOfComplexNumbers[0]]

    for i in range(1, len(listOfComplexNumbers)):
        if is_a_prime_number(abs(compute_the_modulus_of_a_complex_number(
                listOfComplexNumbers[i - 1]) - compute_the_modulus_of_a_complex_number(listOfComplexNumbers[i]))):
            currentLengthOfASubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber += 1
            if (currentLengthOfASubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber >
                    maximumLengthOfASubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber):
                maximumLengthOfASubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber \
                    = currentLengthOfASubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber
                longestSubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber \
                    = listOfComplexNumbers[
                      i - currentLengthOfASubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber + 1 : i + 1]
        else:
            currentLengthOfASubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber = 1

    return (maximumLengthOfASubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber,
            longestSubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber)


def longest_alternating_subsequence_using_each_complex_numbers_real_part(listOfComplexNumbers):
    """
    A function that finds the length of the longest alternating subsequence considering the real part of each number`s
    real part and its elements.
    :param listOfComplexNumbers: list of complex numbers
    :return: the length of the alternating subsequence - integer (int)
             the elements of the alternating subsequence - list of complex numbers
    """

    """
    longestAlternatingSubsequenceMatrix[i][0] - length of the longest alternating subsequence that ends at index i and 
                                                has the last element greater than its previous element
    longestAlternatingSubsequenceMatrix[i][1] - length of the longest alternating subsequence that ends at index i and 
                                                has the last element smaller than its previous element
    """
    longestAlternatingSubsequenceMatrix = [[INITIALIZATION_VALUE_ZERO for i in range(2)] for j in range(len(listOfComplexNumbers))]

    for i in range(len(listOfComplexNumbers)):
        longestAlternatingSubsequenceMatrix[i][0], longestAlternatingSubsequenceMatrix[i][1] = INITIALIZATION_VALUE_ONE, INITIALIZATION_VALUE_ONE

    resultLongestAlternatingSubsequence = INITIALIZATION_VALUE_ONE
    longestAlternatingSubsequence = []

    for i in range(1, len(listOfComplexNumbers)):
        for j in range(i):
            if (get_the_real_part_of_a_complex_number(listOfComplexNumbers[j]) < get_the_real_part_of_a_complex_number(listOfComplexNumbers[i])
                    and longestAlternatingSubsequenceMatrix[i][0] < longestAlternatingSubsequenceMatrix[j][1] + 1):
                longestAlternatingSubsequenceMatrix[i][0] = longestAlternatingSubsequenceMatrix[j][1] + 1
            if (get_the_real_part_of_a_complex_number(listOfComplexNumbers[j]) > get_the_real_part_of_a_complex_number(listOfComplexNumbers[i])
                    and longestAlternatingSubsequenceMatrix[i][1] < longestAlternatingSubsequenceMatrix[j][0] + 1):
                longestAlternatingSubsequenceMatrix[i][1] = longestAlternatingSubsequenceMatrix[j][0] + 1
        if resultLongestAlternatingSubsequence < max(longestAlternatingSubsequenceMatrix[i][0], longestAlternatingSubsequenceMatrix[i][1]):
            resultLongestAlternatingSubsequence = max(longestAlternatingSubsequenceMatrix[i][0], longestAlternatingSubsequenceMatrix[i][1])

    lastIncreasingElementPlacedInTheAlternatingSequence = lastDecreasingElementPlacedInTheAlternatingSequence = NOT_FOUND_VALUE
    temporaryResultLongestAlternatingSubsequence = resultLongestAlternatingSubsequence

    for i in range(len(listOfComplexNumbers) - 1, -1, -1):
        if (longestAlternatingSubsequenceMatrix[i][0] == temporaryResultLongestAlternatingSubsequence and
                (lastIncreasingElementPlacedInTheAlternatingSequence == NOT_FOUND_VALUE or
                 get_the_real_part_of_a_complex_number(listOfComplexNumbers[i]) >
                 get_the_real_part_of_a_complex_number(listOfComplexNumbers[lastDecreasingElementPlacedInTheAlternatingSequence]))):
            longestAlternatingSubsequence.append(listOfComplexNumbers[i])
            temporaryResultLongestAlternatingSubsequence -= 1
            lastIncreasingElementPlacedInTheAlternatingSequence = i
        elif (longestAlternatingSubsequenceMatrix[i][1] == temporaryResultLongestAlternatingSubsequence and
                (lastDecreasingElementPlacedInTheAlternatingSequence == NOT_FOUND_VALUE or
                 get_the_real_part_of_a_complex_number(listOfComplexNumbers[i]) <
                 get_the_real_part_of_a_complex_number(listOfComplexNumbers[lastIncreasingElementPlacedInTheAlternatingSequence]))):
            longestAlternatingSubsequence.append(listOfComplexNumbers[i])
            temporaryResultLongestAlternatingSubsequence -= 1
            lastDecreasingElementPlacedInTheAlternatingSequence = i

    longestAlternatingSubsequence.reverse()

    return resultLongestAlternatingSubsequence, longestAlternatingSubsequence


#
# Write below this comment 
# UI section
# Write all functions that have input or print statements here
# Ideally, this section should not contain any calculations relevant to program functionalities
#

def print_menu():
    print(str(READ_A_LIST_OF_COMPLEX_NUMBERS) + ". Read a list of Complex Numbers from the console.")
    print(str(DISPLAY_THE_LIST_OF_COMPLEX_NUMBERS) + ". Display the list of Complex Numbers.")
    print(str(DISPLAY_THE_SOLUTIONS_TO_THE_GIVEN_PROBLEMS) + ". Display the solutions to the given problems.")
    print(str(EXIT_THE_MENU) + ". Exit the menu.")


def generate_a_list_of_complex_numbers(numberOfComplexNumbersToBeGenerated) -> list:
    listOfComplexNumbers = []
    for i in range(numberOfComplexNumbersToBeGenerated):
        listOfComplexNumbers.append(
            create_complex_number(random.randint(LOWER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER, UPPER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER),
                                  random.randint(LOWER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER, UPPER_BOUND_FOR_GENERATING_A_RANDOM_INTEGER)))
    return listOfComplexNumbers


def read_a_list_of_complex_numbers(listOfComplexNumbers, numberOfComplexNumbers):
    for i in range(numberOfComplexNumbers):
        realPartOfTheComplexNumber = int(input("Real Part Of The Complex Number: "))
        imaginaryPartOfTheComplexNumber = int(input("Imaginary Part Of The Complex Number: "))
        listOfComplexNumbers.append(create_complex_number(realPartOfTheComplexNumber, imaginaryPartOfTheComplexNumber))


def display_the_list_of_complex_numbers(listOfComplexNumbers):
    print("The list of complex numbers is: ")
    for i in range(len(listOfComplexNumbers)):
        print(transform_a_complex_number_into_string(listOfComplexNumbers[i]), end="   ")
    print()


def display_the_solutions_to_the_given_problems(listOfComplexNumbers):
    print("The length and the elements of the longest subarray of complex numbers having the difference between modulus"
          " of consecutive numbers a prime number")
    (maximumLengthOfASubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber,
     longestSubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber) = (
        longest_subarray_of_complex_numbers_having_the_difference_between_modulus_of_consecutive_elements_a_prime_number(
            listOfComplexNumbers))
    print("The length: " + str(
        maximumLengthOfASubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber))
    print("The subarray: ")
    for i in range(len(longestSubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber)):
        print(transform_a_complex_number_into_string(
            longestSubarrayOfNumbersHavingTheDifferenceBetweenModulusOfConsecutiveNumbersAPrimeNumber[i]))

    print()

    print(
        "The length and the elements of the longest alternating subsequence, when considering each number`s real part")
    (maximumLengthOfTheLongestAlternatingSubsequence, longestAlternatingSubsequence) = (
        longest_alternating_subsequence_using_each_complex_numbers_real_part(listOfComplexNumbers))
    print("The length: " + str(maximumLengthOfTheLongestAlternatingSubsequence))
    print("The subsequence: ")
    for i in range(len(longestAlternatingSubsequence)):
        print(transform_a_complex_number_into_string(longestAlternatingSubsequence[i]))
    print()


if __name__ == "__main__":
    listOfComplexNumbersListRepresentation = generate_a_list_of_complex_numbers(
        NUMBER_OF_COMPLEX_NUMBERS_AVAILABLE_AT_PROGRAM_STARTUP)
    while True:
        print_menu()
        try:
            userOption = int(input("Choose an option from the list above: "))
            if userOption == READ_A_LIST_OF_COMPLEX_NUMBERS:
                numberOfComplexNumbersToBeRead = int(input("The number of Complex Numbers: "))
                read_a_list_of_complex_numbers(listOfComplexNumbersListRepresentation, numberOfComplexNumbersToBeRead)
            elif userOption == DISPLAY_THE_LIST_OF_COMPLEX_NUMBERS:
                display_the_list_of_complex_numbers(listOfComplexNumbersListRepresentation)
            elif userOption == DISPLAY_THE_SOLUTIONS_TO_THE_GIVEN_PROBLEMS:
                display_the_solutions_to_the_given_problems(listOfComplexNumbersListRepresentation)
            elif userOption == EXIT_THE_MENU:
                break
            else:
                print("Choose a valid option from the list.")
        except ValueError:
            print("Invalid input")
