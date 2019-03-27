#include <assert.h>
#include "../matrix/Matrix.h"
#include "ExtendedTest.h"
#include <iostream>
#include <exception>

using namespace std;


void testCreate() {
	Matrix m(10, 10);
	assert(m.nrLines() == 10);
	assert(m.nrColumns() == 10);
	for (int i = 0; i < m.nrLines(); i++)
		for (int j = 0; j < m.nrColumns(); j++)
			assert(m.element(i, j) == 0);
}

void testModify() {
	Matrix m(10, 10);
	for (int j = 0; j < m.nrColumns(); j++)
		m.modify(4, j, 3);
	for (int i = 0; i < m.nrLines(); i++)
		for (int j = 0; j < m.nrColumns(); j++)
			if (i == 4)
				assert(m.element(i, j) == 3);
			else
				assert(m.element(i, j) == 0);
}

void testQuantity() {
	Matrix m(300, 300);
	for (int i = 0; i < m.nrLines(); i++)
		for (int j = 0; j < m.nrColumns(); j++)
			if (i % 2 == 0 && j % 2 == 0)
				m.modify(i, j, i*j);
			else
				if (j % 3 == 0)
					m.modify(i, j, i + j);
	for (int i = 0; i < m.nrLines(); i++)
		for (int j = 0; j < m.nrColumns(); j++)
			if (i % 2 == 0 && j % 2 == 0)
				assert(m.element(i, j) == i * j);
			else
				if (j % 3 == 0)
					assert(m.element(i, j) == i + j);
				else assert(m.element(i, j) == 0);
}

void testExceptions() {
	Matrix m(10, 10);
	try {
		m.element(-10, 0);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		m.modify(12, 0, 1);
		assert(false);
	}
	catch (exception&) {
		assert(true);
	}
	try {
		assert(m.nrLines());
	}
	catch (exception&) {
		assert(false);
	}
}



void testAllExtended() {
	testCreate();
	testModify();
	testQuantity();
	testExceptions();
}
