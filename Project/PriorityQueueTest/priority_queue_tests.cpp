/*
 *
 *  DO NOT MODIFY THIS FILE
 *
 */

#include "pch.h"
#include "test_config.h"

#include "Patient.h"
#include "PriorityQueue.h"

std::vector<Patient> generate_ordered_patient_set();
std::vector<Patient> generate_unordered_patient_set();

#if TEST_PRIORITY_QUEUE_CONSTRUCTOR
TEST(PriorityQueue, Constructor) {
	PriorityQueue<Patient> queue;

	ASSERT_TRUE(queue.empty());
	ASSERT_EQ(queue.size(), 0);
}
#endif

#if TEST_PRIORITY_QUEUE_SINGLE_PATIENT
TEST(PriorityQueue, SinglePatient) {
	PriorityQueue<Patient> queue;

	//create a patient to add to the queue
	const Patient patient("Bob Smith");

	//add the patient to the queue
	queue.enqueue(patient);

	//verify the size
	ASSERT_FALSE(queue.empty());
	ASSERT_EQ(queue.size(), 1);

	//get the top patient and make sure they are the same patient
	Patient patient_from_queue = queue.dequeue();
	ASSERT_EQ(patient_from_queue, patient);

	//make sure the queue is empty again
	ASSERT_TRUE(queue.empty());
	ASSERT_EQ(queue.size(), 0);
}
#endif

#if TEST_PRIORITY_QUEUE_MULTI_PATIENT_ORDERED
TEST(PriorityQueue, MultiPatientOrdered) {
	PriorityQueue<Patient> queue;

	//create a list of patients with various ailments
	std::vector<Patient> test_patients_ordered = generate_ordered_patient_set();
	size_t counter = 0;
	for (auto& patient : test_patients_ordered)
	{
		//add the patient to the queue
		queue.enqueue(patient);
		++counter;

		//verify the size
		ASSERT_EQ(queue.empty(), counter == 0);
		ASSERT_EQ(queue.size(), counter);
	}

	//get the top patient and make sure they are the same patients we added (in order)
	for (const auto& expected_patient : test_patients_ordered)
	{
		--counter;

		//get the patient
		Patient patient_from_queue = queue.dequeue();

		//verify the patient
		ASSERT_EQ(patient_from_queue, expected_patient);

		//verify the size
		ASSERT_EQ(queue.empty(), counter == 0);
		ASSERT_EQ(queue.size(), counter);
	}

	//make sure the queue is empty again
	ASSERT_TRUE(queue.empty());
	ASSERT_EQ(queue.size(), 0);
}
#endif

#if TEST_PRIORITY_QUEUE_MULTI_PATIENT_UNORDERED
TEST(PriorityQueue, MultiPatientUnOrdered) {
	PriorityQueue<Patient> queue;

	//create a list of patients with various ailments
	const std::vector<Patient> test_patients_ordered = generate_unordered_patient_set();
	const std::vector<Patient> test_patients_expected = generate_ordered_patient_set();

	size_t counter = 0;
	for (const auto& patient : test_patients_ordered)
	{
		//add the patient to the queue
		queue.enqueue(patient);
		++counter;
		
		//verify the size
		ASSERT_EQ(queue.empty(), counter == 0);
		EXPECT_EQ(queue.size(), counter);
	}
	
	//get the top patient and make sure they are the same patients we added (in order)
	for (const auto& expected_patient : test_patients_expected)
	{
		--counter;

		//get the patient
		Patient patient_from_queue = queue.dequeue();

		//verify the patient
		ASSERT_EQ(expected_patient, patient_from_queue);

		//verify the size
		ASSERT_EQ(queue.empty(), counter == 0);
		ASSERT_EQ(queue.size(), counter);
	}

	//make sure the queue is empty again
	ASSERT_TRUE(queue.empty());
	ASSERT_EQ(queue.size(), 0);
}
#endif