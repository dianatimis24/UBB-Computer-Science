#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

// Constructor
// Time Complexity:
// - Best Case: Theta(1) - Constant time operation regardless of input size
// - Worst Case: Theta(1) - Constant time operation regardless of input size
// - Total Complexity: Theta(1) - Constant time operation regardless of input size
Bag::Bag() {
	this->bagSize = 0;
	this->capacity = 10;
	this->elements = new TElem[this->capacity];
	this->frequencies = new int[this->capacity];
}

// Adds an element to the bag
// Time Complexity, where n is the size of the bag:
// - Best Case: Theta(1) - The element to be added is found on the first position
// - Worst Case: Theta(n) - The element to be added is found on the last position or is not found
// - Total Complexity: O(n) - Assumes elements are evenly distributed
void Bag::add(TElem elem) {
	if (this->bagSize == this->capacity)
		this->resize();

	bool found = false;
	int index = 0;
	while (index < this->bagSize) {
		if (this->elements[index] == elem) {
			this->frequencies[index]++;
			found = true;
			break;
		}
		index++;
	}
	if (!found) {
		this->elements[this->bagSize] = elem;
		this->frequencies[this->bagSize] = 1;
		this->bagSize++;
	}
}

// Removes one occurence of an element from a bag
// Returns true if an element was removed, false otherwise (if e was not part of the bag)
// Time Complexity, where n is the size of the bag:
// - Best Case: Theta(1) - The element to be removed is on the first position
// - Worst Case: Theta(n) - The element to be removed is on the last position or is not found
// - Total Complexity: O(n) - Assumes elements are evenly distributed
bool Bag::remove(TElem elem) {
	int index = 0;
	while (index < this->bagSize) {
		if (this->elements[index] == elem) {
			if (this->frequencies[index] > 1)
				this->frequencies[index]--;
			else {
				this->elements[index] = this->elements[this->bagSize - 1];
				this->frequencies[index] = this->frequencies[this->bagSize - 1];
				this->bagSize--;
			}
			return true;
		}
		index++;
	}
	return false; 
}

// Checks if an element appearch is the bag
// Time Complexity, where n is the size of the bag:
// - Best Case: Theta(1) - The first element checked is the target
// - Worst Case: Theta(n) - The element is either not found or is the last one checked
// - Total Complexity: O(n) - Assumes elements are evenly distributed
bool Bag::search(TElem elem) const {
	int index = 0;
	while (index < this->bagSize) {
		if (this->elements[index] == elem)
			return true;
		index++;
	}
	return false; 
}

// Returns the number of occurrences for an element in the bag
// Time Complexity, where n is the size of the bag:
// - Best Case: Theta(1) - The first element checked is the target
// - Worst Case: Theta(n) - The element is either not found or is the last one checked
// - Total Complexity: O(n) - Assumes elements are evenly distributed
int Bag::nrOccurrences(TElem elem) const {
	int index = 0, count = 0;
	while (index < this->bagSize) {
		if (this->elements[index] == elem) {
			count = this->frequencies[index];
			break;
		}
		index++;
	}
	return count; 
}

// Returns the number of elements from the bag
// Time Complexity, where n is the size of the bag:
// - Best Case: Theta(n) - The entire array of frequencies has to be parsed
// - Worst Case: Theta(n) - The entire array of frequencies has to be parsed
// - Total Complexity: Theta(n) - The entire array of frequencies has to be parsed
int Bag::size() const {
	int index = 0, count = 0;
	while (index < this->bagSize) {
		count += this->frequencies[index];
		index++;
	}
	return count;
}

// Checks if the bag is empty
// Time Complexity:
// - Best Case: Theta(1) - Direct access to a member variable
// - Worst Case: Theta(1) - Direct access to a member variable
// - Total Complexity: Theta(1) - Direct access to a member variable
bool Bag::isEmpty() const {
	return this->bagSize == 0;
}

// Returns an iterator for this bag
BagIterator Bag::iterator() const {
	return BagIterator(*this);
}

// Destructor
// Time Complexity:
// - Best Case: Theta(1) - Deletion of the array is a constant time operation
// - Worst Case: Theta(1) - Deletion of the array is a constant time operation
// - Total Complexity: Theta(1) - Deletion of the array is a constant time operation
Bag::~Bag() {
	delete[] this->elements;
	delete[] this->frequencies;
}

// Doubles the capacity of the storage arrays when more space is needed.
// Time Complexity, where n is the size of the bag:
// - Best Case: Theta(n) - Directly proportional to the current size due to the need to copy elements
// - Worst Case: Theta(n) - Directly proportional to the current size due to the need to copy elements
// - Total Complexity: Theta(n) - Directly proportional to the current size due to the need to copy elements
void Bag::resize() {
	TElem* newElements = new TElem[2 * this->capacity];
	int* newFrequencies = new int[2 * this->capacity];
	for (int i = 0; i < this->capacity; i++) {
		newElements[i] = this->elements[i];
		newFrequencies[i] = this->frequencies[i];
	}
	for (int i = 0; i < this->capacity; i++) {
		newElements[i + this->capacity] = 0;
		newFrequencies[i + this->capacity] = 0;
	}
	delete[] this->elements;
	delete[] this->frequencies;
	this->elements = newElements;
	this->frequencies = newFrequencies;
	this->capacity *= 2;
}

// Removes 'nr' occurrences of the element 'elem' from the bag. 
// If the element occurs fewer times than 'nr', all occurrences are removed.
// Returns the number of removed occurrences.
// Throws an exception if 'nr' is negative.
int Bag::removeOccurrences(int nr, TElem elem)
{
	if (nr < 0)
		throw exception();
	int index = 0, removedOccurrences = 0;
	while (index < this->bagSize) {
		if (this->elements[index] == elem) {
			if (this->frequencies[index] > nr) {
				removedOccurrences = nr;
				this->frequencies[index] -= nr;
				break;
			}
			else {
				removedOccurrences = this->frequencies[index];
				this->elements[index] = this->elements[this->bagSize - 1];
				this->frequencies[index] = this->frequencies[this->bagSize - 1];
				this->bagSize--;
				break;
			}
		}
		++index;
	}
	return removedOccurrences;
}

