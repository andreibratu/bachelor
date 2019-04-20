CC=g++
ARGS=-std=c++11 -g -c -Wall -Werror -Wfatal-errors
EXECARGS=-std=c++11 -g -Wall -Werror -Wfatal-errors
GRAPH_PATH=../asg1/graph_c/implementations

vertex.o:
	$(CC) $(ARGS) -o vertex.o $(GRAPH_PATH)/vertex.cpp

graph.o:
	$(CC) $(ARGS) -o graph.o $(GRAPH_PATH)/graph.cpp

iterator.o:
	$(CC) $(ARGS) -o iterator.o $(GRAPH_PATH)/iterator.cpp

generator.o:
	$(CC) $(ARGS) -o generator.o $(GRAPH_PATH)/generator.cpp

bfs.o:
	$(CC) $(ARGS) -o bfs.o BFS.cpp

test.o:
	$(CC) $(ARGS) -o test.o ./test.cpp

test: test.o vertex.o graph.o iterator.o generator.o test.o generator.o bfs.o
	$(CC) $(EXECARGS) -o output.o vertex.o graph.o iterator.o generator.o test.o bfs.o
	./output.o


.PHONY: clean

clean:
	find -name "*.o" | xargs rm
	find -name "*.h.gch" | xargs rm
