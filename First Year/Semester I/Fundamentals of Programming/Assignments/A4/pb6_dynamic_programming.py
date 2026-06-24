"""
 6. Given an array of integers A, maximize the value of the expression A[m] - A[n] + A[p] - A[q],
    where m, n, p, q are array indices with m > n > p > q. For A = [30, 5, 15, 18, 30, 40], the maximum value is 32,
    obtained as 40 - 18 + 15 - 5. Display both the maximum value as well as the expression used to calculate it.
"""
import sys


THE_SMALLEST_VALUE_OF_AN_INTEGER = -sys.maxsize - 1
NULL_VALUE = 0


def dynamic_programming_algorithm_to_maximize_the_value_of_the_alternating_expression(givenArrayOfIntegers: list) -> tuple:
    maximumValueOfTheAlternatingExpression = [[0 for currentColumn in range(len(givenArrayOfIntegers) + 1)] for currentRow in range(5)]
    termsUsedInComputingTheAlternatingExpression = []

    for i in range(5):
        for j in range(len(givenArrayOfIntegers) + 1):
            if i == 0 or j == len(givenArrayOfIntegers):
                maximumValueOfTheAlternatingExpression[i][j] = NULL_VALUE
            else:
                maximumValueOfTheAlternatingExpression[i][j] = THE_SMALLEST_VALUE_OF_AN_INTEGER

    for numberOfOperands in range(1, 5):
        for index in range(len(givenArrayOfIntegers) - numberOfOperands, -1, -1):
            currentTerm = ((-1) ** (numberOfOperands + 1)) * givenArrayOfIntegers[index]
            maximumValueOfTheAlternatingExpression[numberOfOperands][index] = (
                max(maximumValueOfTheAlternatingExpression[numberOfOperands][index + 1],
                    maximumValueOfTheAlternatingExpression[numberOfOperands - 1][index + 1] + currentTerm))

    currentColumnForSearchingTheTermsOfTheExpression = 0
    for i in range(4, 0, -1):
        for j in range(currentColumnForSearchingTheTermsOfTheExpression, len(givenArrayOfIntegers) + 1 - i):
            if maximumValueOfTheAlternatingExpression[i][j] == maximumValueOfTheAlternatingExpression[i][j + 1]:
                continue
            else:
                termsUsedInComputingTheAlternatingExpression.append(givenArrayOfIntegers[j])
                currentColumnForSearchingTheTermsOfTheExpression = j + 1
                break

    termsUsedInComputingTheAlternatingExpression.reverse()
    return (maximumValueOfTheAlternatingExpression[4][0],
            termsUsedInComputingTheAlternatingExpression,
            maximumValueOfTheAlternatingExpression)


def naive_algorithm_to_maximize_the_value_of_the_alternating_expression(givenArrayOfIntegers: list) -> tuple:
    maximumValueOfTheAlternatingExpression = THE_SMALLEST_VALUE_OF_AN_INTEGER
    termsUsedInComputingTheAlternatingExpression = []

    for index_firstTermOfTheExpression in range(len(givenArrayOfIntegers) - 1, -1, -1):
        temporarySum_firstTermOfTheExpression = givenArrayOfIntegers[index_firstTermOfTheExpression]
        for index_secondTermOfTheExpression in range(index_firstTermOfTheExpression - 1, -1, -1):
            temporarySum_secondTermOfTheExpression = temporarySum_firstTermOfTheExpression
            temporarySum_secondTermOfTheExpression -= givenArrayOfIntegers[index_secondTermOfTheExpression]
            for index_thirdTermOfTheExpression in range(index_secondTermOfTheExpression - 1, -1, -1):
                temporarySum_thirdTermOfTheExpression = temporarySum_secondTermOfTheExpression
                temporarySum_thirdTermOfTheExpression += givenArrayOfIntegers[index_thirdTermOfTheExpression]
                for index_fourthTermOfTheExpression in range(index_thirdTermOfTheExpression - 1, -1, -1):
                    temporarySum_fourthTermOfTheExpression = temporarySum_thirdTermOfTheExpression
                    temporarySum_fourthTermOfTheExpression -= givenArrayOfIntegers[index_fourthTermOfTheExpression]

                    if temporarySum_fourthTermOfTheExpression > maximumValueOfTheAlternatingExpression:
                        maximumValueOfTheAlternatingExpression = temporarySum_fourthTermOfTheExpression
                        termsUsedInComputingTheAlternatingExpression = \
                            [givenArrayOfIntegers[index_firstTermOfTheExpression],
                             givenArrayOfIntegers[index_secondTermOfTheExpression],
                             givenArrayOfIntegers[index_thirdTermOfTheExpression],
                             givenArrayOfIntegers[index_fourthTermOfTheExpression]]

    return (maximumValueOfTheAlternatingExpression, termsUsedInComputingTheAlternatingExpression)


def main():
    numberOfElementsOfTheSequence = int(input("Enter the number of the elements of the sequence: "))
    inputSequenceOfNumbers = []
    for i in range(numberOfElementsOfTheSequence):
        currentNumber = int(input())
        inputSequenceOfNumbers.append(currentNumber)

    print("Naive Algorithm")
    (maximumValueOfTheAlternatingExpressionNaive,
     termsUsedInComputingTheAlternatingExpressionNaive) = (
        naive_algorithm_to_maximize_the_value_of_the_alternating_expression(inputSequenceOfNumbers))

    print(maximumValueOfTheAlternatingExpressionNaive)
    print(str(termsUsedInComputingTheAlternatingExpressionNaive[0]) + " - " +
          str(termsUsedInComputingTheAlternatingExpressionNaive[1]) + " + " +
          str(termsUsedInComputingTheAlternatingExpressionNaive[2]) + " - " +
          str(termsUsedInComputingTheAlternatingExpressionNaive[3]))

    print()

    print("Dynamic Programming Algorithm")
    (maximumValueOfTheAlternatingExpressionDynamicProgramming,
     termsUsedInComputingTheAlternatingExpressionDynamicProgramming,
     maximumValueOfTheAlternatingExpression) = (
        dynamic_programming_algorithm_to_maximize_the_value_of_the_alternating_expression(inputSequenceOfNumbers))

    print(maximumValueOfTheAlternatingExpressionDynamicProgramming)
    print(str(termsUsedInComputingTheAlternatingExpressionDynamicProgramming[0]) + " - " +
          str(termsUsedInComputingTheAlternatingExpressionDynamicProgramming[1]) + " + " +
          str(termsUsedInComputingTheAlternatingExpressionDynamicProgramming[2]) + " - " +
          str(termsUsedInComputingTheAlternatingExpressionDynamicProgramming[3]))
    print()
    for i in range(5):
        for j in range(len(inputSequenceOfNumbers) + 1):
            print(maximumValueOfTheAlternatingExpression[i][j], end=" ")
        print()


main()
