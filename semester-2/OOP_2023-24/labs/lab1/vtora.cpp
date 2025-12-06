#include <iostream>

using namespace std;

struct Engine{
    int hp;
    int tq;
};

struct Car{
    char name[50];
    int y;
    Engine engine;

    void printCar(){
        cout << "Manufacturer: " << name << '\n';
        cout << "Horsepower: " << engine.hp << '\n';
        cout << "Torque: " << engine.tq << '\n';
    }

};
    void printCars(Car cars[], int n){
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (cars[i].engine.hp < cars[j].engine.hp) swap(cars[i],cars[j]);
            }
        }
        (cars[0].engine.tq > cars[1].engine.tq) ? cars[0].printCar() : cars[1].printCar();
    }

int main(){
    int n;
    cin >> n;
    Car cars[n];
    for (int i = 0; i < n; ++i) {
        cin >> cars[i].name;
        cin >> cars[i].y;
        cin >> cars[i].engine.hp;
        cin >> cars[i].engine.tq;
    }
    printCars(cars, n);
}