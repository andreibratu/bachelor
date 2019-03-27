CC=g++
LINK_F=-std=c++11 -c -Wall
BUILD_F=-std=c++11 -Wall


extended_test.o:
	$(CC) $(LINK_F) -o extended_test.o tests/ExtendedTest.cpp


short_test.o:
	$(CC) $(LINK_F) -o short_test.o tests/ShortTest.cpp


matrix.o:
	$(CC) $(LINK_F) -o matrix.o matrix/Matrix.cpp


main.o:
	$(CC) $(LINK_F) -o main.o main.cpp


output: extended_test.o short_test.o main.o matrix.o
	$(CC) $(BUILD_F) -o output.o main.o extended_test.o short_test.o matrix.o
	./output.o


. PHONY: clean

clean:
	find -name "*.h.gch" | xargs rm
	find -name "*.o" | xargs rm
