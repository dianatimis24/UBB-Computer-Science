#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;

// Time Complexity:
// Best Case: Theta(1); Worst Case: Theta(1); Average Case: Theta(1)
BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->currentPosition = 0;
	this->currentFrequency = 1;
}

// Time Complexity:
// Best Case: Theta(1); Worst Case: Theta(1); Average Case: Theta(1)
void BagIterator::first() {
	this->currentPosition = 0;
	this->currentFrequency = 1;
}

// Time Complexity:
// Best Case: Theta(1); Worst Case: Theta(1); Average Case: Theta(1)
void BagIterator::next() {
	if (this->currentPosition == this->bag.bagSize)
		throw exception();
	if (this->currentFrequency < this->bag.frequencies[this->currentPosition])
		this->currentFrequency++;
	else {
		this->currentPosition++;
		this->currentFrequency = 1;
	}
}

// Time Complexity:
// Best Case: Theta(1); Worst Case: Theta(1); Average Case: Theta(1)
bool BagIterator::valid() const {
	return this->currentPosition < this->bag.bagSize;
}

// Time Complexity:
// Best Case: Theta(1); Worst Case: Theta(1); Average Case: Theta(1)
TElem BagIterator::getCurrent() const
{
	if (this->currentPosition == this->bag.bagSize)
		throw exception();
	return this->bag.elements[this->currentPosition];
}
