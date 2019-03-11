MedicationTest: model/Medication.c tests/MedicationTest.c
	gcc -o MedicationTest -Wall -Werror model/Medication.c tests/MedicationTest.c
	./MedicationTest
	valgrind ./MedicationTest
	rm MedicationTest

MedicationVectorTest: model/Medication.c ds/MedicationVector.c tests/MedicationVectorTest.c
	gcc -o MedicationVectorTest -Wall -Werror model/Medication.c ds/MedicationVector.c tests/MedicationVectorTest.c
	./MedicationVectorTest
	valgrind ./MedicationVectorTest
	rm MedicationVectorTest
