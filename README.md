# Patient-Triage
Creating a program for nurses to use to Triage patients in an emergency room

This project is meant to demonstrate the implementation of Queues and Prirority Queues in a real world setting. 

**Requirements**
- Create a menu that will allow a Triage Nurse to:
- Add a patient to the queue in its appropriate position based on their triage status (priority)
      -  You will collect the following parameters for patients:
            - Name
            - Ailments
                - The patient can have more than one. Use an instance of the LinkedList class to hold all the ailments.
                - Contain Severity, time criticality, contagiousness for each condition.
- Service the next patient in the queue
    - Remove the pateient from the queue with the highest priority
    - Display the patient with the next highest priority score 
- Print the contents of the queue
    - Display the patients in the queue including the following information:
        - Their position in the queue
        - Patient name
        - Priority score
        - Ailments  
- Print the history of the queue (oldest first)
    - Display a list of pateients that have been processed"
        - Most recently treated patient first
        - This should list the following:
            - Patient name
            - Priority Score
            - Ailments      
- Load the queue from a csv file (see patients.csv for formatting.)
    - Prompt the user to enter a path to a .csv file that contains a list of pateients
        - Load the patients from the file into the queue  
- BONUS: Save the queue to a csv file (in the same format as loading.)
    - Prompt the user to enter a path to a file to write the patient data from the queue to.

 Technical Requirements:

- No STL (Standard Template Library)
  - Except where provided by me in PriorityQueueTests
- All inputs must be validated
- Pointer notation must be used throughout
- Patient Class Properties
  - Patient Name
  - Must maintain a list of Ailments using the provided LinkedList class
- Ailment Properties
  - Name
  - Severity
	- Time Criticality
	- Contagiousness
- PriorityQueue
  - Must use an instance of the LinkedList class to hold queued patients
  - Patients may only be in the queue once (no duplicates)
  - Patients position is determined by the sum of all ailments priority score. (> score is higher priority)
  - Score calculated by the following:
    - (Severity * Time Criticality) + Contagiousness
  - Score calculated when patient joins the queue


