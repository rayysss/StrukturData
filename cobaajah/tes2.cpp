#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;   
};

Node* buatNode(int nilai) {
    Node* baru = new Node;
    baru->data = nilai;
    baru->next = nullptr;
    return baru;
}

void cetakList(Node* head) {
    Node* real = head;
    while (real != nullptr) {
        cout << real->data;
        if (real->next != nullptr) cout << " -> ";
        real = real->next;
    }
    cout << " -> null" << endl;
}

Node* mergeSortedLists(Node* L1, Node* L2) {
    Node fake;              
    Node* real = &fake;
    fake.next = nullptr;

    while (L1 != nullptr && L2 != nullptr) {
        if (L1->data <= L2->data) {
            real->next = L1;
            L1 = L1->next;
        } else {
            real->next = L2;
            L2 = L2->next;
        }
        real = real->next;
    }

    if (L1 != nullptr) {
        real->next = L1;
    } else {
        real->next = L2;
    }

    return fake.next;   
}

void swapData(Node* a, Node* b) {
    int temp = a->data;
    a->data = b->data;
    b->data = temp;
}

void sortLinkedList(Node* head) {
    if (head == nullptr) return;

    bool tuker;
    Node* ptr1;
    Node* lptr = nullptr;

    do {
        tuker = false;
        ptr1 = head;

        while (ptr1->next != lptr) {
            if (ptr1->data > ptr1->next->data) {
                swapData(ptr1, ptr1->next);
                tuker = true;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (tuker);
}

int main() {
    cout << "===== Challenge 5: Merge Two Sorted Lists =====" << endl;

    Node* L1 = buatNode(10);
    L1->next = buatNode(30);
    L1->next->next = buatNode(50);

    Node* L2 = buatNode(20);
    L2->next = buatNode(40);
    L2->next->next = buatNode(60);

    cout << "L1   : "; cetakList(L1);
    cout << "L2   : "; cetakList(L2);

    Node* hasil = mergeSortedLists(L1, L2);
    cout << "Hasil: "; cetakList(hasil);

    cout << endl;

    cout << "===== Challenge 6: Sort Linked List =====" << endl;

    Node* head = buatNode(40);
    head->next = buatNode(10);
    head->next->next = buatNode(30);
    head->next->next->next = buatNode(20);

    cout << "Sebelum sort: "; cetakList(head);

    sortLinkedList(head);

    cout << "Setelah sort: "; cetakList(head);

    return 0;
}