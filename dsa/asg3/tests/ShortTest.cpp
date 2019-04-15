#include <assert.h>
#include "../matrix/Matrix.h"

using namespace std;

void testAll() {
	Matrix m(4, 4);
	assert(m.nrLines() == 4);
	assert(m.nrColumns() == 4);
	m.modify(1, 1, 5);
	assert(m.element(1, 1) == 5);
	m.modify(1, 1, 6);
	assert(m.element(1, 2) == 0);
	int i = 0;
	MatrixIterator it = m.iterator();
	for(; it.valid() ; it.next()) {
		i++;
	}
	assert(i==2);
}
