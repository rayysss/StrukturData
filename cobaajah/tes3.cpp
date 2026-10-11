#include <iostream>
using namespace std;

struct node{
 int info;
 node* next;
};

node *newNode, *bantu;
node *head, *tail;

void printList(){
    bantu = head;
    while(bantu != NULL){
        cout << bantu->info << " , ";
        bantu = bantu->next;
    }
    cout << endl;
}

void LitsKosong(){
    head = NULL;
    tail = NULL;
}

void sisipNode(int info_baru){
    newNode = new node();
    newNode ->info = info_baru;
    newNode->next = NULL;

    if(head == NULL && tail == NULL){
        head = newNode;
        tail = newNode;   
    }else if (newNode->info < head->info){
        newNode->next = head;
        head = newNode;
    }else if (newNode->info > tail->info){
        tail->next = newNode;
        tail = newNode; 
    }else{
        bantu = head;
        while (bantu != NULL && newNode->info > bantu->next->info){
            bantu = bantu->next;
        }
        newNode->next = bantu->next;
        bantu->next = newNode;
    }
}

void hapusnode(int info_hapus){
    node *hapus;
    bantu = head;

    while(bantu->next->info != info_hapus && bantu != NULL ){
        bantu = bantu->next;
    }

    hapus = bantu->next;
    bantu->next = hapus->next;
    hapus->next = NULL;
    delete(hapus);
}

int main(){

    LitsKosong();
    sisipNode(11);
    sisipNode(92);
    sisipNode(100);
    sisipNode(39);
    sisipNode(29);
    printList();
    hapusnode(92);
    printList();
}