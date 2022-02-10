#include <iostream>
#include <fstream>
using namespace std;
// This file is ONLY an example of how to load a struct from a file
struct Bunny{
    enum {MAX_CHAR_LEN=100};
    char name[MAX_CHAR_LEN];
    double maxWeight;
    int yearRecognized;
    bool isRare;
    bool isValid;
    
};

const int MAX_BUNNIES=500;
Bunny readBunny(ifstream &inFile){
    Bunny bunny; 
    inFile.get(bunny.name, Bunny::MAX_CHAR_LEN, ';');
    inFile.ignore(100,';');
    inFile >> bunny.maxWeight;
    inFile.ignore(100,';');
    inFile >> bunny.yearRecognized;
    inFile.ignore(100,';');
    inFile >> bunny.isRare;
    inFile.ignore(100,'\n');
    // If we reached the end of the file while reading, then the entry is not valid
    bunny.isValid = !inFile.eof();
    return bunny;
}

int readBunnies(Bunny bunnies[]) {
    ifstream bunnyFile("bunnies.txt");
    int numBunnies = 0;
    while(bunnyFile.peek() != EOF && numBunnies < MAX_BUNNIES) {
        bunnies[numBunnies] = readBunny(bunnyFile);
        numBunnies++;
    }
    return numBunnies;
}

int main() {
    Bunny bunnies[MAX_BUNNIES]; 
    int num = readBunnies(bunnies);
    cout << "Nums: " << num << endl;
    printBunnies(bunnies, num);
    return 0;
}
