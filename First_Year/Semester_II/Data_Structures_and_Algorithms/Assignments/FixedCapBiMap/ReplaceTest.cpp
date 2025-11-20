#include "ReplaceTest.h"
#include <assert.h>
#include "FixedCapBiMap.h"
#include "FixedCapBiMapIterator.h"
#include <utility>

void testReplace() {
	FixedCapBiMap m(10);
	m.add(5, 5);
	m.add(1, 111);
	m.add(10, 110);
	m.add(7, 7);
	m.add(1, 1);
	m.add(10, 10);
	m.add(-3, -3);

	m.replace(7, 7, 3);
	m.replace(10, 12, 11);
	m.replace(2, 7, 2);
	std::pair<TValue, TValue> res1 = m.search(7), res2 = m.search(10);
	std::pair<TValue, TValue> res3(NULL_TVALUE, NULL_TVALUE);;
	assert(res1.first == 3);
	assert(res2.first != 11 && res2.second != 11);
	assert(m.search(2) == res3);
}