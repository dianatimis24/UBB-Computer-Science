#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

/// Best Case: Theta(1), Worst Case: Theta(n), Total Complexity: O(n)
void SortedBagIterator::inOrderTraversal(BSTNode* node) {
	if (node == nullptr)
		return;
	this->inOrderTraversal(node->left);

	for (int i = 0; i < node->frequency; ++i)
		this->elements[this->numberOfElements++] = node->element;

	this->inOrderTraversal(node->right);
}

/// Best Case: Theta(1), Worst Case: Theta(n), Total Complexity: O(n)
SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	int capacity = this->bag.bagSize;
	this->elements = new TComp[capacity];
	this->currentIndex = 0;
	this->numberOfElements = 0;
	this->inOrderTraversal(this->bag.root);
}

/// Best Case: Theta(1), Worst Case: Theta(1), Total Complexity: Theta(1)
TComp SortedBagIterator::getCurrent() {
	if (!this->valid())
		throw exception();
	return this->elements[this->currentIndex];
}

/// Best Case: Theta(1), Worst Case: Theta(1), Total Complexity: Theta(1)
bool SortedBagIterator::valid() {
	return this->currentIndex < this->numberOfElements;
}

/// Best Case: Theta(1), Worst Case: Theta(1), Total Complexity: Theta(1)
void SortedBagIterator::next() {
	if (!this->valid())
		throw exception();
	this->currentIndex++;
}

/// Best Case: Theta(1), Worst Case: Theta(1), Average Case: Theta(1)
void SortedBagIterator::first() {
	this->currentIndex = 0;
}

/// Best Case: Theta(1), Worst Case: Theta(1), Total Complexity: Theta(1)
SortedBagIterator::~SortedBagIterator() {
	delete[] this->elements;
}

