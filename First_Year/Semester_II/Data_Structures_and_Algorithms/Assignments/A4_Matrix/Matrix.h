#pragma once
#include <utility>

//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

typedef std::pair<std::pair<int, int>, TElem> Triple;
#define NULL_TRIPLE {{-1, -1}, NULL_TELEM}
#define DELETED_TRIPLE {{-2, -2}, NULL_TELEM}

class Matrix {
private:
	int nrLins, nrCols;
	Triple* triplets;
	int size, capacity;

	// Computes the hash value for the element from line i and column j, using open addressing, quadratic probing formula
	int hash(int i, int j, int probe) const;

	// Checks if a given triple was deleted
	bool isElementDeleted(const Triple& triple) const;

	// Checks if a given number is prime
	bool isPrime(int number);

	// Finds the first prime number after a given number
	int nextPrimeNumber(int number);

	// Increases the capacity of the storage hashtable when more space is needed and rehashes the elements
	void resize();

public:
	//constructor
	Matrix(int nrLines, int nrCols);

	//returns the number of lines
	int nrLines() const;

	//returns the number of columns
	int nrColumns() const;

	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem element(int i, int j) const;

	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	TElem modify(int i, int j, TElem e);

	//destructor
	~Matrix();

	// Removes all elements on the main diagonal of the matrix.
	void removeDiagonal();
};
