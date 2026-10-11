#include <iostream>
using namespace std;

struct node{
    int info;
    node* next;
};

struct linkedStack{
    node* top;
};

linkedStack stack;

void buatStack(){
    stack.top = nullptr;
}

bool isFull(){
    node* temp = new node();
    if(temp == nullptr){
        return true;
    }
    delete temp;
    return false;
}

bool isEmpty(){
    return stack.top == nullptr;
}

// push - menambahkan stack baru
bool push(int info_baru){
    node* newNode = new node();

    if(isFull()){
        cout << "stack is full breee" << endl;
        return false;
    }

    newNode->info = info_baru;
    newNode->next = stack.top;
    stack.top = newNode;
    return true;
}

// pop - hapus paling atas
void pop(){
    if(isFull()){
        cout << "stack penuhh breee" << endl;
        return;
    }
    node* temp = stack.top;
    stack.top = stack.top->next; // top turun ke node berikutnya
    cout << "Berhasil POPPP nih: " << temp->info << endl;
    delete temp;
}

// membaca data paling atas
void peek(){
    if(isEmpty()){
        cout << "stack masih kosong breee" << endl;
        return;
    }
    cout << "data paling atas (peek): " << stack.top->info << endl;
}


void printStack(){
    if(isEmpty()){
        cout << "stack masih kosong breee" << endl;
        return;
    }

    node* temp = stack.top;
    while (temp != nullptr){
        cout << temp->info << " ";
        temp = temp->next;
    }
    
}

void clear(){
    if(isEmpty()){
        cout << "stack masih kosong breee" << endl;
        return;
    }
    while(stack.top != nullptr){
        node* temp = stack.top;
        stack.top = stack.top->next;
        delete temp;
    }
    
}

int main(){
    buatStack();
    cout << "Isi Stack: ";
    printStack();
    push(82);
    push(21);
    push(32);
    push(15);
    cout << "Isi Stack: ";
    printStack();
    cout << endl;
    peek();
    pop();
    cout << "Isi Stack: ";
    printStack();
    cout << endl;
    clear();
    cout << "Isi Stack: ";
    printStack();
    cout << endl;
}