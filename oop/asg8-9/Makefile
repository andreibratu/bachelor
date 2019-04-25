CC=g++
LINK_COVERAGE_F=-c -g -O0 --coverage -Wall -Werror -std=c++11
LINK_F=-c -g --coverage -Wall -Werror -std=c++11
BUILD_F=-g --coverage -Wall -Werror -std=c++11


movie.o:
	$(CC) $(LINK_COVERAGE_F) -o movie.o model/Movie.cpp


repo.o:
	$(CC) $(LINK_COVERAGE_F) -o repo.o repo/Repository.cpp


admin_controller.o:
	$(CC) $(LINK_COVERAGE_F) -o admin_controller.o controller/AdminController.cpp


user_controller.o:
	$(CC) $(LINK_COVERAGE_F) -o user_controller.o controller/UserController.cpp


movie_test.o:
	$(CC) $(LINK_F) -o movie_test.o tests/MovieTest.cpp


repo_test.o:
	$(CC) $(LINK_F) -o repo_test.o tests/RepositoryTest.cpp


admin_test.o:
	$(CC) $(LINK_F) -o admin_test.o tests/AdminControllerTest.cpp


user_test.o:
	$(CC) $(LINK_F) -o user_test.o tests/UserControllerTest.cpp


ui.o:
		$(CC) $(LINK_F) -o ui.o ui/AdminUI.cpp


user_ui.o:
	$(CC) $(LINK_F) -o user_ui.o ui/UserUI.cpp


main_test.o:
	$(CC) $(LINK_F) -o main_test.o tests/Test.cpp


main.o:
		$(CC) $(LINK_F) -o main.o main.cpp


TestMovie: movie.o movie_test.o
	$(CC) $(BUILD_F) -o TestMovie.o movie.o movie_test.o
	./TestMovie.o
	gcov movie.gcno


TestRepo: movie.o repo.o repo_test.o
	$(CC) $(BUILD_F) -o TestRepository.o repo_test.o repo.o movie.o
	./TestRepository.o
	gcov repo.gcno


TestAdmin: movie.o repo.o admin_controller.o admin_test.o
	$(CC) $(BUILD_F) -o TestAdmin.o movie.o repo.o admin_controller.o admin_test.o
	./TestAdmin.o
	gcov admin_controller.gcno


TestUser: movie.o repo.o user_controller.o user_test.o
	$(CC) $(BUILD_F) -o TestUser.o movie.o repo.o user_controller.o user_test.o
	./TestUser.o
	gcov user_controller.gcno


Build: movie.o repo.o admin_controller.o ui.o main.o user_ui.o user_controller.o
	$(CC) $(BUILD_F) -o output.o movie.o repo.o admin_controller.o ui.o main.o user_ui.o user_controller.o


.PHONY: clean

clean:
	ls -p | grep -v / | grep -v "main.cpp" | grep -v "Makefile" | grep -v ".csv" | xargs rm
	find "*.h.gch" | xargs rm

