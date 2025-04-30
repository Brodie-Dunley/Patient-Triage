/*
	Brodie Dunley
	Student Number: 0849109
*/
#pragma once
#include "Ailment.h"
#include "LinkedList.h"
#include <string>
#include <iostream>

class Patient
{
//Creating a Node for the Patient class
public:
	struct Node {

		std::string Condition;
		int Severity;
		int timeSeverity;
		int contagiousness;

		Node* prev;
		Node* next;
		Node() : Condition(""), Severity(0), timeSeverity(0), contagiousness(0) {}
		Node(std::string c, int sev, int timesev, int contag) : Condition(c), Severity(sev), timeSeverity(timesev),contagiousness(contag) {}
	};
	std::string name_;
	LinkedList<Ailment> ailments_;
	double score_;
	
	Node* head;
	Node* tail;

public:
	Patient() : head(nullptr),name_(""), ailments_(){}
	Patient(std::string n) : name_(n) {}
	Patient(std::string n, LinkedList<Ailment> a) : name_(n),ailments_(a) {}
	
	//Getter methods for the head and tail 
	Node* getHead() const { return head; }
	Node* getTail() const { return tail; }
	void setName(std::string name)
	{
		name_ = name;
	}
	std::string get_name() const{
		return name_;
	}
	
	void setAilmentsList(LinkedList<Ailment> patientAilmentList)
	{
		ailments_ = patientAilmentList;
	
	}
	void add_ailment(Ailment ailment)
	{
		ailments_.push_back(ailment);
	}
	void setScore(double score)
	{
		score_ = score;
	}
	/*
		Name: get_score()
		Purpose: Calculates the severity score for the patient, this will be used to determine where to add the patient in the priority Q
	*/
	double get_score() const
	{
		auto* nonConstAilments = const_cast<LinkedList<Ailment>*>(&ailments_);
		LinkedList<Ailment>::Node* current = nonConstAilments->begin();
		
		double score = 0.0;
		while (current != nullptr)
		{
			const Ailment& ailment = current->data;
			score += (ailment.get_severity() * ailment.get_time_sensitivity()) + ailment.get_contagiousness();
			current = current->next;
		}
		return score;
	}
	/*
		Name: get_ailments()
		Purpose: To return a linked list of Ailments for a specific patient
	*/
	LinkedList<Ailment>get_ailments() const{
		return ailments_;
	}

	/*
		Name: print_ailments
		Purpose: To print out the ailments in a linked list
	*/
	void print_ailments() {
		LinkedList<Ailment> returnAilments = ailments_;
		LinkedList<Ailment>::Node* current = returnAilments.begin();
		while (current != nullptr)
		{
			std::cout << current->data.get_name() << ", ";
			current = current->next;
		}
	}

	//Overloading the equality operator to be able to compare Patient class objects
	bool operator==(const Patient& other) const {
		return  name_ == other.name_;
	}
	
	
};