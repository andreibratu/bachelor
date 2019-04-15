CC=g++
LINK_F=-std=c++11 -c -Wall
BUILD_F=-std=c++11 -Wall


extended_test.o:
	$(CC) $(LINK_F) -o extended_test.o tests/ExtendedTest.cpp


short_test.o:
	$(CC) $(LINK_F) -o short_test.o tests/ShortTest.cpp


matrix.o:
	$(CC) $(LINK_F) -o matrix.o matrix/Matrix.cpp


matrix_iterator.o:
	$(CC) $(LINK_F) -o matrix_iterator.o iter/MatrixIterator.cpp


main.o:
	$(CC) $(LINK_F) -o main.o main.cpp


output: extended_test.o short_test.o main.o matrix.o matrix_iterator.o
	$(CC) $(BUILD_F) -o output.o main.o extended_test.o short_test.o matrix_iterator.o matrix.o
	./output.o


. PHONY: clean

clean:
	find -name "*.o" | xargs rm
	find -name "*.h.gch" | xargs rm
