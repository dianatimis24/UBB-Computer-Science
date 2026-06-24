#include "Matrix.h"
#include <exception>
using namespace std;

// Constructor
// Time Complexity:
// - Best Case: Theta(1) - Constant time operation regardless of input size
// - Worst Case: Theta(1) - Constant time operation regardless of input size
// - Total Complexity: Theta(1) - Constant time operation regardless of input size
Matrix::Matrix(int nrLines, int nrCols) {
	   
	this->nrLins = nrLines;
	this->nrCols = nrCols;
	this->head = nullptr;
}

// Returns the number of lines
// Time Complexity:
// - Best Case: Theta(1) - Direct access to a member variable
// - Worst Case: Theta(1) - Direct access to a member variable
// - Total Complexity: Theta(1) - Direct access to a member variable
int Matrix::nrLines() const {
	return this->nrLins;
}

// Returns the number of columns
// Time Complexity:
// - Best Case: Theta(1) - Direct access to a member variable
// - Worst Case: Theta(1) - Direct access to a member variable
// - Total Complexity: Theta(1) - Direct access to a member variable
int Matrix::nrColumns() const {
	return this->nrCols;
}

// Returns the element from line i and column j (indexing starts from 0)
// Throws exception if (i,j) is not a valid position in the Matrix
// Time Complexity:
// - Best Case: Theta(1) - The searched element is the head
// - Worst Case: Theta(n) - The element is either the last one checked, or is not found
// - Total Complexity: O(n) - Assumes elements are evenly distributed
TElem Matrix::element(int i, int j) const {
	if (i < 0 || i >= this->nrLins || j < 0 || j >= this->nrCols)
		throw std::exception();

	Node* node = this->head;
	if (node != nullptr)
	{
		while (node != nullptr)
		{
			if (node->triple.first.first == i && node->triple.first.second == j) {
				return node->triple.second;
			}
			node = node->next;
		}
	}
	return NULL_TELEM;
}

// Modifies the value from line i and column j
// Returns the previous value from the position
// Throws exception if (i,j) is not a valid position in the Matrix
// Time Complexity:
// - Best Case: Theta(1) - The searched element is the head or has to be inserted before the head
// - Worst Case: Theta(n) - The element is either the last one checked before modification, or is added as a new element
// - Total Complexity: O(n) - Assumes elements are evenly distributed
TElem Matrix::modify(int i, int j, TElem e) {
	if (i < 0 || i >= this->nrLins || j < 0 || j >= this->nrCols)
		throw std::exception();

	Node* node = this->head;
	if (node != nullptr)
	{
		while (node != nullptr)
		{
			if (node->triple.first.first == i && node->triple.first.second == j) {
				break;
			}
			node = node->next;
		}
	}

	TElem previousValue = NULL_TELEM;
	if (node != nullptr)
	{
		previousValue = node->triple.second;
		node->triple.second = e;
	}
	else
	{
		node = new Node({{i, j}, e});
		if (this->head == nullptr || (this->head->triple.first.first > i || (this->head->triple.first.first == i && this->head->triple.first.second > j)))
		{
			node->next = this->head;
			this->head = node;
		}
		else
		{
			Node* currentNode = this->head;
			while (currentNode->next != nullptr && (currentNode->next->triple.first.first < i || (currentNode->next->triple.first.first == i && currentNode->next->triple.first.second < j)))
				currentNode = currentNode->next;
			
			node->next = currentNode->next;
			currentNode->next = node;
		}
	}

	return previousValue;
}

// Destructor
// Time Complexity:
// - Best Case: Theta(n) - Each allocated node has to be deallocated
// - Worst Case: Theta(n) - Each allocated node has to be deallocated
// - Total Complexity: Theta(n) - Each allocated node has to be deallocated
Matrix::~Matrix()
{
	Node* currentNode = this->head;
	while (currentNode != nullptr) 
	{
		Node* nodeToBeDeleted = currentNode;
		currentNode = currentNode->next;
		delete nodeToBeDeleted;
	}
}

//returns the position(as a line–column pair) of the first occurrence of the given element
//if the element is not found, returns <-1, -1>
// Time Complexity: BC - Theta(1), WC - Theta(n), TC: O(n)
std::pair<int, int> Matrix::positionOf(TElem elem) const {
	Node* node = head;
	if (node != nullptr)
	{
		while (node != nullptr)
		{
			if (node->triple.second == elem)
				return node->triple.first;
			node = node->next;
		}
	}
	return { -1, -1 };
}


