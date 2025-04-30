/*
	Brodie Dunley
	Student Number: 0849109
*/
#include "Patient.h"
#include "PriorityQueue.h"
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>


PriorityQueue<Patient> queue;

//Forward declarations for functions that will be used in the menu options
void patientIntake(PriorityQueue<Patient>& queue);
void removePatient(PriorityQueue<Patient>& queue, PriorityQueue<Patient>& history);
void display(PriorityQueue<Patient>& queue);
void load_queue(PriorityQueue<Patient>& queue);
void save_queue(PriorityQueue<Patient>& queue);
bool checkQueue(PriorityQueue<Patient>& q, const std::string& patient);


int main(int argc, char* argv[])
{
	std::cout << "******************************************************************" << std::endl;
	std::cout << "*		Welcome to Fanshawe College Medical Center F2024 *" << std::endl;
	std::cout<< "*		Brodie Dunley					 *" << std::endl;
	std::cout << "******************************************************************" << std::endl;

	//Bool that will be used to exit the while loop
	bool menu = true;
	PriorityQueue<Patient> queue;
	PriorityQueue<Patient> history;
	//While loop to keep coming back to the menu after the menu option function has completed
	while (menu)
	{
		//Variable to store the users input of menu choicr
	int choice;
		std::cout << "\nPlease Make a Selection: " << std::endl;
		std::cout << std::endl;
		
		std::cout << "\t1 - Add Patient" << std::endl;
		std::cout << "\t2 - Process Next Patient In Queue" << std::endl;;
		std::cout << "\t3 - Display Queue " << std::endl;
		std::cout << "\t4 - View Processed Patients History" << std::endl;
		std::cout << "\t5 - Load Queue" << std::endl;
		std::cout << "\t6 - Save Queue" << std::endl;
		std::cout << "\t7 - Exit" << std::endl;

		std::cout << " < ";
		std::cin >> choice;
		switch (choice)
		{
		case 1:
			 patientIntake(queue);
			break;
		case 2:
			removePatient(queue,history);
			break;
		case 3:
			display(queue);
			break;
		case 4:
			display(history);
			break;
		case 5:
			load_queue(queue);
			break;
		case 6:
			save_queue(queue);
			break;
		case 7:
			menu = false;
			break;
		default:
			std::cout << "Not a valid choice"; 
			std::cout << "please Choose again.\n";
			continue;

		}
	}

}
/*
	Function Name: patientIntake
	Purpose: First menu option to add a new patient into the Q. It will intake the patient name, condition, severity, time sensitivity and contagiousness. 
	Accepts: A patient Priority Queue
	Returns: Nothing it is a void function

*/
void patientIntake(PriorityQueue<Patient>& queue)
{
	//Creating a linked list to store patient ailments if they have more than one
	LinkedList<Ailment> patientAilmentList;
	
	std::string Condition,patientName;
	int Time, Contagiousness,Severity;	
	std::string temp;
	bool continueFlag = true;

	//Collecting patients name
	std::cout << "Enter patient name: ";
	std::getline(std::cin,temp);
	std::getline(std::cin, patientName);

	//Check if the patient is already in the Q
	bool patient_exists = checkQueue(queue, patientName);
	if (patient_exists == true)
	{
		std::cout << patientName << " is already in the queue! \nDo you want to add another ailment to this Patient? Enter 1 to add another ailment, 2 to exit to menu: ";
		int user_input;
		std::cin >> user_input;

		//flushing the buffer
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		bool valid_input = false;
		PriorityQueue<Patient>::Node* patient_update = queue.getHead();

		//Ensuring the user enters a valid input, if not will re-prompt for entry
		while (valid_input == false)
		{
			switch (user_input) {
			//Case 1 
			case 1:
				
				//Finding the patient node in the Queue 
				while (patient_update->patient.get_name() != patientName)
				{
					patient_update = patient_update->next;
				}

				//Getting the ailments to add to the patient's ailment list
				while (continueFlag)
				{
					std::cout << "Enter ailment (leave blank when done): ";
					std::getline(std::cin, Condition);

					//Condition to indicate if there is more ailments to add. If it is empty, it indicates there is no more ailments and loop will exit
					if (Condition.empty())
					{
						continueFlag = false;
						break;
					}
					std::cout << "Enter severity: ";
					std::cin >> Severity;
					std::cout << "Enter time criticality: ";
					std::cin >> Time;
					std::cout << "Enter contagiousness: ";
					std::cin >> Contagiousness;
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

					//Creating a new ailment and adding it to the current patient's ailment linked list
					Ailment patientAilment{ Condition, Severity, Time, Contagiousness };
					patient_update->patient.add_ailment(patientAilment);

				}
				std::cout << "Updated ailments sucesfully!" << std::endl;
				valid_input = true;
				break;
			case 2:
				std::cout << "Returning to Main menu " << std::endl;
				valid_input = true;
				break;
			default:
				std::cout << "Invalid input, please enter 1 to add another ailment or 2 to exit to the menu.";
			}
			return;
		}


	}

	//Creating a new instance of a patient
	Patient patient;
	patient.setName(patientName);

	while (continueFlag)
	{
		std::cout << "Enter ailment (leave blank when done): ";
		std::getline(std::cin,Condition);

		//Condition to indicate if there is more ailments to add. If it is empty, it indicates there is no more ailments and loop will exit
		if (Condition.empty())
		{
			continueFlag = false;
			break;
		}
		std::cout << "Enter severity: ";
		std::cin >> Severity;
		std::cout << "Enter time criticality: ";
		std::cin >> Time;
		std::cout << "Enter contagiousness: ";
		std::cin>>Contagiousness;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		//Creating a new ailment and adding it to the current ailment linked list
		Ailment patientAilment{ Condition, Severity, Time, Contagiousness };
		patientAilmentList.push_back(patientAilment);
		
	}
	//Setting the Current patients ailments
	patient.setAilmentsList(patientAilmentList);
	//Adding the client to the queue.
	queue.enqueue(patient);
	
}


/*
	Function Name: removePatient
	Purpose: Second menu option to move the top patient in the queue into the waiting room, removes them from the queue and loads this patient into the history of completed patients
	Accepts: 2 patient PriorityQueues, one is the current Queue of patients and the other a record of the patients that have been removed from the Queue
	Returns: Nothing it is a void function

*/
void removePatient(PriorityQueue<Patient>& queue, PriorityQueue<Patient>& history)
{
	//Creating an instance of Patient, assigning the top patient in the Q to it
	Patient patientToRemove = queue.top();
	std::cout << patientToRemove.get_name() << " moved to patient room!" << std::endl;

	//Adding the Patient to the history Q
	queue.patientHistoryProcess(patientToRemove, history);
	//Removing the Patient from the Q
	queue.dequeue();
	//Checking to see if there is anymore people in the Q
	bool morePatients = queue.peekTop();
	if (morePatients == false)
	{
		std::cout << "No one left in Queue! " << std::endl;
	}
	else
	{
		Patient nextPatient = queue.top();
		double nextPatientScore = nextPatient.get_score();
		std::cout << "Next in Queue: " << nextPatient.get_name() << " with a priority score of " << nextPatientScore << std::endl;
		
	}
}

/*
	Function Name: display
	Purpose: Third menu option to display all the patients in the Q and the corresponding information for each Patient
	Accepts: 1 patient PriorityQueues
	Returns: Nothing it is a void function

*/
void display(PriorityQueue<Patient>& queue)
{
	//Creating a Node to traverse the Priority Q
	PriorityQueue<Patient>::Node* current = queue.getHead();
	if (current == nullptr) {
		std::cout << "The queue is currently empty." << std::endl;
		return;
	}

	std::cout << "Patients in Queue:" << std::endl;
	std::cout << std::endl;

	//Using the counter to display the position in the Q the current Patient is in
	int counter = 0;
	// Traverse the queue
	while (current != nullptr) {
		
		std::cout << counter << " : " << current->patient.get_name() << " - Score: " << current->patient.get_score() << " - ";
		//Function call to display the current patients ailment LinkedList
		current->patient.print_ailments();
		std::cout << std::endl;
		current = current->next; 
		//Increment the counter to indicate the next person in line
		counter++;
	}
}

/*
	Function Name: load_queue
	Purpose: Fifth menu option to load the Priority Queue from a csv file
	Accepts: Patient Priority Q so that the function can get the data from the CSV file and load the Q
	Returns: Nothing it is a void function

*/
void load_queue(PriorityQueue<Patient>& queue)
{
	std::string pathway, line, PatientName, num_of_ailments_str, condtion, severity_str, time_str, contagiouness_str,temp;
	int num_of_ailments = 0;
	int time = 0;
	int contagiousness = 0;
	int severity = 0;
	
	//Getting the File path from the user
	std::cout << "Enter path to file: ";
	std::getline(std::cin, temp);
	std::getline(std::cin, pathway);
	
	//Opening the file to read from
	std::ifstream file(pathway);
	if (!file.is_open())
	{
		std::cerr << "Could not open the file!" << std::endl;
		return;
	}
	while (std::getline(file, line))
	{
		//Creating a string stream object to read the information into 
		std::stringstream ss(line);
		std::getline(ss, PatientName, ',');
		std::getline(ss, num_of_ailments_str, ',');
		Patient patient(PatientName);
		try {
			//Using this to know how many ailments the Patient has to be able to loop through and add to the LinkedList Ailment
			num_of_ailments = std::stoi(num_of_ailments_str);
		}
		catch (const std::invalid_argument& e) {
			std::cerr << "Invalid integer format in number of ailments column" << num_of_ailments_str << std::endl;
			continue;
		}
		//Looping through to get the ailment information
		for (int i = 0; i < num_of_ailments; i++)
		{
			std::getline(ss, condtion, ',');
			std::getline(ss, severity_str, ',');
			std::getline(ss, time_str, ',');
			std::getline(ss, contagiouness_str, ',');

			//Converting to integer values
			try {
				severity = std::stoi(severity_str);
				time = std::stoi(time_str);
				contagiousness = std::stoi(contagiouness_str);
			}
			catch (const std::invalid_argument& e) {
				continue;
			}
			//Setting the patient information 
			Ailment ailment;
			ailment.setAilments(condtion, severity, time, contagiousness);
			patient.add_ailment(ailment);
		}
		//Add the patient to the Q
		queue.enqueue(patient);
		
	}
	std::cout << "Queue loaded successfully" << std::endl;
	file.close();
	
}

/*
	Function Name: save_queue
	Purpose: Sixth menu option to save the Priority Queue to a csv file
	Accepts: Patient Priority Q so that the function can get the data that it will be saving to the CSV file
	Returns: Nothing it is a void function

*/
void save_queue(PriorityQueue<Patient>& queue)
{
	std::string filename,PatientName,temp;
	
	int time = 0;
	int contagiousness = 0;
	int severity = 0;
	
	//flushing the buffer
	std::getline(std::cin, temp);

	std::cout << "Enter path to the file you would like to save to: ";
	std::getline(std::cin, filename);

	std::ofstream file(filename);
	
	if (!file.is_open())
	{
		std::cerr << "Could not open the file!" << std::endl;
		return;
	}
	
	file << "Patient Name, Ailment, Severity, Time Sensitivity, Contagiousness, Ailment_2,Severity_2, Time Sensitivity_2, Contagiousness_2\n ";
	
	PriorityQueue<Patient>::Node* current = queue.head;
	while(current != nullptr)
	{
		const Patient& patient = current->patient;
		PatientName = patient.get_name();
		LinkedList<Ailment> patientAilments = current->patient.get_ailments();
		LinkedList<Ailment>::Node* currentAilment = patientAilments.begin();
		
		file << PatientName << ", ";
		while (currentAilment != nullptr)
		{
			
				file << currentAilment->data.get_name() << ", "
				<< currentAilment->data.get_severity() << ", "
				<< currentAilment->data.get_time_sensitivity() << ", "
				<< currentAilment->data.get_contagiousness();

			currentAilment = currentAilment->next;

			if (currentAilment != nullptr) {
				file << ", ";
			}
		}
		file << "\n";
		current = current->next;
	}
	file.flush();
	file.close();
	std::cout << "Queue saved successfully to " << filename << std::endl;
}
/*
	Function Name: checkQueue
	Purpose: To check if the patient being added to the Q is already there
	Accepts: A priority Queue of type Patient, a const string of the patients names
	Returns: A bool indicating if the client was already in the Queue or not

*/
bool checkQueue(PriorityQueue<Patient>& q, const std::string& patient)
{
	PriorityQueue<Patient>::Node* current = q.getHead();
	while (current != nullptr)
	{
		if (current->patient.get_name() == patient)
			return true;

		current = current->next;
	}

	return false;
}


