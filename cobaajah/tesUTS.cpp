#include <iostream>
using namespace std;

int main(){
int x = 10;
int y = 20;

int *p = &x;
int *q = &y;

p = q;

*q = 90;

cout << x << endl;
cout << y << endl;
cout << *p << endl;
cout << *q << endl;
}