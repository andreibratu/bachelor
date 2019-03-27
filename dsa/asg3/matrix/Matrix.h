#ifndef MATRIX_H
#define MATRIX_H

#include "../dll/DLL.h"
#include "../iter/DLLIterator.h"
typedef int TElem;

#define NULL_TELEM 0



class Matrix {

private:

	typedef struct {
		int row;
		int col;
		TElem val;
	} Record;

	DLL<Record> list;
	int r;
	int c;
public:

	//constructor
	//throws exception if nrLines or nrCols is negative or zero
	// O(1)
	Matrix(int nrLines, int nrCols);



	//returns the number of lines
	// O(1)
	int nrLines() const;



	//returns the number of columns
	// O(1)
	int nrColumns() const;



	//returns the element from line i and column j (indexing starts from 0)
	//throws exception if (i,j) is not a valid position in the Matrix
	// O(N), the DLL must be traversed
	TElem element(int i, int j) const;



	//modifies the value from line i and column j
	//returns the previous value from the position
	//throws exception if (i,j) is not a valid position in the Matrix
	// O(N), the DLL must be traversed 
	TElem modify(int i, int j, TElem e);

};


#endif
