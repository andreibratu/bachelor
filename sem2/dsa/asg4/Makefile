CC=g++
L_FLAGS=-std=c++11 -c -Wall -Werror
B_FLAGS=-std=c++11 -Wall -Werror


short_test.o:
	$(CC) $(L_FLAGS) -o short_test.o tests/ShortTest.cpp


extended_test.o:
	$(CC) $(L_FLAGS) -o extended_test.o tests/ExtendedTest.cpp


sorted_set.o:
	$(CC) $(L_FLAGS) -o sorted_set.o sset/SortedSet.cpp


main.o:
	$(CC) $(L_FLAGS) -o main.o main.cpp


output: main.o sorted_set.o short_test.o extended_test.o
	$(CC) $(B_FLAGS) -o output.o main.o sorted_set.o short_test.o extended_test.o
	./output.o


.PHONY: clean

clean:
	find -name "*.o" | xargs rm
	find -name "*.h.gch" | xargs rm
