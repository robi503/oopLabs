#pragma once

#include <string.h>
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct Car {
	char licensePlate[255];
	char model[255];
	char category[255];
	int rented;
}Car;

extern const char counties[][3];

/*
Create a new car
*/
Car createCar(const char licensePlate[255], const char model[255], const char category[255]);

/*
 Dealocate memory occupied by a car
*/
void destroyCar(Car* c);

/*
 * Ensures that the format of a license plate is valid
 *
 * This function validates whether a given license plate follows a specific format:
 * - The license plate must consist of 7 characters.
 * - The first two characters must represent a valid county abbreviation.
 * - The third and fourth characters must represent a number between 1 and 99.
 * - The last three characters must be letters (uppercase or lowercase).
 *
 * @param licensePlate The string containing the license plate to be validated.
 *
 * @return Returns 1 if the license plate is valid according to the specified format,
 *         and 0 otherwise.
*/
int validateLicensePlate(const char licensePlate[255]);

/*
Validates a car

@return - 0 if car is ok
		 - 1 if licensePlate is wrong
		 - 2 if model is wrong
		 - 3 if category is wrong
*/
int validateCar(Car c);

/*
Compares two cars alphabetically by model

@return - < 0 if car a is less than car b
		-if > 0 then it indicates car b is less than car a
		- 0 then it indicates car a is equal to car b
*/
int compareCarsByModel(const Car a, const Car b);

/*
Compares two cars alphabetically by category

@return - < 0 if car a is less than car b
		-if > 0 then it indicates car b is less than car a
		- 0 then it indicates car a is equal to car b
*/
int compareCarsByCategory(const Car a, const Car b);

void testCar();
void testPlate();
void testCompare();
void testAllCar();