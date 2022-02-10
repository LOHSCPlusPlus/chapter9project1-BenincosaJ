#include <iostream>
using namespace std;

int readInt(const char prompt[]){
    int temp = 0;
    cout << prompt;
    cin >> temp;
    while (!cin) {
        cin.clear();
        cin.ignore(1000,'\n');
        cout << "Invalid Data!" << endl;
        cout << prompt;
        cin >> temp;
    }
    return temp;
}


int main() {
    int num = readInt("Enter an integer: ");
    num = readInt("Enter another integer: ");
}
