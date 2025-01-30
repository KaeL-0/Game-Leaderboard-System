#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <limits>
#include <stdexcept>
#include <sstream>  

using namespace std;

//this struct will be our node for our linkedlist

struct Node {
	int list_score;
	string list_name;
	Node* next;

	//constructor for node
	Node(int list_score, string list_name)
		: list_score(list_score), list_name(list_name), next(NULL) {}
};

class LinkedList {
private:

	//our pointer that points at the head or the start of the list
	// we must intialize it to NULL to indicate that it has no node yet
	Node* head = NULL;
	int size = 0; // for our update function in the linked list



public:

	//Our function that will insert nodes to our list
	bool append(int score, string name) {

		Node* temp = head;

		//To prevent duplication of data we must verify if player exist
		//if player exist output a message and terminate function
		while (temp) {

			if (temp->list_name == name) {

				return true;
			}
			temp = temp->next;
		}

		Node* newNode = new Node(score, name);
		if (!head) {
			head = newNode;
		} else {
			temp = head;
			while (temp->next) {
				temp = temp->next;
			}
			temp->next = newNode;
		}
		insertion_sort();
		size++;
		return false;
	}

	void insertion_sort() {

		Node* sorted = NULL;  //This will act as the sorted part of the list
		Node* current = head;

		while (current != NULL) {
			Node* nextNode = current->next;

			//Putting the current node into the sorted part of the list
			//Note that the sorted part of the list act as a different list until we sorted all of the nodes

			//If the current node is greater than the sorted node, the next node of the current will be sorted, and the sorted pointer will point to the current node
			if (sorted == NULL || sorted->list_score < current->list_score) {
				current->next = sorted;
				sorted = current;
			}

			//The insertion will traverse the temp(sorted) node until it is NULL and if the nextnode score is greater than the currentnode score
			else {
				Node* temp = sorted;
				while (temp->next != NULL && temp->next->list_score >= current->list_score) {
					temp = temp->next;
				}

				//Point the currentnode pointer to temp->next
				//then point the temp to the current
				//It will be in visualization:   Node Node Node Tempnode Currentnode Node Node
				//or Node Node Node Tempnode Currentnode NULL

				current->next = temp->next;
				temp->next = current;
			}

			current = nextNode;
		}

		// Set head to the sorted part of the list
		head = sorted;
	}


	void update_score(string name, int new_score) {
		Node* temp = head;


		// Traversing the list to find the player name and update the score
		while (temp) {
			if (temp->list_name == name) {
				temp->list_score = new_score;
				insertion_sort();
				return;
			}
			temp = temp->next;
		}
		cout << "\n\nInvalid Input, player does not exist\n";
	}
	//function to get the name of the top 10 on the list
	string get_nametop10() {
		Node* temp = head;

		for(int i = 1; i < 10; i++) {
			temp = temp->next;
		}
		return temp->list_name;

	}
	
	//function to get the score of the top 10 on the list
	int get_scoretop10() {
		Node* temp = head;

		for(int i = 1; i < 10; i++) {
			temp = temp->next;
		}
		return temp->list_score;

	}
	//function for display
	void display() {
		Node* temp = head;

		cout << "\n\nPLAYERS AND SCORES\n\n";
		while (temp) {
			cout << "Player name  : " << temp->list_name << endl;
			cout << "Player score : " << temp->list_score << endl << endl;
			temp = temp->next;
		}
		cout << "END OF THE LIST" << endl;
		cout << "Total Data: " << size << endl;
	}



	//descructor to avoid memory leaks (seems useless, but ok)
	~LinkedList() {
		Node* temp;
		while (head) {
			temp = head;
			head = head->next;
			delete temp;
		}
	}
};

//basically a struct, it will serve as our "variable" in the priorityqueue class

class Player {
public:
	int score;
	string name;

	Player(int score, string name) {
		this->score = score;
		this->name = name;
	}

	//this is an operator overloading, it is a custom function that basically overrides the "<" operator when using it against other Player objects
	bool operator<( Player &other) {
		return score < other.score;
	}
};

//Our priority queue class
class Leaderboard {
private:


	Player* heap[10];
	int size;


	void swap(Player* &a, Player* &b) {
		Player* temp = a;
		a = b;
		b = temp;
	}


	void heapify(int i) {

		int lowest = i;
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		//compare the parent node to its left and right child, if child is less than the parent then recursive call

		if (left < size && heap[left] < heap[lowest]) {
			lowest = left;
		}

		if (right < size && heap[right] < heap[lowest]) {
			lowest = right;
		}

		if (lowest != i) {
			swap(heap[i], heap[lowest]);
			heapify(lowest);
		}


		//Im using bubble sort to sort the data from lowest to highest
		//even though we have maintain the min-heap property, it is still not properly sorted for displaying the top 10 scores
		//since we're dealing with low dataset of 10, bubble sort is a suitable algorithm

		for (int i = 0; i < size; i++) {
			for (int j = i + 1; j < size; j++) {
				if (heap[i]->score > heap[j]->score) {
					swap(heap[i], heap[j]);
				}
			}
		}


	}





public:
	Leaderboard() {
		size = 0;
	}

	// Function to insert a new player into the heap
	// If the player already exist then terminate function
	void insert_score(int score, string name) {

		for (int i = 0; i < size; i++) {
			if (heap[i]->name == name) {
				return;
			}
		}
		//size > 10, because 10 is the max size of our array
		if (size < 10) {
			heap[size] = new Player(score, name);
			heapify(size);
			size++;
		} else {

			// if the new input score is higher than heap[0] which is the lowest score of the top 10, replace the top 10 with the new input score
			//after that using heapify function to maintain min-heap property and to sort the array

			if (score > heap[0]->score) {
				delete heap[0];
				heap[0] = new Player(score, name);
				heapify(0);
			}
		}
	}


	//Function to update player score in the heap

	bool update_score(string name, int new_score) {

		for (int i = 0; i < size; i++) {
			if (heap[i]->name == name) {
				heap[i]->score = new_score;
				heapify(i);
				return false;
			}
		}
		return true;
	}
	
	//function to get the lowest score on the leaderboard
	int get_scoretop10() {

		return heap[0]->score;
	}

	
	// Function to display the top scores with names
	void display_top() {

		cout << "\n\nTop 10 Scores:" << endl;
		for (int i = size-1; i >= 0; i--) {
			cout << heap[i]->name << ": " << heap[i]->score << endl;
		}
	}

	void write_to_file() {
		ofstream outFile("leaderboard.txt");
		if (!outFile) {
			cout << "Error: Unable to open file for writing." << endl;
			return;
		}

		outFile << "Top 10 Scores:" << endl;
		for (int i = size-1; i >= 0; i--) {
			outFile << left << setw(10) << heap[i]->name << ": "
			        << right << setw(5) << heap[i]->score << endl;
		}
		outFile.close();
	}

	//descructor to avoid memory leaks (seems useless, but ok)
	~Leaderboard() {

		for (int i = 0; i < size; i++) {
			delete heap[i];
		}
	}
};

int getValidPositiveInteger(const string& prompt, int minValue, int maxValue) {
    int value;
    bool validInput = false;
    string input;
    
    do {
        try {
            cout << prompt;
            cin >> input;
            
            // Check if input contains only digits
            for(size_t i = 0; i < input.length(); i++) {
                if(!isdigit(input[i])) {
                    throw invalid_argument("Input must contain only numbers.");
                }
            }
            
            // Convert string to integer using stringstream
            stringstream ss(input);
            ss >> value;
            
            // Check range
            if (value < minValue || value > maxValue) {
                stringstream error_msg;
                error_msg << "Value must be between " << minValue << " and " << maxValue;
                throw out_of_range(error_msg.str());
            }
            
            validInput = true;
            
        } catch (const invalid_argument& e) {
            cout << "\nError: Invalid input. Please enter only numbers or positive integers.\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } catch (const out_of_range& e) {
            cout << "\nError: " << e.what() << "\n\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    } while (!validInput);
    
    return value;
}



int main() {
    //Objects
    LinkedList list;
    Leaderboard ld;

    //Variables for the menu
    int menu = 0;
    bool loop = true;

    //Variables for the player inputs
    int score;
    string name;

    //Test Cases
    ld.insert_score(560, "Taguiam");
    ld.insert_score(420, "Laqui");
    ld.insert_score(850, "Junio");
    ld.insert_score(850, "Kyle");
    ld.insert_score(667, "Aldrin");
    ld.insert_score(705, "Duebean");
    ld.insert_score(310, "Gonzales");
    ld.insert_score(670, "Edra");
    ld.insert_score(900, "Amiel");
    ld.insert_score(1000, "Ric");

    list.append(560, "Taguiam");
    list.append(420, "Laqui");
    list.append(850, "Junio");
    list.append(850, "Kyle");
    list.append(667, "Aldrin");
    list.append(705, "Duebean");
    list.append(310, "Gonzales");
    list.append(670, "Edra");
    list.append(900, "Amiel");
    list.append(1000, "Ric");

    //MENU OPTIONS
    while(loop) {
        cout << "________________________________\n" << endl;
        cout << "    GAME LEADERBOARD SYSTEM" << endl;
        cout << "________________________________\n\n" << endl;

        cout << "MENU OPTIONS\n\n";
        cout << "1. Add player score\n";
        cout << "2. Update player score\n";
        cout << "3. Display the top 10 scores\n";
        cout << "4. Display the list of all scores\n";
        cout << "5. Open the leaderboards file\n";
        cout << "6. Exit program\n\n";

        menu = getValidPositiveInteger("Enter here: ", 1, 6);
        bool v_playerexist = false;

        switch(menu) {
            case 1: {
                cout << "Enter Player Name: ";
                cin >> name;
                score = getValidPositiveInteger("Enter Score (1-1000): ", 1, 1000);
                
                ld.insert_score(score, name);
                v_playerexist = list.append(score, name);
                
                if(v_playerexist != true) {
                    cout << "\nPlayer " << name << " score of " << score << " is inserted\n\n";
                    ld.write_to_file();
                    break;
                }
                cout << "\nPlayer " << name << " already exist\n";
                cout << "Updating player score.......\n";
                break;
            }

            case 2: {
                bool upt = false;
                
                if(v_playerexist != true) {
                    cout << "Enter Player Name to Update Score: ";
                    cin >> name;
                    score = getValidPositiveInteger("Enter Score (1-1000): ", 1, 1000);
                }
            
                list.update_score(name, score);
                upt = ld.update_score(name, score);

                if(upt) {
                    ld.insert_score(score, name);
                    ld.write_to_file();					
                    break;
                }

                int list_temp_score = list.get_scoretop10();
                int heap_temp_score = ld.get_scoretop10();

                if(list_temp_score > heap_temp_score) {
                    name = list.get_nametop10();
                    score = list.get_scoretop10();
                    ld.insert_score(score, name);
                }

                cout << "Player " << name << " score of " << score << " is updated\n\n";
                ld.write_to_file();
                break;
            }

            case 3:
                ld.display_top();
                break;

            case 4:
                list.display();
                break;

            case 5: {
                ld.write_to_file();
                
                ofstream createFile("leaderboard.txt", ios::app);
                createFile.close();

                system("notepad leaderboard.txt");
                break;
            }

            case 6:
                cout << "\nExiting program......";
                loop = false;
                break;
        }
    }

    return 0;
}
