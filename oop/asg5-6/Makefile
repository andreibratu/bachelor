CC=g++
LFLAGS=-c -g -Wall -Werror -std=c++11
TFLAGS=-g -Wall -Werror -std=c++11


movie.o:
	$(CC) $(LFLAGS) -o movie.o model/Movie.cpp


repo.o:
	$(CC) $(LFLAGS) -o repo.o repo/Repository.cpp


admin_controller.o:
	$(CC) $(LFLAGS) -o admin_controller.o controller/AdminController.cpp


movie_test.o:
	$(CC) $(LFLAGS) -o movie_test.o tests/MovieTest.cpp


vector_test.o:
	$(CC) $(LFLAGS) -o vector_test.o tests/VectorTest.cpp


repository_test.o:
	$(CC) $(LFLAGS) -o repository_test.o tests/RepositoryTest.cpp


ui.o:
		$(CC) $(LFLAGS) -o ui.o ui/AdminUI.cpp


main.o:
		$(CC) $(LFLAGS) -o main.o main.cpp


TestVector: vector_test.o
	$(CC) $(TFLAGS) -o VectorTest.o vector_test.o
	./VectorTest.o
	valgrind ./VectorTest.o


TestMovie: movie_test.o movie.o
	$(CC) $(TFLAGS) -o MovieTest.o movie_test.o movie.o
	./MovieTest.o
	valgrind ./MovieTest.o


TestRepository: repo.o movie.o repository_test.o
	$(CC) $(TFLAGS) -o RepositoryTest.o repo.o movie.o repository_test.o
	./RepositoryTest.o
	valgrind ./RepositoryTest.o


Build: movie.o repo.o admin_controller.o ui.o main.o
	$(CC) $(TFLAGS) -o output.o movie.o repo.o admin_controller.o ui.o main.o
	./output.o

.PHONY: clean

clean:
	find -name "*.o" | xargs rm
	find -name "*.h.gch" | xargs rm
