#include <iostream>
using namespace std;

struct node {
    int data;
    node* next;
};

struct queue {
    node* front = nullptr;
    node* rear  = nullptr;
};

queue q;

bool isEmpty(queue q) {
    return q.front == nullptr;
}

void enqueue(int nilai) {
    node* baru = new node{nilai, nullptr};

    if (isEmpty(q)) {
        q.front = baru;
        q.rear  = baru;          
    } else {
        q.rear->next = baru;
        q.rear = baru;
    }

    cout << "Data " << nilai << " berhasil ditambahkan ke antrian geng" << endl;
}

void dequeue() {
    if (isEmpty(q)) {
        cout << "Data kosongg bree" << endl;
        return;
    }

    node* hapus = q.front;
    q.front = hapus->next;

    if (q.front == nullptr) {
        q.rear = nullptr;
    }

    cout << "Data yang dihapus: " << hapus->data << endl;
    delete hapus;
}

void peek() {
    if (isEmpty(q)) {
        cout << "Data kosong breee" << endl;
        return;
    }
    cout << "Data terdepan: " << q.front->data << endl;
}

void printQueue() {
    if (isEmpty(q)) {
        cout << "Data kosong breee" << endl;
        return;
    }

    node* bantu = q.front;
    cout << "Isi antrian: ";
    while (bantu != nullptr) {
        cout << bantu->data << " ";
        bantu = bantu->next;
    }
    cout << endl;
}

void clearQueue() {
    if (isEmpty(q)) {
        cout << "Data kosong breee" << endl;
        return;
    }

    node *bantu = q.front;
    while (bantu != nullptr) {
        node *hapus = bantu;
        bantu = bantu->next;
        delete hapus;
    }
    q.front = q.rear = nullptr;

    cout << "Antrian gw kosongin semuaa yaa breee" << endl;
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    printQueue();     
    dequeue();        
    printQueue();     
    peek();           
    dequeue();        
    printQueue();
    enqueue(40);
    peek();
    clearQueue();     
    printQueue();
}