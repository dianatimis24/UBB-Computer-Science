import math
import matplotlib.pyplot as plt

maximumNumberOfTerms = 500
sumValues = []
partialSum = 0

for i in range(1, maximumNumberOfTerms + 1):
    currentTerm = ((-1) ** (i + 1)) * (1 / i)
    partialSum += currentTerm
    sumValues.append(partialSum)

ln2 = math.log(2)

plt.plot(range(1, maximumNumberOfTerms + 1), sumValues, label="Partial Sum")
plt.axhline(ln2, color='red', linestyle='--', label="ln(2)")

plt.xlabel("Number of terms")
plt.ylabel("Sum Value")
plt.title("Sum of the Alternating Harmonic Series (up to 500) vs ln(2)")
plt.legend()
plt.grid(True)
plt.show()


