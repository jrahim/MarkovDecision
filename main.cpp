//
// Created by jamal on 30/09/2018.
//

#include <iostream>
using namespace std;

void printit(int* num) {
    cout << *num;
}

int main() {
    int* num = new int;
    *num = 5;
    printit(num);
    return 0;
}