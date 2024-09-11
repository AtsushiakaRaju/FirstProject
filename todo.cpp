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
    getline(cin,newnode->task);
    cout<<"Enter completion time: ";
    cin>>newnode->CompletionTime;
    cin.ignore();
    newnode->next = NULL;
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
void putDataIntoFile(){
    ofstream outFile("todo.txt");  // Open file for writing
    if (outFile.is_open()) {
        cur = head;
        while (cur != NULL) {
            outFile << cur->task << endl;
            outFile << cur->CompletionTime << endl;
            cur = cur->next;
        }
        outFile.close();
        cout << "To-do list saved to file." << endl;
    } else {
        cout << "Error opening file to write." << endl;
    }
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
void display(){
    if(head == NULL){
        cout<<"List is empty"<<endl;
    }
    else{
        cur = head;
        while(cur->next != NULL){
            cout<<cur->task<<" "<<cur->CompletionTime<<endl;
            cur = cur->next;
        }
        cout<<cur->task<<" "<<cur->CompletionTime<<endl;
    }
}
int main(){
    takeDataFromFile();
    string name;
    int ch;
    while(1){
        cout<<"Enter your choice: "<<endl;
        cout<<"1. Add task ,2. Delete task ,3. display,4. exit"<<endl;
        cin>>ch;
        switch(ch){
            case 1: addTask();
                    break;
            case 2: cout<<"Enter the task to delete: ";
                    cin>>name;
                    deleteTask_byName(name);
                    break;
            case 3: display(); break;        
            case 4: putDataIntoFile();
                    exit(0);
        }
    }
}