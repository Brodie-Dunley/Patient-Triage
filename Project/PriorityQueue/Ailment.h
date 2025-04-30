/*
	Brodie Dunley
	Student Number: 0849109
*/
#pragma once

#include <string>

class Ailment
{
	std::string Condition;
	int Severity;
	int timeCriticality;
	int contagiousness;

public:
	Ailment(): Condition(""), Severity(0),timeCriticality(0), contagiousness(0){}
	Ailment(std::string con, int sev, int time, int contag) : Condition(con),Severity(sev),timeCriticality(time),contagiousness(contag){}

	
	void setAilments(std::string con, int sev, int timeC, int contag)
	{
		Condition = con;
		Severity = sev;
		timeCriticality = timeC;
		contagiousness = contag;
	}
	std::string get_name()const {
		return Condition;
	}
	int get_severity() const {
		return Severity;
	}
	int get_time_sensitivity() const {
		return timeCriticality;
	}
	int get_contagiousness() const {
		return contagiousness;
	}

	//Overloading the equality operator to compare the ailment elements
	bool operator==(const Ailment& other) const {
		return Condition == other.Condition &&
			Severity == other.Severity &&
			timeCriticality == other.timeCriticality &&
			contagiousness == other.contagiousness;
	}
	
};



