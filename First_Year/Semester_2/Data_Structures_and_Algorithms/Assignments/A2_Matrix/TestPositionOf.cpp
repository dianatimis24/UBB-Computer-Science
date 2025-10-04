#include "TestPositionOf.h"
#include <assert.h>
#include <utility>
#include "Matrix.h"

void testPositionOf() {
	std::cout << "Test positionOf()\n";
	Matrix m(4, 4);
	m.modify(1, 1, 5);
	m.modify(2, 1, 2);
	m.modify(1, 3, 6);
	m.modify(3, 2, 7);
	
	assert(m.positionOf(5).first == 1 && m.positionOf(5).second == 1);
	assert(m.positionOf(1).first == -1 && m.positionOf(1).second == -1);
	assert(m.positionOf(7).first == 3 && m.positionOf(7).second == 2);
	assert(m.positionOf(4).first == -1 && m.positionOf(4).second == -1);
}