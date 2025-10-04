#include <stdio.h>
#include <string.h>

void ReadVectorOfNumbers(int vector[], int *lengthOfVector) {
	// A function that reads a vector of integers from the console and memorises it and its length.
	// vector: the vector of integers
	// lengthOfVector: the length of the vector of integers
	// return: No return value

	printf("Enter the length of the vector: ");
	scanf_s("%d", lengthOfVector);
	printf("Enter the elements of the vector: ");
	for (int i = 0; i < *lengthOfVector; ++i) {
		scanf_s("%d", &vector[i]);
	}
}

void PrintVectorOfNumbers(int vector[], int lengthOfVector) {
	// A function that prints a vector of integers in the console.
	// vector: the vector of integers
	// lengthOfVector: the length of the vector of integers
	// return: No return value

	printf("The elements of the vector are: ");
	for (int i = 0; i < lengthOfVector; ++i)
		printf("%d ", vector[i]);
}
  
float PowerOfARealNumber(float x, int n) {
	// A function that computes the n-th power of the real number x.
	// x: the base - float
	// n: the exponent - int
	// return: the n-th power of x - float

	if (x == 0) return 0;
	if (x == 1 || n == 0) return 1;
	if (n == 1) return x;

	if (n % 2 == 0)
		return PowerOfARealNumber(x, n / 2) * PowerOfARealNumber(x, n / 2);
	else
		return x * PowerOfARealNumber(x, n / 2) * PowerOfARealNumber(x, n / 2);
}

void FindTheLongestSignAlternatingSubsequence(int vector[], int lengthOfVector) {
	// A function that finds the longest contiguous subsequence such that any two consecutive elements have contrary signs and prints it in the console.
	// vector: the vector of integers
	// lengthOfVector: the length of the vector of integers
	// return: No return value

	int maximumLength = 0, maximumStart = 0;
	int currentLength = 1, currentStart = 0;

	for (int i = 1; i < lengthOfVector; i++) {
		if ((vector[i] < 0 && vector[i - 1] > 0) || (vector[i] > 0 && vector[i - 1] < 0)) {
			currentLength++;
			if (currentLength > maximumLength) {
				maximumLength = currentLength;
				maximumStart = currentStart;
			}
		}
		else {
			currentStart = i;
			currentLength = 1;
		}
	}

	printf("The longest contiguous subsequence such that any two consecutive elements have contrary signs has the lenght %d:\n", maximumLength);
	for (int i = maximumStart; i < maximumStart + maximumLength; i++) {
		printf("%d ", vector[i]);
	}
	printf("\n\n");
}

void DecomposeAPrimeNumberIntoItsPrimeFactors(int n) {
	// A function that decomposes a number into its prime factors and prints the decomposition.
	// n: integer to be decomposed
	// No return value, only the printing

	int primeBase = 2, exponent = 0;
	printf("%d = ", n);
	while (n > 1) {
		while (n % primeBase == 0) {
			exponent++;
			n /= primeBase;
		}
		if (exponent > 0) {
			printf("%d ^ %d", primeBase, exponent);
		}
		if (n != 1) {
			printf(" * ");
		}
		primeBase++;
		exponent = 0;
	}
	printf("\n\n");
}

void PrintMenu() {
	// A function that print the menu of valid options in the console.
	// No input/output parameters
	// No return value

	printf("Program menu:\n");
	printf("1. Read a vector of numbers from the console and print it.\n");
	printf("2. Determine the value x^n, where x is a real number and n is a natural number.\n");
	printf("3. Find the longest contiguous subsequence such that any two consecutive elements have contrary signs in a vector of natural numbers.\n");
	printf("4. Decompose a given natural number in its prime factors.\n");
	printf("5. Exit the program.\n");
	printf("Choose an option: ");
}

void PerformOperations() {
	// A function that performs successively the valid operations, based on the choice of the user, until the user chooses to exit the program.
	// No input/output parameters
	// No return value

	int option = 0, lengthOfVector = 0, vector[1000];
	float base = 0, power = 0;
	int exponent = 0, number = 0;
	while (1) {
		PrintMenu();
		scanf_s("%d", &option);

		switch (option) {
		case 1:
			ReadVectorOfNumbers(vector, &lengthOfVector);
			PrintVectorOfNumbers(vector, lengthOfVector);
			printf("\n\n");
			break;
		case 2:
			printf("Enter the real number x: ");
			scanf_s("%f", &base);
			printf("Enter the natural number n: ");
			scanf_s("%d", &exponent);
			power = PowerOfARealNumber(base, exponent);
			printf("The value of x^n, where x = %.3f and n = %d, is equal to %.5f.\n\n", base, exponent, power);
			break;
		case 3:
			ReadVectorOfNumbers(vector, &lengthOfVector);
			FindTheLongestSignAlternatingSubsequence(vector, lengthOfVector);
			break;
		case 4:
			printf("Enter the real number n: ");
			scanf_s("%d", &number);
			DecomposeAPrimeNumberIntoItsPrimeFactors(number);
			break;
		case 5:
			printf("Goodbye!\n");
			return;
		default:
			printf("Invalid input. Please try again!\n\n");
			break;
		}
	}
}

int main() {
	PerformOperations();
	return 0;
}