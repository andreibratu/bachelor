CC=gcc
LFLAGS=-Wall -c -g
BFLAGS=-Wall -g
VFLAGS=--leak-check=full


medication.o:
	$(CC) -o medication.o $(LFLAGS) model/Medication.c


vector.o:
	$(CC) -o vector.o $(LFLAGS) ds/Vector.c


repository.o:
	$(CC) -o repository.o $(LFLAGS) repo/MedicationRepository.c


controller.o:
	$(CC) -o controller.o $(LFLAGS) controller/MedicationController.c


action.o:
	$(CC) -o action.o $(LFLAGS) model/Action.c


history.o:
	$(CC) -o history.o $(LFLAGS) history/HistoryController.c


ui.o:
	$(CC) -o ui.o $(LFLAGS) ui/UI.c


medication_test.o:
	$(CC) -o medication_test.o $(LFLAGS) tests/MedicationTest.c


vector_test.o:
	$(CC) -o vector_test.o $(LFLAGS) tests/VectorTest.c


repository_test.o:
	$(CC) -o repository_test.o $(LFLAGS) tests/MedicationRepositoryTest.c


controller_test.o:
	$(CC) -o controller_test.o $(LFLAGS) tests/MedicationControllerTest.c


history_test.o:
	$(CC) -o history_test.o $(LFLAGS) tests/HistoryControllerTest.c


main.o:
	$(CC) -o main.o $(LFLAGS) main.c



MedicationTest: medication.o vector.o medication_test.o
	$(CC) -o MedicationTest.o $(BFLAGS) medication.o vector.o medication_test.o
	./MedicationTest.o
	valgrind $(VFLAGS) ./MedicationTest.o


VectorTest: medication.o vector.o vector_test.o
	$(CC) -o VectorTest.o $(BFLAGS) medication.o vector.o vector_test.o
	./VectorTest.o
	valgrind $(VFLAGS) ./VectorTest.o


RepositoryTest: medication.o vector.o repository.o repository_test.o
	$(CC) -o RepositoryTest.o $(BFLAGS) medication.o vector.o repository.o repository_test.o
	./RepositoryTest.o
	valgrind $(VFLAGS) ./RepositoryTest.o


ControllerTest: medication.o vector.o repository.o controller.o history.o controller_test.o action.o
	$(CC) $(BFLAGS) -o ControllerTest.o medication.o vector.o action.o repository.o history.o controller.o controller_test.o
	./ControllerTest.o
	valgrind $(VFLAGS) ./ControllerTest.o


HistoryTest: medication.o vector.o repository.o controller.o history.o action.o history_test.o
	$(CC) $(BFLAGS) -o HistoryTest.o medication.o vector.o action.o repository.o history.o controller.o history_test.o
	./HistoryTest.o
	valgrind $(VFLAGS) ./HistoryTest.o


Build: medication.o vector.o repository.o controller.o history.o ui.o action.o main.o
	$(CC) $(BFLAGS) -o output medication.o vector.o repository.o controller.o history.o ui.o action.o main.o
	./output


.PHONY: clean

clean:
	rm *.o
