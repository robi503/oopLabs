#pragma once

#include "CarService.h" 

void printMenu();
void run();
void printCar(const Car* car);
void printCars(MyList* l);
void printCarValidationMessage(int result);
void addCarPrompt(CarService* cs);
void modifyCarPrompt(CarService* cs);
void rentCarPrompt(CarService* cs);
void returnCarPrompt(CarService* cs);
int selectCriteriaPrompt();
void filterCarsPrompt(CarService* cs);
void sortCarsPrompt(CarService* cs);
void addDummy(CarService* cs);