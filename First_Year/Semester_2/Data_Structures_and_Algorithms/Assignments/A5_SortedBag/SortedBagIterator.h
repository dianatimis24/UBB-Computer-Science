#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	TComp* elements;
	int currentIndex, numberOfElements;

	SortedBagIterator(const SortedBag& b);

	void inOrderTraversal(BSTNode* node);

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
	~SortedBagIterator();
};

