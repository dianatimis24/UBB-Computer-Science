"""
 3. The sequence a = a1, ..., an with integer elements is given.
    Determine all strictly increasing subsequences of sequence a
    (conserve the order of elements in the original sequence).
"""


def backtracking_iterative_to_determine_the_increasing_subsequences_of_a_given_sequence(givenSequence: list) -> list:
    iterativeSubsequencesResults = []
    stackIterativeBacktrackingToDetermineTheIncreasingSubsequences = [(0, [])]

    while stackIterativeBacktrackingToDetermineTheIncreasingSubsequences:
        indexCurrentIteration, currentIncreasingSubsequence = stackIterativeBacktrackingToDetermineTheIncreasingSubsequences.pop()

        if 0 < len(currentIncreasingSubsequence) <= len(givenSequence):
            iterativeSubsequencesResults.append(currentIncreasingSubsequence)

        for i in range(indexCurrentIteration, len(givenSequence)):
            if len(currentIncreasingSubsequence) == 0 or givenSequence[i] > currentIncreasingSubsequence[-1]:
                stackIterativeBacktrackingToDetermineTheIncreasingSubsequences.append(
                    (i + 1, currentIncreasingSubsequence + [givenSequence[i]]))
    return iterativeSubsequencesResults


def backtracking_recursive_to_determine_the_increasing_subsequences_of_a_given_sequence(givenSequence: list,
                                                                                        currentIncreasingSubsequence: list,
                                                                                        indexInTheGivenSequence: int,
                                                                                        lengthCurrentIncreasingSubsequence: int,
                                                                                        recursiveSubsequencesResults: list):
    for i in range(indexInTheGivenSequence, len(givenSequence)):
        if lengthCurrentIncreasingSubsequence == 0 or givenSequence[i] > currentIncreasingSubsequence[-1]:
            currentIncreasingSubsequence.append(givenSequence[i])
            if len(currentIncreasingSubsequence) <= len(givenSequence):
                recursiveSubsequencesResults.append(currentIncreasingSubsequence.copy())
            backtracking_recursive_to_determine_the_increasing_subsequences_of_a_given_sequence(givenSequence,
                                                                                                currentIncreasingSubsequence,
                                                                                                i + 1,
                                                                                                lengthCurrentIncreasingSubsequence + 1,
                                                                                                recursiveSubsequencesResults)
            currentIncreasingSubsequence.pop()


def main():
    numberOfElementsOfTheSequence = int(input("Enter the number of the elements of the sequence: "))
    inputSequenceOfNumbers = []
    for i in range(numberOfElementsOfTheSequence):
        currentNumber = int(input())
        inputSequenceOfNumbers.append(currentNumber)

    print("Iterative Backtracking")
    resultIncreasingSubsequencesIterative = (
        backtracking_iterative_to_determine_the_increasing_subsequences_of_a_given_sequence(inputSequenceOfNumbers))
    for subsequence in resultIncreasingSubsequencesIterative:
        print(subsequence)

    print()

    print("Recursive Backtracking")
    resultIncreasingSubsequencesRecursive = []
    backtracking_recursive_to_determine_the_increasing_subsequences_of_a_given_sequence(
        inputSequenceOfNumbers,
        [],
        0,
        0,
        resultIncreasingSubsequencesRecursive)
    for subsequence in resultIncreasingSubsequencesRecursive:
        print(subsequence)


main()
