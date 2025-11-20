#include "TestRemoveOccurrences.h"
#include <assert.h>
#include <exception>
#include "Bag.h"
#include "BagIterator.h"

void testRemoveOccurrences()
{
	Bag b;
	b.add(5);
	b.add(1);
	b.add(10);
	b.add(7);
	b.add(7);
	b.add(1);
	b.add(1);
	b.add(1);
	b.add(11);
	b.add(-3);
	assert(b.removeOccurrences(3, 1) == 3);
	assert(b.size() == 7);
	assert(b.removeOccurrences(3, 7) == 2);
	assert(b.size() == 5);
	assert(b.removeOccurrences(1, 11) == 1);
	assert(b.size() == 4);
	try {
		int i = b.removeOccurrences(-1, 10);
		assert(false);
	}
	catch (std::exception e) {
		assert(true);
	}
}