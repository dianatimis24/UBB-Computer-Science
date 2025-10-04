#include "Matrix.h"
#include <exception>
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
	this->capacity = 10;
	this->first = -1;
	this->firstEmpty = 0;

	this->triplets = new Triple[this->capacity];
	this->next = new int[this->capacity];
	this->previous = new int[this->capacity];

	for (int i = 0; i < this->capacity; ++i)
	{
		this->triplets[i] = NULL_TRIPLE;
		this->next[i] = i + 1;
		this->previous[i] = i - 1;
	}
	this->next[capacity - 1] = -1;
	this->previous[0] = -1;
}


// Destructor
// Time Complexity:
// - Best Case: Theta(1) - Deletion of the arrays is a constant time operation
// - Worst Case: Theta(1) - Deletion of the arrays is a constant time operation
// - Total Complexity: Theta(1) - Deletion of the arrays is a constant time operation
Matrix::~Matrix()
{
	delete[] triplets;
	delete[] next;
	delete[] previous;
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
// - Best Case: Theta(1) - The searched element is the head
// - Worst Case: Theta(n) - The element is either the last one checked, or is not found
// - Total Complexity: O(n) - Assumes elements are evenly distributed
TElem Matrix::element(int i, int j) const 
{
	if (i < 0 || i >= this->nrLins || j < 0 || j >= this->nrCols)
		throw std::exception();

	std::pair<int, int> position = {i, j};
	int current = this->first;
	while (current != -1)
	{
		if (this->triplets[current].first == position)
			return this->triplets[current].second;
		current = this->next[current];
	}
	return NULL_TELEM;
}


// Modifies the value from line i and column j
// Returns the previous value from the position
// Throws exception if (i,j) is not a valid position in the Matrix
// Time Complexity, where n is the capacity:
// - Best Case: Theta(1) - The searched element is the head or has to be inserted before the head
// - Worst Case: Theta(n) - The element is either the last one checked before modification, or is added as a new element
// - Total Complexity: O(n) - Assumes elements are evenly distributed
TElem Matrix::modify(int i, int j, TElem e) 
{
	if (i < 0 || i >= this->nrLins || j < 0 || j >= this->nrCols)
		throw std::exception();

	TElem previousValue = NULL_TELEM;
	std::pair<int, int> position = {i, j};
	int current = this->first, prev = -1;

	while (current != -1 && this->triplets[current].first <= position)
	{
		if (this->triplets[current].first == position)
		{
			previousValue = this->triplets[current].second;
			if (e == NULL_TELEM) // we want to remove this element
			{
				if (prev == -1)
					this->first = this->next[current];
				else
					this->next[prev] = this->next[current];

				this->next[current] = this->firstEmpty;
				this->triplets[current] = NULL_TRIPLE;
				this->firstEmpty = current;
				this->size--;
				return previousValue;
			}
			else
			{
				this->triplets[current].second = e;
				return previousValue;
			}
		}
		prev = current;
		current = this->next[current];
	} 

	if (e == NULL_TELEM) // we want to remove that element, but it does not exist in the matrix
		return NULL_TELEM;

	if (this->firstEmpty == -1 || this->size == this->capacity)
		this->resize();

	int newPosition = this->firstEmpty;
	this->firstEmpty = this->next[this->firstEmpty];

	this->triplets[newPosition] = {position, e};
	this->next[newPosition] = -1;
	this->previous[newPosition] = -1;

	if (prev == -1)
	{
		this->next[newPosition] = this->first;
		if (this->first != -1)
			this->previous[this->first] = newPosition;
		this->first = newPosition;
	}
	else
	{
		this->next[newPosition] = this->next[prev];
		this->previous[newPosition] = prev;
		this->next[prev] = newPosition;

		if (this->next[newPosition] != -1)
			this->previous[this->next[newPosition]] = newPosition;
	}

	this->size++;
	return NULL_TELEM;
}


// Doubles the capacity of the storage arrays when more space is needed.
// Time Complexity, where n is the capacity:
// - Best Case: Theta(n) - Directly proportional to the current capacity due to the need to copy elements
// - Worst Case: Theta(n) - Directly proportional to the current capacity due to the need to copy elements
// - Total Complexity: Theta(n) - Directly proportional to the current capacity due to the need to copy elements
void Matrix::resize()
{
	this->capacity *= 2;
	Triple* newTriplets = new Triple[this->capacity];
	int* newNext = new int[this->capacity];
	int* newPrevious = new int[this->capacity];

	for (int i = 0; i < this->size; ++i)
	{
		newTriplets[i] = this->triplets[i];
		newNext[i] = this->next[i];
		newPrevious[i] = this->previous[i];
	}

	for (int i = this->size; i < this->capacity; ++i)
	{
		newTriplets[i] = NULL_TRIPLE;
		newNext[i] = i + 1;
		newPrevious[i] = -1;
	}
	newNext[this->capacity - 1] = -1;

	delete[] this->triplets;
	delete[] this->next;
	delete[] this->previous;

	this->triplets = newTriplets;
	this->next = newNext;
	this->previous = newPrevious;
	this->firstEmpty = this->size;
}

// Sets all values in the specified column to NULL_TELEM.
// Time Complexity, where n is the capacity:
// - Best Case: Theta(n) - Goes through all the elements
// - Worst Case: Theta(n) - Goes through all the elements
// - Total Complexity: Theta(n) - Goes through all the elements
void Matrix::clearColumn(int col)
{
	int current = this->first;
	while (current != -1)
	{
		if (this->triplets[current].first.second == col)
			this->triplets[current].second = NULL_TELEM;
		current = this->next[current];
	}
}
