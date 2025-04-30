/*
 *
 *  DO NOT MODIFY THIS FILE
 *
 */

#include "pch.h"
#include "Ailment.h"
#include "Patient.h"
#include "test_config.h"

 //just some helper functions for basic test sets
 //if there are errors here please check your constructors
#if TEST_PATIENT_ADD_AILMENT
std::vector<Patient> generate_ordered_patient_set()
{
	Patient p1("A");
	p1.add_ailment(Ailment("Heart Attack", 8, 10, 0));

	Patient p2("B");
	p2.add_ailment(Ailment("Stroke", 9, 8, 0));

	Patient p3("C");
	p3.add_ailment(Ailment("Broken Arm", 5, 5, 0));

	Patient p4("D");
	p4.add_ailment(Ailment("Covid-19", 4, 3, 10));

	Patient p5("E");
	p5.add_ailment(Ailment("Flu", 3, 3, 5));

	Patient p6("F");
	p6.add_ailment(Ailment("Flu", 3, 3, 5));

	return { p1, p2, p3,p4, p5, p6 };
}
std::vector<Patient> generate_unordered_patient_set()
{
	Patient p1("A");
	p1.add_ailment(Ailment("Heart Attack", 8, 10, 0));

	Patient p2("B");
	p2.add_ailment(Ailment("Stroke", 9, 8, 0));

	Patient p3("C");
	p3.add_ailment(Ailment("Broken Arm", 5, 5, 0));

	Patient p4("D");
	p4.add_ailment(Ailment("Covid-19", 4, 3, 10));

	Patient p5("E");
	p5.add_ailment(Ailment("Flu", 3, 3, 5));

	Patient p6("F");
	p6.add_ailment(Ailment("Flu", 3, 3, 5));

	//p6 must be after p6 (as they have same priority and are first come first serve)
	return { p5, p1, p6, p3,p4,p2 };
}
#endif

