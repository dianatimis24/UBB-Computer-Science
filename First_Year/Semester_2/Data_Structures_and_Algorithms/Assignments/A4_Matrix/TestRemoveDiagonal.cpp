#include "TestRemoveDiagonal.h"
#include <assert.h>
#include <iostream>
#include "Matrix.h"

void testRemoveDiagonal()
{
	std::cout << "Test Remove Diagonal\n";
	Matrix m(4, 4);
	m.modify(1, 1, 5);
	m.modify(2, 2, 22);
	m.modify(0, 0, 1);
	m.modify(3, 3, 9);
	m.modify(2, 3, 10);
	m.modify(3, 1, 3);
	m.removeDiagonal();
	assert(m.element(1, 1) == NULL_TELEM);
	assert(m.element(2, 2) == NULL_TELEM);
	assert(m.element(0, 0) == NULL_TELEM);
	assert(m.element(3, 3) == NULL_TELEM);
	assert(m.element(2, 3) == 10);
	assert(m.element(3, 1) == 3);
}
