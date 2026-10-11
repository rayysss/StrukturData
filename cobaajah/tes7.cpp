#include<iostream>
using namespace std;

const int kapasitas = 4;

// stack ll itu dinamis
// stack arrya itu statis

struct stack{
    int data[kapasitas];
    int top;
};

void buatStack(stack& s){
    s.top = -1;
}

bool isEmpty(stack& s){
    return s.top == -1;

}

bool isFull(stack& s){
    return s.top == kapasitas - 1;
}

bool push(stack& s, int nilai){
    if(isFull(s)){
        cout << "woi penuh ini stack bree" << endl;
        return false;
    }
    ++s.top; // dari yg awalnya min satu, jadinya index 0
    s.data[s.top] = nilai;
    return true;
}

void printStack(stack& s){
    if (isFull(s)){
        cout << "woi kapasitas data ini gada atau full jir" << endl;
        return;
    }
    cout << "Isi data stack sekarang" << endl;
    for (int i = s.top; i >= 0; --i){
        cout << "|" << s.data[i] << endl;
    }
}

int main(){
    stack s;
    buatStack(s);

    cout << "cek status awal banget" << endl;
    cout << "apakah kosong bree? " << (isEmpty(s) ? "Ya" : "Tidak") << endl;
    cout << "apakah full bree? " << (isFull(s) ? "Ya" : "Tidak") << endl;

    cout << "negpush data 10, 200, 45" << endl;
    push(s, 10);
    push(s, 200);
    push(s, 45);
    printStack(s);

    push(s, 214);
    cout << "cek status lagii bree" << endl;
    cout << "apakah kosong bree? " << (isEmpty(s) ? "Ya" : "Tidak") << endl;
    cout << "apakah full bree? " << (isFull(s) ? "Ya" : "Tidak") << endl;
    printStack(s);
}