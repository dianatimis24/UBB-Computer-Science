import math
import matplotlib.pyplot as plt

numberOfPositiveTerms = int(input("Enter the number of positive terms added consecutively to the alternating sum: "))
numberOfNegativeTerms = int(input("Enter the number of negative terms added consecutively to the alternating sum: "))

maximumNumberOfTerms = 200 * (numberOfPositiveTerms + numberOfNegativeTerms)
sumValues = []
partialSum = 0

n = 1
oddNumber = 1
evenNumber = 2
while n <= maximumNumberOfTerms:
    for i in range(numberOfPositiveTerms):
        currentTerm = 1 / oddNumber
        partialSum += currentTerm
        n += 1
        oddNumber += 2
        sumValues.append(partialSum)
    for i in range(numberOfNegativeTerms):
        currentTerm = -1 / evenNumber
        partialSum += currentTerm
        n += 1
        evenNumber += 2
        sumValues.append(partialSum)

ln2 = math.log(2)

plt.plot(range(1, maximumNumberOfTerms + 1), sumValues, label="Partial Sum")
plt.axhline(ln2, color='red', linestyle='--', label="ln(2)")

plt.xlabel("Number of terms")
plt.ylabel("Sum Value")
plt.title("Sum of the Alternating Harmonic Series (up to 500) vs ln(2) when we are adding consecutively " +
          str(numberOfPositiveTerms) + " positive terms and " +
          str(numberOfNegativeTerms) + " negative terms")
plt.legend()
plt.grid(True)
plt.show()

