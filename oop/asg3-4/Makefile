MedicationTest: model/Medication.c tests/MedicationTest.c
	gcc -o MedicationTest -Wall -Werror model/Medication.c tests/MedicationTest.c
	./MedicationTest
	valgrind ./MedicationTest
	rm ./MedicationTest

MedicationVectorTest: model/Medication.c ds/MedicationVector.c tests/MedicationVectorTest.c
	gcc -o MedicationVectorTest -Wall -Werror model/Medication.c ds/MedicationVector.c tests/MedicationVectorTest.c
	./MedicationVectorTest
	valgrind ./MedicationVectorTest
	rm ./MedicationVectorTest

MedicationRepositoryTest: repo/MedicationRepository.c ds/MedicationVector.c model/Medication.c
	gcc -o MedicationRepositoryTest -Wall -Werror tests/MedicationRepositoryTest.c model/Medication.c ds/MedicationVector.c repo/MedicationRepository.c
	./MedicationRepositoryTest
	valgrind ./MedicationRepositoryTest
	rm ./MedicationRepositoryTest
