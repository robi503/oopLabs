#pragma once

#include "MyList.h"

typedef struct CarService{
    MyList* l;
} CarService;

/*
  Create a car service
*/
CarService* createService(int type);

/*
  Destroy car service
*/
void destroyService(CarService* cs);

/*
  Creates a car and adds it to the list
    @return - -1 if the car couldn't be created
            - errorno if memory reallocation fails in the list
            - 1,2 or 3 if the car is not valid
            - 0 otherwise
*/
int add(CarService* cs, const char* licensePlate, const char* model, const char* category);

/*
    Sets a cars rented to 1
    @param pos - position of the car which will be rented
    @return - -1 if the position is not valid
            - 1 if the car was previously rented
            - 0 otherwise
*/
int rentCar(CarService* cs, int pos);

/*
    Sets a cars rented to 0
    @param pos - position of the car which will be returned
    @return - -1 if the position is not valid
            - 1 if the car was not previously rented
            - 0 otherwise
*/
int returnRentedCar(CarService* cs, int pos);

/*
  Modifies a car from the list
  @param pos - position of the element which will be modified
  @return - -1 if the position is not valid
          - 1,2 or 3 if the modifications to the car are not valid
          - 0 otherwise
*/
int modify(CarService* cs, const char* licensePlate, const char* model, const char* category, int pos);

/*
  Filters the list with cars with a specific model
  @param model - the model with which we filter
  @return The filtered list.
*/
MyList* filterCarsByModel(CarService* cs, const char* model);

/*
  Filters the list with cars with a specific category
  @param model - the category with which we filter
  @return The filtered list.
*/
MyList* filterCarsByCategory(CarService* cs, const char* category);

/*
  Swaps two cars from the given positions
*/
void swapCars(MyList* list, int i, int j);

/*
  Sorts the cars with a given compare function
  @param cmpFct - compare function used to compare two cars
  @param direction - direction in which to sort the cars
  @return The sorted list.
*/
MyList* sortCars(CarService* cs, int(*cmpFct)(Car*, Car*), int direction);

void testCreateDeleteService();
void testAddCars();
void testModifyCar();
void testRentReturnCar();
void testAllService();
void testFilterFunctions();
void testSortCars();