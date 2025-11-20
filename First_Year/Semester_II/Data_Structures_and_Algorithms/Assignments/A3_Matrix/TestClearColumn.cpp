#include "TestClearColumn.h"
#include <assert.h>
#include "Matrix.h"

using namespace std;

void testClearColumn()
{
	Matrix m(4, 4);
	m.modify(1, 1, 5);
	m.modify(2, 1, 7);
	m.modify(3, 1, 8);
	m.modify(1, 2, 11);
	m.modify(2, 2, 4);
	m.modify(1, 3, 5);
	m.modify(3, 3, 20);
	m.clearColumn(1);
	assert(m.element(1, 1) == NULL_TELEM);
	assert(m.element(2, 1) == NULL_TELEM);
	assert(m.element(3, 1) == NULL_TELEM);
	assert(m.element(3, 3) == 20);
	assert(m.element(1, 2) == 11);
	assert(m.element(2, 2) == 4);
	assert(m.element(1, 3) == 5);

}
