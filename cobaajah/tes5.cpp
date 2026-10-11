#include <iostream>
using namespace std;

struct Node
{
    int info;
    Node *prev;
    Node *next;
};

Node *head = nullptr;
Node *tail = nullptr;

bool listKosong()
{
    return head == nullptr;
}

void sisipNode(int info_baru)
{
    Node *new_node = new Node();
    new_node->info = info_baru;
    new_node->next = nullptr;
    new_node->prev = nullptr;

    if (listKosong())
    {
        head = new_node;
        tail = new_node;
    }
    else if (info_baru < head->info)
    {
        new_node->next = head;
        head->prev = new_node;
        head = new_node;
    }
    else if (info_baru >= tail->info)
    {
        new_node->prev = tail;
        tail->next = new_node;
        tail = new_node;
    }
    else
    {
        Node *temp = head;
        while (temp->next != nullptr && temp->next->info < info_baru)
        {
            temp = temp->next;
        }
        new_node->next = temp->next;
        new_node->prev = temp;
        temp->next->prev = new_node;
        temp->next = new_node;
    }
}

void printLinkedList()
{
    if (listKosong())
    {
        cout << "list masih kosong" << endl;
    }
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->info << ",";
        temp = temp->next;
    }
    cout << endl;
}

void hapusNode(int info_hapus)
{
    if (listKosong())
    {
        cout << "list masih kosong" << endl;
    }
    if (info_hapus == head->info)
    {
        Node *hapus = head;
        if (head == tail)
        {
            head = nullptr;
            tail = nullptr;
        }
        else
        {
            head = head->next;
            head->prev = nullptr;
        }
        delete hapus;
        cout << "Node" << info_hapus << "Berhasil dihapus" << endl;
        return;
    }

    Node *temp = head->next;
    while (temp != nullptr && temp->info != info_hapus)
    {
        temp = temp->next;
    }

    if (temp != nullptr)
    {
        if (temp->prev != nullptr)
        {
            temp->prev->next = temp->next; // melewati node yang mau dihapus dari sisi prev
        }
        if (temp->next != nullptr)
        {
            temp->next->prev = temp->prev; // melewati node yang mau dihapus dari sisi prev
        }

        if (temp == tail)
        {
            tail = temp->prev;
        }
        delete temp;
        cout << "Node " << info_hapus << " Berhasil dihapus" << endl;
    }
    else
    {
        cout << "Node " << info_hapus << " Tidak ditemukan" << endl;
    }
}

int main()
{
    system("cls");
    sisipNode(60);
    sisipNode(10);
    sisipNode(30);
    sisipNode(5);
    printLinkedList();
    hapusNode(100);
    printLinkedList();
    hapusNode(10);
    printLinkedList();
}