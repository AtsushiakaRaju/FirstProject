#include<iostream>
#include<string>   //For string
#include<fstream>  //For file handling
using namespace std;

int n = 0;  //Variable to store the number of tasks

struct node{      //Create a node structure
    int i;               
    string task;
    string CompletionTime;
    node* next;
}; //Consists of task number, task and completion time

struct node *head = NULL, *cur, *newnode;
//Some usful variables for the code
void create() {   //Function to create a new node
    newnode = new node();
    newnode->i = ++n;
    cout << "Task no. " << newnode->i << endl;
    
    cin.ignore();  // Clear the input buffer before using getline
    cout << "Enter task: ";
    getline(cin, newnode->task);
    
    cout << "Enter completion time: ";
    cin >> newnode->CompletionTime;
    
    newnode->next = NULL;  
}  

void addTask() {   //Function to add a new task 
    create();
    if (head == NULL) { 
        head = newnode;
    } else {
        cur = head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newnode;
    }
}

void deleteTask_byNumber(int y) {    //Function to delete a task
    cur = head;
    node *temp = nullptr;
    
    while (cur != NULL && cur->i != y) {
        temp = cur;
        cur = cur->next;
    }
    
    if (cur == NULL) {
        cout << "Task not found" << endl;
    } else if (cur == head) {
        temp = head;
        head = head->next;
        delete temp;
    } else if (cur->next == NULL) {
        temp->next = NULL;
        delete cur;
    } else {
        temp->next = cur->next;
        delete cur;
    }
}

void putDataIntoFile() {    //Function to save data into file
    ofstream outFile("todo.txt", ios::trunc);  // Open file in trunc mode to clear previous contents
    if (outFile.is_open()) {
        if (head == NULL) {
            cout << "No tasks to save. File will be cleared." << endl;
        } else {
            cur = head;
            while (cur != NULL) {
                outFile << cur->i << endl;
                outFile << cur->task << endl;
                outFile << cur->CompletionTime << endl;
                cur = cur->next;
            }
            cout << "To-do list saved to file." << endl;
        }
        outFile.close();
    } else {
        cout << "Error opening file to write." << endl;
    }
}


void takeDataFromFile() {    //Function to load data from file
    ifstream inFile("todo.txt");
    if (inFile.is_open()) {
        string task, completionTime;
        int x;
        node* temp = nullptr;

        while (inFile >> x) {  // Read the task number
            inFile.ignore();   // Ignore leftover newline
            getline(inFile, task);  // Read the task
            getline(inFile, completionTime);  // Read the completion time
            
            node* newNode = new node();  // Create a new node
            newNode->i = x;
            newNode->task = task;
            newNode->CompletionTime = completionTime;
            newNode->next = nullptr;

            if (head == nullptr) {  // If list is empty, this is the first node
                head = newNode;
                temp = head;
            } else {
                temp->next = newNode;  // Add to the end of the list
                temp = newNode;
            }
        }
        inFile.close();
        cout << "To-do list loaded from file." << endl;
    } else {
        cout << "Error opening file to read." << endl;
    }
}

void display() {         //Function to display the list
    if (head == NULL) {   
        cout << "List is empty" << endl;
    } else {
        cur = head;
        while (cur != NULL) {
            cout <<cur->i<<": "<< cur->task << " __Finish by__  " << cur->CompletionTime << endl;
            cur = cur->next;
        }
    }
}

int main() {            //Main function
    takeDataFromFile();
    int ch, q;
    
    while (1) {
        cout << "Enter your choice: " << endl;
        cout << "1. Add task, 2. Delete task, 3. Display, 4. Exit" << endl;
        cin >> ch;
        
        switch (ch) {
            case 1: addTask();
                    break;
            case 2: display();
                    cout << "Enter the task number to delete: ";
                    cin >> q;
                    deleteTask_byNumber(q);
                    break;
            case 3: display();
                    break;        
            case 4: putDataIntoFile();
                    exit(0);
        }
    }
}
