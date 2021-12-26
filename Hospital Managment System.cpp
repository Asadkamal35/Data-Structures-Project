#include<iostream>
#include<fstream>
#include<string>
#include<time.h>
#include<cstdlib>
#include <iomanip>
#define size 26
using namespace std;

class node {
public:
	string data;
	string disease;
	string medicine;
	node* next;
	
	node():next(NULL){}
};

class Node {
public:
	Node* child[size];
	bool wordEnd;
	Node() {
		for (int i = 0; i < size; i++) {
			child[i] = NULL;
		}
		wordEnd = false;
	}
};

class tries {
	Node* root;

public:
	tries() {
		root = createNode();
	}
	Node* createNode() {
		Node* newNode;
		newNode = new Node;
		return newNode;
	}

	void add_medicine() {
		string yourtext;
		ifstream ReadFile("search.txt");
		while (getline(ReadFile, yourtext)) {
			insert(yourtext);
		}
	}

	void insert(string word) {
		word = to_Lower(word);
		int len = word.length();
		int index;
		Node* temp = root;
		for (int i = 0; i < len; i++) {
			index = word[i] - 'a';
			if (!(temp->child[index])) {
				temp->child[index] = createNode();
			}
			temp = temp->child[index];
		}
		temp->wordEnd = true;
	}

	string to_Lower(string word) {
		for (int i = 0; i < word.length(); i++) {
			word[i] = tolower(word[i]);
		}
		return word;
	}

	bool search(string word) {
		word = to_Lower(word);
		int len = word.length();
		int index;
		Node* temp = root;
		for (int i = 0; i < len; i++) {
			index = word[i] - 'a';
			if (!temp->child[index])
				return false;

			temp = temp->child[index];
		}
		if (temp->wordEnd)
			return true;
		else
			return false;
	}

};

class linked_list {
public:
	void push(node** head_ref, string new_data, string new_disease, string new_medicine="") {
		node* new_node = new node();
		new_node->data = new_data;
		new_node->disease = new_disease;
		new_node->medicine = new_medicine;
		new_node->next = *head_ref;
		*head_ref = new_node;
	}
	void append(node** head_ref, string new_data, string new_disease, string new_medicine) {
		node* new_node = *head_ref;
		node* temp = *head_ref;
		new_node->next = NULL;
		new_node->data = new_data;
		new_node->medicine = new_medicine;
		new_node->disease = new_disease;

		if (*head_ref == NULL) {
			*head_ref = new_node;
			return;
		}
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = new_node;
	}

	void print(node* n) {
		cout << "NAME\t" << "\t    DISEASE\t" << "\t\t  MEDICINE\t" << endl;
		while (n != NULL) {
			cout << left;
				cout <<setw(20)<< n->data << setw(30) << n->disease << setw(25)<< n->medicine<<"\n";
				n = n->next;
			
		}
	}

	void find_medicine(node* head) {
		tries obj;
		obj.add_medicine();
		bool found;
		while (head != NULL) {
			//cout << <<endl;
			found=obj.search(head->medicine);
			if (found == true) {
				cout << head->medicine << " found" << endl;
			}
			else {
				cout << "NOT FOUND" << endl;
			}
			head = head->next;
		}
	}
};

class queue {
public:
	int count = 0;
	void enqueue(node** head_ref, string new_data) {
		node* new_node = new node();
		new_node->data = new_data;
		new_node->next = *head_ref;
		*head_ref = new_node;
	}

	string dequeue(node** head_ref) {
		string temp_data;
		node* temp = *head_ref;
		node* prev = *head_ref;
		while (temp->next!=NULL) {
			prev = temp;
			temp = temp->next;
		}
		if (temp == (*head_ref)) {
			*(head_ref) = NULL;
			return temp->data;
		}
		prev->next = NULL;
		temp_data = temp->data;
		
		//prev = temp;
		return temp_data;
	}

	void print(node* n) {
		while(n!=NULL) {
			cout << " " << n->data << "  " << endl;
			n = n->next;
		}
	} 
};

class patient {
private:
	int Total_patients = 12 + rand() % (14 - 12 + 1);
	int surgeries= 4 + rand() % (7 - 4 + 1);
	int surgeries2 = 0;

	int medicine_patients=0;

	linked_list list1;
	node* head_list1 = NULL;
	
	queue list;
	queue surgery;
	queue pharmacy;
	queue total_pharmacy;
	queue total_surgery;

	node* head = NULL;
	node* head_surgery = NULL;
	node* head_total_pharmacy = NULL;
	node* head_total_surgery = NULL;
	node* head_pharmacy = NULL;
public:

	void add_patient() {
		
		int a = 0;
		
		string myText;
		ifstream MyReadFile("Names.txt");
		
		srand(time(0));
		Total_patients = 12 + rand() % (14 - 12 + 1);
		
		while (getline(MyReadFile, myText) && (a) < (Total_patients)) {
			list.enqueue(&head, myText);
			a++;
		}
		MyReadFile.close();
	}

	void diagnose() {

		srand(time(0));
		int surgeries = 4 + rand() % (7 - 4 + 1);

		int number = 0;
		int count = 0;

		string str;
		cout << "\t\tTotal patients day 1" << endl;
		list.print(head);
		//cout << "";
		
		for (int i = 0; i < Total_patients; i++) {
			str = list.dequeue(&head);
			
			number= 1 + rand() % (2);
			
			//cout << "NUMBERS : " << number << " ";

			if (number == 1) {
				pharmacy.enqueue(&head_pharmacy, str);
			}
			else if (number == 2 && count<surgeries) {
				surgery.enqueue(&head_surgery, str);
				total_surgery.enqueue(&head_total_surgery, str);
				count++;
			}
			else {
				pharmacy.enqueue(&head_pharmacy, str);
			}
		}
		list.print(head);
		cout << "\n\t\tSURGERY LIST\n";
		surgery.print(head_surgery);
		cout << "\n\t\tPHARMACY LIST\n";
		pharmacy.print(head_pharmacy);
		surgeries2 = surgeries;
		cout << "\n\nTotal patients : " << Total_patients;
		cout << "\nNo. of patients diagnosed for surgeries are : " << surgeries;
		medicine_patients = Total_patients - surgeries;
		cout << "\nNo. of patients who need medicine only : " << medicine_patients;
		cout << "\n\n";
		/*for (int i = 0; i < surgeries; i++) {
			str = list.traverse(head, num);
			surgery.enqueue(&head_surgery,str);
		}
		cout << "\n\nPatients who require Surgery \n\n" << endl;
		surgery.print(head_surgery);*/
	}

	void Prescription() {
		string medicine_Patient,b;
		string yourtext, ourtext;
		string diesease_name, medicine_name;
		int R_number;
		int q = 0;

//Alloting random disease to patients
		for (int i = 0; i < medicine_patients; i++) {
			ifstream MyReadFile("Pharmacy.txt");
			ifstream ReadFile("Medicine.txt");
			q = 0;
			R_number = 0;

			medicine_Patient = pharmacy.dequeue(&head_pharmacy);
//Random number to allot random disease, total number of diseases are 17 so we find 
//a random number between 1 and 17.
			R_number = 1 + rand() % (17);

									//cout << " number : " << R_number;
//Reading files for medicine and disease.
//"q" becomes zero in every alteration so that the files traverse from the begenning to the random line 
//alloted by "R_number".
			while (getline(MyReadFile, yourtext) && q < R_number && getline(ReadFile, ourtext)) {
				diesease_name = yourtext;
				medicine_name = ourtext;
				q++;
			}

			MyReadFile.close();
//A link list("list1") in which each node contains the patient name, patient disease and the medicine.
			list1.push(&head_list1, medicine_Patient, diesease_name, medicine_name);
		}
		list1.print(head_list1);		
	}
	node* get_head(){
		return head_list1;
	}
	int get_surgeries() {
		return surgeries2;
	}
	queue& get_total_surgery(){
		return total_surgery;
	}
	node* get_node() {
		return head_total_surgery;
	}
};

class Surgery {
private:
	int surgeries=0;
	int random_number = 0;
	node* head;
	queue Total_surgeries;
	string types[6] = { "Appendectomy","Carotid endarterectomy","Cataract surgery","Hemorrhoidectomy","Partial colectomy","Tonsillectomy" };
	int cost[6] = { 3000,15000,8000,6500,12000,5000 };
public:
	
	void setSurgeries(int surgery) {
		surgeries = surgery;
	}

	void setHead(node* h) {
		head = h;
	}

	void setTotalSurgeries(queue &surgery) {
		Total_surgeries = surgery;
	}
	
	void Surgery_perform(){

		int i = 0;

		if (5 > surgeries) {
			cout << "\n\t\tSurgery performed : " << surgeries << endl;
			cout << "NAMES\t\t    OPERATIONS \t\t\t  COST\n";
			for (int i = 0; i < surgeries; i++) {
				random_number = 0 + rand() % (5);
				//srand(time(0));
				cout << left;
				cout << setw(20) << Total_surgeries.dequeue(&head)<< setw(30) << types[random_number] << setw(25) << cost[random_number] << endl;
			}	
		}
		else {
			cout << "\n\t\tSurgery performed : " << 5 << endl;
			cout << "NAMES\t\t    OPERATIONS \t\t\t  COST\n";
			for (int i = 0; i < 5; i++) {
				random_number = 0 + rand() % (5);
				//srand(time(0));
				cout << left;
				cout << setw(20) << Total_surgeries.dequeue(&head) << setw(30) << types[random_number] << setw(25) << cost[random_number] << endl;
			}
		}
	}
};

class mains {
	patient obj;
	Surgery s;
	tries P;
	linked_list L;

public: 
	mains() {

			obj.add_patient();
			obj.diagnose();
			obj.Prescription();
			s.setHead(obj.get_node());
			s.setSurgeries(obj.get_surgeries());
			s.setTotalSurgeries(obj.get_total_surgery());
			s.Surgery_perform();
			cout << "LAKA POI POI \n\n" << endl;
			L.find_medicine(obj.get_head());
	}
};

int main() {
	mains obj;
	return 0;
}