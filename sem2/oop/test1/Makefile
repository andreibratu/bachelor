player.o:
	g++ -std=c++11 -Wall -Werror -c -o player.o Player.cpp

repo.o: player.o
	g++ -std=c++11 -Wall -Werror -c -o repo.o Repository.cpp

controller.o: repo.o player.o
	g++ -std=c++11 -Wall -Werror -c -o controller.o Controller.cpp

ui.o: controller.o repo.o player.o
	g++ -std=c++11 -Wall -Werror -c -o ui.o UI.cpp

main.o:
	g++ -std=c++11 -Wall -Werror -c -o main.o main.cpp

test.o:
	g++ -std=c++11 -Wall -Werror -c -o test.o tests.cpp

output: player.o repo.o controller.o ui.o main.o
	g++ -std=c++11 -Wall -Werror -o output.o Controller.cpp Repository.cpp Player.cpp UI.cpp main.cpp
	./output.o

output_test: test.o player.o repo.o controller.o
	g++ -std=c++11 -Wall -Werror -o output_test.o test.o player.o repo.o controller.o
	./output_test.o

.PHONY: clean

clean:
	find -name "*.o" | xargs rm
	find -name "*.h.gch" | xargs rm
