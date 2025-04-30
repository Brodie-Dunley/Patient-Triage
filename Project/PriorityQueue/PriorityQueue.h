/*
	Brodie Dunley
	Student Number: 0849109
*/
#pragma once


template <typename T>
class PriorityQueue
{
public:
	struct Node
	{
		Patient patient;
		Node* prev;
		Node* next;
		T data;
		Node(Patient p) : patient(p), prev(nullptr), next(nullptr){}
		Node() :patient(), prev(nullptr), next(nullptr) {}

	};
	LinkedList<T> patients_;
	
	Node* head;
	Node* tail;
	int q_size;
	

public:
	PriorityQueue() : head(nullptr), tail(nullptr),q_size(0) {}
	

	Node* getHead() const { return head; }
	Node* getTail() const { return head; }
	bool empty()
	{
		return head == nullptr;
	}
	
	void push_front(const T& item)
	{
		Node* node = new Node(item);
		node->data = item;

		//check if there is a node to link in-front of
		if (head != nullptr)
		{
			head->prev = node;
			node->next = head;
		}
		else
		{
			tail = node;
		}

		head = node;
	}

	/*
		Name: enqueue
		Purpose: Add a patient to the Queue calculating the priority to place the patient where they should be within the Q
	*/
	void enqueue(const Patient& new_Patient)
	{
		Node* newNode = new Node(new_Patient);

		if (empty())
			head = tail = newNode;
		else
		{
			Node* current = head;
			
			//Calling the get priorirty method, if the new patient has a higher priority, adjust the Q accordingly
			if ((getPriority(newNode->patient)) > (getPriority(current->patient)))
			{
				Node* temp = head;
				head = newNode;
				newNode = temp;
				head->next = newNode;
				current = newNode;
				current->prev = head;
			}
			else
			{
				//If the current patient doesn't have higher priority than the top patient, go through the Q and compare to other patients to determine where they rank
				while (current != nullptr && (getPriority(newNode->patient)) < (getPriority(current->patient))) {
					current = current->next;
				}

				if (current == nullptr || current->next == nullptr)
				{
					tail->next = newNode;
					newNode->prev = tail;
					tail = newNode;
				}
				else if (current == head && (getPriority(current->patient)) != (getPriority(newNode->patient)))
				{
					newNode->next = head;
					head->prev = newNode;
					head = newNode;
				}
				else
				{
					newNode->next = current;
					newNode->prev = current->prev;
					if (current->prev) current->prev->next = newNode;
					current->prev = newNode;
				}
			}
		}
		q_size++;
	}
	/*
		Name: getPriority
		Purpose: Take in a patient, look at their Ailment Linked list and calculate their priority score to be able to compare to others in the Q
		Score calculation = (Severity * time criticiality) + contagiousness
	*/
	double getPriority(Patient& patient)
	{
		LinkedList<Ailment> patientAilments = patient.get_ailments();
		LinkedList<Ailment>::Node* current = patientAilments.begin();
		
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
		Name: dequeue
		Purpose: Remove a patient from the Queue, the priority will be dealt with elsewhere
	*/
	Patient dequeue()
	{
		
		Node* temp = head;
		Patient patient = temp->patient;

		if (head == tail)
		{
			head = tail = nullptr;
		}
		else
		{
			head = head->next;
			head->prev = nullptr;
		}
		delete temp;
		q_size--;
		return patient;
	}

	/*
		Name: patientHistoryProcess
		Purpose: Takes a Patient that is being removed from the Q and adding them to the History Priority Q
	*/
	void patientHistoryProcess(Patient& patient, PriorityQueue<Patient>& history)
	{
		history.push_front(patient);
	}
		
	
	bool peekTop()
	{
		if (empty())
			return false;

		return true;
	}

	/*
		Name: clear
		Purpose: Will fully empty the Q
	*/
	void clear()
	{
		while (!empty())
			dequeue();
	}
	/*
		Name: size
		Purpose: returns the size of the q, which represents the amount of patients in the Q
	*/
	int size()
	{
		return q_size;
	}
	/*
		Name: top
		Purpose: Gives the ability to see who is at the top of the Q
	*/
	Patient top() {
		if (empty()) 
		{
			throw std::runtime_error("Priority Queue is empty.");
		}
			return head->patient;  // The patient with the highest priority is at the head
		}
	/*
		Name: ~PriorityQueue
		Purpose: Destructor for the Priority Queue class
	*/
	~PriorityQueue()
	{
		while (head != nullptr)
		{
			Node* temp = head;
			head = head->next;
			delete temp;
		}
	}
	

};


