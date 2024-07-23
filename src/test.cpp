#include <iostream>
#include <conio.h>
#include "console.hpp"

using namespace std;

int main() {
    Console con;
    keyState stan;
    char c;
    while (c != 'c') {
        stan = con.getKey(VK_CAPITAL);
        cout << stan.pressed << ' ' << stan.toggled << endl;
        c = getch();
    }
    return 0;
}