#include <iostream>
using namespace std;

// di circular LL, tail tidak menunjuk nullptr,
// dia menunjuk ke head,
// jadi kaya lingkaran

struct Node {
    int info;
    Node *next;
};

Node *head = nullptr;
Node *tail = nullptr;

bool listKosong(){
    return head == nullptr;
}

void sisipNode(int info_baru){
    Node *newNode = new Node();
    newNode->info = info_baru;
    newNode->next = nullptr;

    if(listKosong()){
        // mengubah head sekaligus tail jadi newnode
        head = tail = newNode;
        // menunjuk dirinya sendiri
        newNode->next = head;
    } else if (info_baru < head->info){
        // apabila info_baru lebih kecil dari head
        newNode->next = head;
        head = newNode; // head pindah ke node baru
        tail->next = head; // tail menunjuk ke node baru
    } else if (info_baru >= tail->info){
        // apabila info_baru lebih besar atau sama dengan tail
        // dia harus jadi tail baru
        tail->next = newNode;
        tail = newNode;
        tail->next = head;
    } else {
        // apabila info_baru ada di tengah tengah
        Node *temp = head;
        while (temp->next != head && temp->next->info <= info_baru){
            temp = temp->next; // cari posisi yang pas
        }
        newNode->next = temp->next;
        temp->next = newNode;
    }
}

void hapusNode(int info_hapus){
    if(listKosong()){
        cout << "List masih kosong!" << endl;
        return;
    }

    Node *temp = tail;
    Node *hapus = head;

    do {
        // apabila node yang dicari ketemu
        if(hapus->info == info_hapus){
            // cuma ada satu node
            if (head == tail){
                head = tail = nullptr;
            } else { // kalau ada beberapa node 
                temp->next = hapus->next;
                if (hapus == head) { // apabila yang dihapus head
                    head = hapus->next;
                } 
                if (hapus == tail) {
                    tail = temp;
                }
            }
            delete hapus;
            cout << "Node " << info_hapus << " berhasil dihapus!" << endl;
            return;
        }
        temp = hapus;
        hapus = hapus->next;
    } while (hapus != head);
}

void printLinkedList(){
    if(listKosong()){
        cout << "List masih kosong!" << endl;
        return;
    }

    Node *temp = head;
    do {
        cout << temp->info << ", ";
        temp = temp->next;
    } while (temp != head);
}

int main (){
    sisipNode(30);
    sisipNode(4);
    sisipNode(9);
    sisipNode(20);
    printLinkedList();
    hapusNode(4);
    hapusNode(30);
    printLinkedList();
}