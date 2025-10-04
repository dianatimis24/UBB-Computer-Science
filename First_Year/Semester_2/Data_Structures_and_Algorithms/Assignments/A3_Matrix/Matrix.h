#pragma once
#include <utility>
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

typedef std::pair<std::pair<int, int>, TElem> Triple;
#define NULL_TRIPLE {{-1, -1}, NULL_TELEM}

class Matrix {

private:
	int nrLins, nrCols;
	Triple* triplets;
	int *next, *previous;
	int size, capacity, first, firstEmpty;

	// Doubles the capacity of the storage arrays when more space is needed.
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

	// Sets all values in the specified column to NULL_TELEM.
	void clearColumn(int col);
};
