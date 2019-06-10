CC=g++
ARGS=-std=c++11 -g -c -Wall -Werror -Wfatal-errors
EXECARGS=-std=c++11 -g -Wall -Werror -Wfatal-errors

vertex.o: iterator.o
	$(CC) $(ARGS) -o vertex.o implementations/vertex.cpp

graph.o: vertex.o iterator.o
	$(CC) $(ARGS) -o graph.o implementations/graph.cpp

iterator.o:
	$(CC) $(ARGS) -o iterator.o implementations/iterator.cpp

generator.o: graph.o
	$(CC) $(ARGS) -o generator.o implementations/generator.cpp

test.o: vertex.o graph.o iterator.o generator.o
	$(CC) $(ARGS) -o test.o test.cpp

test: test.o vertex.o graph.o iterator.o generator.o test.o generator.o
	$(CC) $(EXECARGS) -o output.o vertex.o graph.o iterator.o generator.o test.o
	./output.o
