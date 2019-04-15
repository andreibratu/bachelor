CC=g++
BUILD_F=-g -Wall -Werror -std=c++11

output:
	$(CC) $(BUILD_F) -o output.o main.cpp ComparatorAscendingString.cpp ComparatorDescendingInteger.cpp
	./output.o

.PHONY: clean

clean:
	find -name "*.h.gch" | xargs rm
	find -name "*.o" | xargs rm
	find -name "*.gcda" | xargs rm
	find -name "*.gcno" | xargs rm
