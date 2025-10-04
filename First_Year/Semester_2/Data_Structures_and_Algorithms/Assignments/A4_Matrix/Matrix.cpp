#include "Matrix.h"
#include <exception>
#include <cmath>
#include <iostream>
using namespace std;

// Constructor
// Time Complexity, where n is the capacity:
// - Best Case: Theta(n) - Directly proportional to the current capacity of the array
// - Worst Case: Theta(n) - Directly proportional to the current capacity of the array
// - Total Complexity: Theta(n) - Directly proportional to the current capacity of the array
Matrix::Matrix(int nrLines, int nrCols) 
{
	this->nrLins = nrLines;
	this->nrCols = nrCols;
	this->size = 0;
	this->capacity = 131071;
	this->triplets = new Triple[this->capacity];
	for (int i = 0; i < this->capacity; ++i)
		this->triplets[i] = NULL_TRIPLE;
}


// Destructor
// Time Complexity:
// - Best Case: Theta(1) - Deletion of the array is a constant time operation
// - Worst Case: Theta(1) - Deletion of the array is a constant time operation
// - Total Complexity: Theta(1) - Deletion of the array is a constant time operation
Matrix::~Matrix()
{
	delete[] this->triplets;
}


// Returns the number of lines
// Time Complexity:
// - Best Case: Theta(1) - Direct access to a member variable
// - Worst Case: Theta(1) - Direct access to a member variable
// - Total Complexity: Theta(1) - Direct access to a member variable
int Matrix::nrLines() const 
{
	return this->nrLins;
}


// Returns the number of columns
// Time Complexity:
// - Best Case: Theta(1) - Direct access to a member variable
// - Worst Case: Theta(1) - Direct access to a member variable
// - Total Complexity: Theta(1) - Direct access to a member variable
int Matrix::nrColumns() const 
{
	return this->nrCols;
}


// Returns the element from line i and column j (indexing starts from 0)
// Throws exception if (i,j) is not a valid position in the Matrix
// Time Complexity, where n is the capacity:
// - Best Case: Theta(1) - The searched element is found in the first probe
// - Worst Case: Theta(n) - The function needs to probe every slot in the hashtable
// - Total Complexity: Theta(1) - Amortizat
TElem Matrix::element(int i, int j) const 
{
	if (i < 0 || i >= this->nrLins || j < 0 || j >= this->nrCols)
		throw std::exception();

	int index;
	pair<int, int> position = { i, j };
	for (int probe = 0; probe < this->capacity; ++probe)
	{
		index = this->hash(i, j, probe);
		if (this->triplets[index].first.first == -1 && this->triplets[index].first.second == -1 && this->triplets[index].second == NULL_TELEM)
			return NULL_TELEM;
		if (!isElementDeleted(this->triplets[index]) && this->triplets[index].first == position)
			return this->triplets[index].second;
	}
	return NULL_TELEM;
}


// Modifies the value from line i and column j
// Returns the previous value from the position
// Throws exception if (i,j) is not a valid position in the Matrix
// Time Complexity, where n is the capacity:
// - Best Case: Theta(1) - The desired position is found in the first probe and no resizing is needed
// - Worst Case: Theta(n) - All n slots has to be probed and the value from the desired position is modified afterwards
// - Total Complexity: Theta(1) - Amortizat
TElem Matrix::modify(int i, int j, TElem e) 
{
	if (i < 0 || i >= this->nrLins || j < 0 || j >= this->nrCols)
		throw std::exception();

	int index, firstDeletedIndex = -1;
	pair<int, int> position = { i, j };
	TElem previousValue = NULL_TELEM;
	for (int probe = 0; probe < this->capacity; ++probe)
	{
		index = this->hash(i, j, probe);
		if (this->triplets[index].first.first == -1 && this->triplets[index].first.second == -1 && this->triplets[index].second == NULL_TELEM)
		{
			if (e != NULL_TELEM)
			{
				if (firstDeletedIndex != -1)
					this->triplets[firstDeletedIndex] = { position, e };
				else
					this->triplets[index] = { position, e };
				this->size++;
				
				if ((double)this->size / this->capacity >= 0.5)
					this->resize();
			}
			return NULL_TELEM;
		}
		if (isElementDeleted(this->triplets[index]))
		{
			if (firstDeletedIndex == -1)
				firstDeletedIndex = index;
		}
		else if (this->triplets[index].first == position)
		{
			previousValue = this->triplets[index].second;
			if (e != NULL_TELEM)
				this->triplets[index].second = e;
			else
			{
				this->triplets[index] = DELETED_TRIPLE;
				this->size--;
			}
			return previousValue;
		}
	}
	return NULL_TELEM;
}


// Computes the hash value for the element from line i and column j, using open addressing, quadratic probing formula (probe - the number of collisions that occured so far)
// Time Complexity:
// - Best Case: Theta(1) - The calculations are done in constant time
// - Worst Case: Theta(1) - The calculations are done in constant time
// - Total Complexity: Theta(1) - The calculations are done in constant time
int Matrix::hash(int i, int j, int probe) const
{
	int key = i * this->nrCols + j;
	int hashValue = abs(key);
	return (hashValue + probe * (probe + 1) / 2) % this->capacity;
}


// Checks if a given triple was deleted
// - Best Case: Theta(1) - The checks are done in constant time
// - Worst Case: Theta(1) - The checks are done in constant time
// - Total Complexity: Theta(1) - The checks are done in constant time
bool Matrix::isElementDeleted(const Triple& triple) const {
	return triple.first.first == -2 && triple.first.second == -2;
}


// Checks if a given number is prime
// Time Complexity:
// - Best Case: Theta(1) - number <= 3
// - Worst Case: Theta(sqrt(number)) - the number is prime or it is the square of a prime number 
// - Total Complexity: O(sqrt(number))
bool Matrix::isPrime(int number)
{
	if (number == 0 || number == 1) return false;
	if (number == 2) return true;
	if (number % 2 == 0) return false;
	for (int d = 3; d * d <= number; d += 2)
		if (number % d == 0)
			return false;
	return true;
}


// Finds the first prime number after a given number
// Time Complexity:
// - Best Case: Theta(1) - the number is already prime or is 0 or 1 (in these cases the function returns 2)
// - Worst Case: Theta(sqrt(number) * log(number)) - log(number) is the maximal time to find the next prime number and for each intermediate number we have to check if it is prime (sqrt(n) in the worst case)
// - Total Complexity: O(sqrt(number) * log(number))
int Matrix::nextPrimeNumber(int number)
{
	if (number <= 1)
		return 2;
	int nextPrimeNumber = number;
	if (nextPrimeNumber % 2 == 0)
		nextPrimeNumber++;
	while (!isPrime(nextPrimeNumber)) 
		nextPrimeNumber += 2;
	
	return nextPrimeNumber;
}


// Increases the capacity of the storage hashtable when more space is needed and rehashes the elements
// Time Complexity, where n is the capacity:
// - Best Case: Theta(n^2) - All the elements has to be copied and rehashed
// - Worst Case: Theta(n^2) - All the elements has to be copied and rehashed
// - Total Complexity: Theta(n^2) - All the elements has to be copied and rehashed
void Matrix::resize()
{
	int newCapacity = nextPrimeNumber(this->capacity * 2);
	Triple* newTriplets = new Triple[newCapacity];
	int currentRow, currentColumn;
	for (int i = 0; i < newCapacity; ++i)
		newTriplets[i] = NULL_TRIPLE;
	for (int i = 0; i < this->capacity; ++i)
		if ((this->triplets[i].first.first != -1 || this->triplets[i].first.second != -1 || this->triplets[i].second != NULL_TELEM) && !isElementDeleted(this->triplets[i]))
		{
			int probe = 0, index = this->hash(this->triplets[i].first.first, this->triplets[i].first.second, probe);
			while (newTriplets[index].first.first != -1 || newTriplets[index].first.second != -1 || newTriplets[index].second != NULL_TELEM)
			{
				++probe;
				index = this->hash(this->triplets[i].first.first, this->triplets[i].first.second, probe);
			}
			newTriplets[index] = this->triplets[i];
		}

	delete[] this->triplets;
	this->triplets = newTriplets;
	this->capacity = newCapacity;
}

// Removes all elements on the main diagonal of the matrix.
// Time Complexity, where n is the capacity:
// - Best Case: Theta(nrLins) - We have to check each element on the main diagonal and in each case the element is in the first slot
// - Worst Case: Theta(nrLins * n) - We have to check each element on the main diagonal and in each case the element is in the last slot
// - Total Complexity: Theta(nrLins) - Amortizat (modify() amortizat)
void Matrix::removeDiagonal()
{
	for (int i = 0; i < this->nrLins; ++i)
		modify(i, i, NULL_TELEM);
}


