#include<iostream>
#include<string>
#include<fstream>
using namespace std;
struct node{
    string task;
    string CompletionTime;
    node* next;
};
struct node *head = NULL, *cur,*newnode;
void create(){
    newnode = new node();
    cout<<"Enter task: ";
    cin>>newnode->task;
    cout<<"Enter completion time: ";
    cin>>newnode->CompletionTime;
    newnode->next = NULL;
}
void takeDataFromFile(){
        ifstream inFile("todo.txt");  // Open file for reading
    if (inFile.is_open()) {
        string task, completionTime;
        node* temp = nullptr;
        
        while (getline(inFile, task)) {          // Read the task
            if (getline(inFile, completionTime)) { // Read the completion time
                node* newNode = new node();       // Create a new node
                newNode->task = task;
                newNode->CompletionTime = completionTime;
                newNode->next = nullptr;
                
                if (head == nullptr) {            // If list is empty, this is the first node
                    head = newNode;
                    temp = head;
                } else {
                    temp->next = newNode;         // Add to the end of the list
                    temp = newNode;
                }
            }
        }
        inFile.close();
        cout << "To-do list loaded from file." << endl;
    } else {
        cout << "Error opening file to read." << endl;
    }

}
void addTask(){
    create();
    if(head == NULL){
        head = newnode;
    }
    else{
        cur = head;
        while(cur->next != NULL){
            cur = cur->next;
        }
        cur->next = newnode;
    }
}
void deleteTask_byName(string name){
    cur = head;
    struct node *temp;
    while( cur != NULL && cur->task != name){
        temp = cur;
        cur = cur->next;
    }
    if(cur == NULL){
        cout<<"Task not found"<<endl;
    }
    else if(cur == head){
        temp = head;
        head = head->next;
        delete temp;
    }
    else if(cur->next == NULL){
        temp->next = NULL;
        delete cur;
    }
    else{
        temp->next = cur->next;
        delete cur;
    }
}