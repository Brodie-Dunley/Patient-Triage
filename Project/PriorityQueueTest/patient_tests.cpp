/*
 *
 *  DO NOT MODIFY THIS FILE
 *
 */

#include "pch.h"
#include "test_config.h"
#include "Patient.h"

std::vector<Patient> generate_ordered_patient_set();

//checks the state of the queue after default construction
#if TEST_PATIENT_CONSTRUCTOR
TEST(Patient, Constructor) {
	const std::string name = "Patient Name";
	const Patient patient(name);

	//verify the name was set
	ASSERT_EQ(patient.get_name(), name);
}
#endif

#if TEST_PATIENT_ADD_AILMENT
TEST(Patient, AddAilment) {
	//create a patient
	const std::string name = "Patient Name";
	Patient patient(name);

	//create list of ailments for the patient
	const std::vector<Ailment> ailments = {
		Ailment("Heart Attack", 10, 10, 0),
		Ailment("Stubbed Toe", 1, 1, 0)
	};

	//add ailments to patient
	for (const auto& ailment : ailments)
	{
		patient.add_ailment(ailment);
	}

	//check that all the ailments are on the patient
	//and that the size is updated as we remove items
	int counter = 0;
	auto* ailment = patient.get_ailments().begin();
	while (ailment != nullptr)
	{
		ASSERT_EQ(ailment->data, ailments[counter++]);
		ailment = ailment->next;
	}
}
#endif

#if TEST_PATIENT_CALCULATES_CORRECT_SCORES
TEST(Patient, CalculatesCorrectScores) {
	auto patients = generate_ordered_patient_set();
	std::vector<int> scores = { 80, 72, 25, 22, 14, 14 };

	int index = 0;
	for (const auto& patient : patients)
	{
		ASSERT_EQ(patient.get_score(), scores[index++]);
	}
}
#endif
