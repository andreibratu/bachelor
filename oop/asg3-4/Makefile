CC=gcc
CFLAGS=-Wall -Werror


MedicationTest: model/Medication.c tests/MedicationTest.c
	gcc -o MedicationTest -Wall -Werror model/Medication.c tests/MedicationTest.c
	./MedicationTest
	valgrind ./MedicationTest
	rm ./MedicationTest

VectorTest: model/Medication.c ds/Vector.c tests/VectorTest.c
	gcc -o MedicationVector model/Medication.c ds/Vector.c tests/VectorTest.c
	./MedicationVector
	valgrind ./MedicationVector
	rm ./MedicationVector

MedicationRepositoryTest: repo/MedicationRepository.c ds/MedicationVector.c model/Medication.c
	gcc -o MedicationRepositoryTest -Wall tests/MedicationRepositoryTest.c model/Medication.c ds/MedicationVector.c repo/MedicationRepository.c
	./MedicationRepositoryTest
	valgrind --leak-check=full ./MedicationRepositoryTest
	rm ./MedicationRepositoryTest

MedicationControllerTest: model/Medication.c ds/MedicationVector.c repo/MedicationRepository.c controller/MedicationController.c tests/MedicationControllerTest.c
	gcc -o MedicationControllerTest -Wall -Werror tests/MedicationControllerTest.c model/Medication.c ds/MedicationVector.c controller/MedicationController.c repo/MedicationRepository.c
	./MedicationControllerTest
	valgrind ./MedicationControllerTest
	rm ./MedicationControllerTest

Build: model/Medication.c ds/MedicationVector.c repo/MedicationRepository.c controller/MedicationController.c ui/ui.c main.c
	gcc -o main -Wall -Werror model/Medication.c ds/MedicationVector.c repo/MedicationRepository.c controller/MedicationController.c ui/ui.c main.c
	./main
	rm ./main
