#include <iostream>
#include <fstream>
using namespace std;

struct CarType{
    enum {MAX_CHAR_LEN=100};
    char carName[MAX_CHAR_LEN];
    double mpg;
    int cylinders;
    double displacement;
    double horsepower;
    double weight;
    double acceleration;
    int model;
    char origin[MAX_CHAR_LEN];
    bool isValid; 
    CarType();
};

CarType::CarType() {
    for (int index = 0; index < MAX_CHAR_LEN; index++){
      carName[index]= '\0';
    }
    mpg = 0;
    cylinders = 0;
    displacement = 0;
    horsepower = 0;
    weight = 0;
    acceleration = 0;
    model = 0;
    for (int index = 0; index < MAX_CHAR_LEN; index++){
      origin[index]= '\0';
    }
    isValid = false; 
}

const int MAX_CARS=500;
CarType readCar(ifstream &inFile){
    CarType car; 
    inFile.get(car.carName, CarType::MAX_CHAR_LEN, ';');
    inFile.ignore(100,';');
    inFile >> car.mpg;
    inFile.ignore(100,';');
    inFile >> car.cylinders;
    inFile.ignore(100,';');
    inFile >> car.displacement;
    inFile.ignore(100,';');
    inFile >> car.horsepower;
    inFile.ignore(100,';');
    inFile >> car.weight;
    inFile.ignore(100,';');
    inFile >> car.acceleration;
    inFile.ignore(100,';');
    inFile >> car.model;
    inFile.ignore(100,';');
    inFile >> car.origin;
    inFile.ignore(100,'\n');
    car.isValid = !inFile.eof();
    return car;
}

int readCarData(CarType carArray[]) {
    ifstream carFile("cars.txt");
    int numCars = 0;
    while(carFile.peek() != EOF && numCars < MAX_CARS) {
        carArray[numCars] = readCar(carFile);
        numCars++;
    }
    return numCars;
}
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

double readDouble(const char prompt[]){
    double temp = 0;
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

void printCars(CarType carArray[]){
  for (int index = 0; index < MAX_CARS; index++){
    bool valid = carArray[index].isValid;
    if (valid){
      cout << "Index " << index << ": ";
      cout << carArray[index].carName << "; " << carArray[index].mpg << "; " << carArray[index].cylinders << "; " << carArray[index].displacement << "; " << carArray[index].horsepower << "; " << carArray[index].weight << "; " << carArray[index].acceleration << "; " << carArray[index].model << "; " << carArray[index].origin << endl;
    }
  }
}


void printCarsByOrigin(CarType carArray[], string origin){
  CarType newCarArray[500];
  for (int index = 0; index < MAX_CARS; index++){
    bool valid = carArray[index].isValid;
    if (valid && carArray[index].origin == origin){
      newCarArray[index] = carArray[index];
    }
  }
  printCars(newCarArray);
}


void removeCar(CarType carArray[]){
  int indexToRemove = readInt("enter an index to remove: ");
  if(indexToRemove < MAX_CARS && carArray[indexToRemove].isValid){
    carArray[indexToRemove].isValid = false;
  }
}



void addCar(CarType carArray[]){
  int index = 0;
  while(index < MAX_CARS && carArray[index].isValid){
    index++;
  }
  if(index == MAX_CARS){
    cout << "Database is full" << endl;
  }else{
    carArray[index].isValid = true;
    cout << "enter the car name: " << endl;
    cin.ignore(100, '\n');
    cin.getline(carArray[index].carName, MAX_CARS); 
    carArray[index].mpg = readDouble("enter the miles per gallon: ");
    carArray[index].cylinders = readInt("enter the number of cylinders: ");
    carArray[index].displacement = readDouble("enter the displacement: ");
    carArray[index].horsepower = readDouble("enter the horsepower: ");
    carArray[index].weight = readDouble("enter the weight: ");
    carArray[index].acceleration = readDouble("enter the acceleration: ");
    carArray[index].model = readInt("enter the model: ");
    cout << "enter the origin: " << endl;
    cin.ignore(100, '\n');
    cin.getline(carArray[index].origin, MAX_CARS);
  }
}

void displayMenu(CarType carArray[]){
  int userInput = 0;
  while (userInput != 5){
    userInput = readInt("enter the number of the option you wish to choose:\n(1) Display the car list\n(2) Remove a car from the list\n(3) Add a car to the list\n(4) display cars by origin\n(5) quit");
    if (userInput == 1){
      printCars(carArray);
    }
    if (userInput == 2){
      removeCar(carArray);
    }
    if (userInput == 3){
      addCar(carArray);
    }
    if (userInput == 4){
      string origin;
      cout << "Enter an origin to search by: " << endl;
      cin >> origin;
      printCarsByOrigin(carArray, origin);
    }
    if(userInput == 5){
      cout << "goodbye";
    }
  }
}
int main() {
    CarType carArray[500];
    readCarData(carArray);
    displayMenu(carArray);
    return 0;
}
