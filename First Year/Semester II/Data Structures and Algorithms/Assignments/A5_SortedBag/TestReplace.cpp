#include "TestReplace.h"
#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <assert.h>
#include <iostream>

bool relationReplace(TComp e1, TComp e2) {
	return e1 <= e2;
}

void testReplace()
{
	std::cout << "Test Replace\n";
	SortedBag sb(relationReplace);
	sb.add(5);
	sb.add(6);
	sb.add(0);
	sb.add(5);
	sb.add(10);
	sb.add(8);
	sb.add(8);
	sb.add(8);
	sb.replace(8, 9);
	assert(sb.nrOccurrences(8) == 0);
	assert(sb.nrOccurrences(9) == 3);
	sb.replace(1, 7);
	assert(sb.nrOccurrences(7) == 0);
}