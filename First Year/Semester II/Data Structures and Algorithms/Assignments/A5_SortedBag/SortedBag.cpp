#include "SortedBag.h"
#include "SortedBagIterator.h"

/// Best Case: Theta(1), Worst Case: Theta(1), Total Complexity: Theta(1)
SortedBag::SortedBag(Relation r) {
	this->relation = r;
	this->root = nullptr;
	this->bagSize = 0;
}

/// Best Case: Theta(1), Worst Case: Theta(n), Total Complexity: O(log(n)) - number of nodes of the BST
void SortedBag::add(TComp e) {
	BSTNode* currentNode = this->root;
	if (currentNode == nullptr)
	{
		this->root = new BSTNode;
		this->initializeNode(this->root, e);
		this->bagSize++;
		return;
	}

	while (currentNode != nullptr) {
		if (currentNode->element == e) {
			currentNode->frequency++;
			this->bagSize++;
			return;
		}
		if (this->relation(e, currentNode->element)) {
			if (currentNode->left == nullptr) {
				currentNode->left = new BSTNode;
				this->initializeNode(currentNode->left, e);
				this->bagSize++;
				return;
			}
			else
				currentNode = currentNode->left;
		}
		else {
			if (currentNode->right == nullptr) {
				currentNode->right = new BSTNode;
				this->initializeNode(currentNode->right, e);
				this->bagSize++;
				return;
			}
			else
				currentNode = currentNode->right;
		}
	}
}

/// Best Case: Theta(1), Worst Case: Theta(n), Total Complexity: O(log(n)) - number of nodes of the BST
bool SortedBag::remove(TComp e) {
	BSTNode *currentNode = this->root, *parentNode = nullptr;
	while (currentNode != nullptr) {
		if (currentNode->element == e) {
			if (currentNode->frequency > 1) {
				currentNode->frequency--;
				this->bagSize--;
				return true;
			}
			else {
				if (currentNode->left == nullptr && currentNode->right == nullptr) {
					if (parentNode == nullptr)
						this->root = nullptr;
					else {
						if (parentNode->left == currentNode)
							parentNode->left = nullptr;
						else
							parentNode->right = nullptr;
					}
					delete currentNode;
					this->bagSize--;
					return true;
				}

				if (currentNode->left == nullptr || currentNode->right == nullptr) {
					if (currentNode->left == nullptr) {
						if (parentNode == nullptr)
							this->root = currentNode->right;
						else {
							if (parentNode->left == currentNode)
								parentNode->left = currentNode->right;
							else
								parentNode->right = currentNode->right;
						}
					}
					else {
						if (parentNode == nullptr)
							this->root = currentNode->left;
						else {
							if (parentNode->left == currentNode)
								parentNode->left = currentNode->left;
							else
								parentNode->right = currentNode->left;
						}
					}
					delete currentNode;
					this->bagSize--;
					return true;
				}

				BSTNode *minNode = currentNode->right;
				BSTNode *minParentNode = currentNode;
				while (minNode->left != nullptr) {
					minParentNode = minNode;
					minNode = minNode->left;
				}

				currentNode->element = minNode->element;
				currentNode->frequency = minNode->frequency;
				if (minParentNode->left == minNode) {
					minParentNode->left = minNode->right;
				}
				else {
					minParentNode->right = minNode->right;
				}
				delete minNode;
				this->bagSize--;
				return true;
			}
		}
		if (this->relation(e, currentNode->element)) {
			parentNode = currentNode;
			currentNode = currentNode->left;
		}
		else {
			parentNode = currentNode;
			currentNode = currentNode->right;
		}
	}
	return false;
}

/// Best Case: Theta(1), Worst Case: Theta(n), Total Complexity: O(log(n)) - number of nodes of the BST
bool SortedBag::search(TComp e) const {
	BSTNode* currentNode = root;
	while (currentNode != nullptr) {
		if (currentNode->element == e)
			return true;
		if (this->relation(e, currentNode->element))
			currentNode = currentNode->left;
		else
			currentNode = currentNode->right;
	}
	return false;
}

/// Best Case: Theta(1), Worst Case: Theta(n), Total Complexity: O(log(n)) - number of nodes of the BST
int SortedBag::nrOccurrences(TComp e) const {
	BSTNode* currentNode = root;
	while (currentNode != nullptr) {
		if (currentNode->element == e)
			return currentNode->frequency;
		if (this->relation(e, currentNode->element))
			currentNode = currentNode->left;
		else
			currentNode = currentNode->right;
	}
	return 0;
}

/// Best Case: Theta(1), Worst Case: Theta(1), Total Complexity: Theta(1)
int SortedBag::size() const {
	return this->bagSize;
}

/// Best Case: Theta(1), Worst Case: Theta(1), Total Complexity: Theta(1)
bool SortedBag::isEmpty() const {
	return this->bagSize == 0;
}

/// Best Case: Theta(1), Worst Case: Theta(1), Total Complexity: Theta(1)
SortedBagIterator SortedBag::iterator() const {
	return SortedBagIterator(*this);
}

/// Best Case: Theta(n), Worst Case: Theta(n), Total Complexity: Theta(n) - number of nodes of the BST
SortedBag::~SortedBag() {
	this->recursiveDestructor(this->root);
}

/// Best Case: Theta(1), Worst Case: Theta(n), Total Complexity: O(n) - number of nodes of the BST
void SortedBag::recursiveDestructor(BSTNode* node) {
	if (node == nullptr)
		return;
	this->recursiveDestructor(node->left);
	this->recursiveDestructor(node->right);
	delete node;
}

/// Best Case: Theta(1), Worst Case: Theta(1), Total Complexity: Theta(1)
void SortedBag::initializeNode(BSTNode* node, TComp e) {
	node->element = e;
	node->frequency = 1;
	node->left = nullptr;
	node->right = nullptr;
}


/// Best Case: Theta(1), Worst Case: Theta(n), Total Complexity: O(log(n)) - number of nodes of the BST
void SortedBag::replace(TComp oldElem, TComp newElem)
{
	BSTNode* currentNode = root;
	while (currentNode != nullptr) {
		if (currentNode->element == oldElem)
		{
			currentNode->element = newElem;
			return;
		}
		if (this->relation(oldElem, currentNode->element))
			currentNode = currentNode->left;
		else
			currentNode = currentNode->right;
	}
}