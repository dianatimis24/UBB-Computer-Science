#pragma once
#include <iostream>
#include <utility>
//DO NOT CHANGE THIS PART
typedef int TElem;
#define NULL_TELEM 0

typedef std::pair<std::pair<int, int>, TElem> Triple;
#define NULL_TRIPLE {{-1, -1}, NULL_TELEM}

struct Node {
	Triple triple;
	Node* next;

	Node(Triple t, Node* n = nullptr) : triple(t), next(n) {}
};

class Matrix {

private:
	int nrLins, nrCols;
	Node* head;

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

	//returns the position(as a line–column pair) of the first occurrence of the given element
	//if the element is not found, returns <-1, -1>
	std::pair<int, int> positionOf(TElem elem) const;
};
