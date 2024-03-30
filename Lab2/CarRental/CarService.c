#include "CarService.h"

CarService* createService(int type) {
	MyList* l = createEmpty(type);
	if (!l) {
		return NULL;
	}
	CarService* cs = malloc(sizeof(CarService));
	if (cs) {
		cs->l = l;
	}
	return cs;
}

void destroyService(CarService* cs) {
	destroyList(cs->l);
	free(cs);
}

int add(CarService* cs, const char* licensePlate, const char* model, const char* category) {
	Car* c = createCar(licensePlate, model, category);
	if (!c) {
		return -1;
	}

	int ok = validateCar(c);
	if (ok != 0) {
		destroyCar(c);
		return ok;
	}

	ok = pushBack(cs->l, c);
	return ok;
}

int modify(CarService* cs, const char* licensePlate, const char* model, const char* category, int pos) {
	Car* c = get(cs->l, pos);
	if (c) {
		Car* newCar = createCar(licensePlate, model, category);
		if (!newCar) {
			return -1;
		}

		int ok = validateCar(newCar);
		if (ok == 0) {
			destroyCar(c); // Free memory for the existing Car object
			cs->l->elems[pos] = newCar; // Update the Car object in the list
		}
		else {
			// Validation failed, free memory for the new Car object
			destroyCar(newCar);
		}

		return ok;
	}
	return -1;
}

int rentCar(CarService* cs, int pos) {
	Car* c = get(cs->l, pos);
	if (c) {
		if (c->rented == 1) {
			return 1;
		}
		c->rented = 1;
		return 0;
	}
	return -1;
}

int returnRentedCar(CarService* cs, int pos) {
	Car* c = get(cs->l, pos);
	if (c) {
		if (c->rented == 0) {
			return 1;
		}
		c->rented = 0;
		return 0;
	}
	return -1;
}

MyList* filterCarsByModel(CarService* cs, const char* model) {
	MyList* filteredList = createEmpty(cs->l->type);
	if (!filteredList) {
		return NULL;
	}

	for (int i = 0; i < size(cs->l); i++) {
		Car* car = get(cs->l, i); // Get the car at position i
		if (strcmp(car->model, model) == 0) { // Check if the car's model matches the specified model
			Car* copyCar = createCar(car->licensePlate, car->model, car->category); // Create a copy of the car
			if (!copyCar) {
				destroyList(filteredList); // Clean up and return NULL if failed to create the copy
				return NULL;
			}
			pushBack(filteredList, copyCar); // Add the copy of the car to the filtered list
		}
	}

	return filteredList; // Return the filtered list
}


MyList* filterCarsByCategory(CarService* cs, const char* category) {
	MyList* filteredList = createEmpty(cs->l->type); // Create an empty list to store filtered cars
	if (!filteredList) {
		return NULL; // Return NULL if failed to create the filtered list
	}

	// Iterate through the list of cars
	for (int i = 0; i < size(cs->l); i++) {
		Car* car = get(cs->l, i); // Get the car at position i
		if (strcmp(car->category, category) == 0) { // Check if the car's model matches the specified model
			Car* copyCar = createCar(car->licensePlate, car->model, car->category); // Create a copy of the car
			if (!copyCar) {
				destroyList(filteredList); // Clean up and return NULL if failed to create the copy
				return NULL;
			}
			pushBack(filteredList, copyCar); // Add the copy of the car to the filtered list
		}
	}

	return filteredList; // Return the filtered list
}

void swapCars(MyList* list, int i, int j) {
	ElemType temp = list->elems[i];
	list->elems[i] = list->elems[j];
	list->elems[j] = temp;
}


MyList* sortCars(CarService* cs, int(*cmpFct)(Car*, Car*), int direction) {
	MyList* sortedList = createEmpty(cs->l->type); // Create an empty list to store sorted cars
	if (!sortedList) {
		return NULL; // Return NULL if failed to create the sorted list
	}

	// Copy cars from original list to the sorted list
	for (int i = 0; i < size(cs->l); i++) {
		Car* car = get(cs->l, i);
		Car* copyCar = createCar(car->licensePlate, car->model, car->category);
		if (!copyCar) {
			destroyList(sortedList);
			return NULL;
		}
		pushBack(sortedList, copyCar);
	}

	int n = size(sortedList);
	for (int i = 0; i < n - 1; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			Car* car1 = get(sortedList, j);
			Car* car2 = get(sortedList, j + 1);
			// Compare cars using the provided sorting function
			if (direction * cmpFct(car1, car2) > 0) {
				swapCars(sortedList, j, j + 1);
			}
		}
	}

	return sortedList; // Return the sorted list
}


void testCreateDeleteService() {
	CarService* cs = createService(1);
	assert(cs != NULL);
	assert(size(cs->l) == 0);
	destroyService(cs);
}

void testAddCars() {
	CarService* cs = createService(1);

	int result = add(cs, "cj10abc", "Toyota", "Sedan");
	assert(result == 0);
	assert(size(cs->l) == 1);
	result = add(cs, "ab20abc", "Toyota", "Sedan");
	assert(result == 0);
	assert(size(cs->l) == 2);

	result = add(cs, "xyz789", "Honda", "SUV");
	assert(result == 1);
	result = add(cs, "cj10abc", "", "suv");
	assert(result == 2);
	result = add(cs, "cj10abc", "BMW X6", "");
	assert(result == 3);
	destroyService(cs);
}

void testModifyCar() {
	CarService* cs = createService(1);

	add(cs, "cj10abc", "Toyota", "Sedan");
	add(cs, "ab20abc", "Toyota", "Sedan");

	int result = modify(cs, "CJ99abc", "Toyota Camry", "SUV", 0);
	assert(result == 0);
	result = modify(cs, "cj99abc", "", "SUV", 0);
	assert(result == 2);
	assert(strcmp(get(cs->l, 0)->licensePlate, "CJ99ABC") == 0);
	assert(strcmp(get(cs->l, 0)->model, "Toyota Camry") == 0);
	assert(strcmp(get(cs->l, 0)->category, "SUV") == 0);

	result = modify(cs, "cj99abc", "Toyota Camry", "Sedan", 3);
	assert(result == -1);

	destroyService(cs);
}

void testRentReturnCar() {
	CarService* cs = createService(1);

	add(cs, "cj10abc", "Toyota", "Sedan");
	add(cs, "ab20abc", "Toyota", "Sedan");

	// Try to rent an unrented car at position 0
	int result = rentCar(cs, 0);
	assert(result == 0);
	assert(get(cs->l, 0)->rented == 1); 

	// Try to rent an already rented car at position 0
	result = rentCar(cs, 0);
	assert(result == 1); 

	// Try to rent an unrented car at position 1
	result = rentCar(cs, 1);
	assert(result == 0);
	assert(get(cs->l, 1)->rented == 1); 

	// Try to rent an already rented car at position 1
	result = rentCar(cs, 1);
	assert(result == 1);

	// Try to return a rented car at position 0
	result = returnRentedCar(cs, 0);
	assert(result == 0);
	assert(get(cs->l, 0)->rented == 0);

	// Try to return an already returned car at position 0
	result = returnRentedCar(cs, 0);
	assert(result == 1); 

	// Try to return a rented car at position 1
	result = returnRentedCar(cs, 1);
	assert(result == 0);
	assert(get(cs->l, 1)->rented == 0);

	// Try to return an already returned car at position 1
	result = returnRentedCar(cs, 1);
	assert(result == 1);

	destroyService(cs);
}

void testFilterFunctions() {
	CarService* cs = createService(1);
	assert(cs != NULL);

	add(cs, "AB12AXY", "Toyota", "Sedan");
	add(cs, "BC46AYZ", "Honda", "SUV");
	add(cs, "AR89AAB", "Toyota", "SUV");
	add(cs, "BH12ACD", "Honda", "Sedan");
	add(cs, "MS45AEF", "Toyota", "SUV");

	// Test filtering by model
	MyList* filteredByModel = filterCarsByModel(cs, "Toyota");
	assert(filteredByModel != NULL);
	assert(size(filteredByModel) == 3); // Expecting 3 cars with model "Toyota"

	// Test filtering by category
	MyList* filteredByCategory = filterCarsByCategory(cs, "SUV");
	assert(filteredByCategory != NULL);
	assert(size(filteredByCategory) == 3); // Expecting 3 cars with category "SUV"

	destroyList(filteredByModel);
	destroyList(filteredByCategory);
	destroyService(cs);
}

void testSortCars() {
	CarService* cs = createService(1);
	assert(cs != NULL);

	add(cs, "AB12AXY", "Tesla", "Sport");
	add(cs, "BC46AYZ", "Honda", "SUV");
	add(cs, "AR89AAB", "Ferrari", "Sport");
	add(cs, "BH12ACD", "Honda", "Sedan");
	add(cs, "MS45AEF", "Dacia", "SUV");

	// Sort cars by model name in ascending order
	MyList* sortedByModelAsc = sortCars(cs, compareCarsByModel, 1);
	assert(sortedByModelAsc != NULL);
	assert(size(sortedByModelAsc) == 5); // Expecting 5 cars in the sorted list
	// Check if the cars are sorted by model name in ascending order
	for (int i = 0; i < size(sortedByModelAsc) - 1; i++) {
		Car* car1 = get(sortedByModelAsc, i);
		Car* car2 = get(sortedByModelAsc, i + 1);
		assert(compareCarsByModel(car1, car2) <= 0);
	}
	destroyList(sortedByModelAsc);

	// Sort cars by model name in descending order
	MyList* sortedByModelDesc = sortCars(cs, compareCarsByModel, -1);
	assert(sortedByModelDesc != NULL);
	assert(size(sortedByModelDesc) == 5); // Expecting 5 cars in the sorted list
	// Check if the cars are sorted by model name in descending order
	for (int i = 0; i < size(sortedByModelDesc) - 1; i++) {
		Car* car1 = get(sortedByModelDesc, i);
		Car* car2 = get(sortedByModelDesc, i + 1);
		assert(compareCarsByModel(car1, car2) >= 0);
	}
	destroyList(sortedByModelDesc);

	// Sort cars by category in ascending order
	MyList* sortedByCategoryAsc = sortCars(cs, compareCarsByCategory, 1);
	assert(sortedByCategoryAsc != NULL);
	assert(size(sortedByCategoryAsc) == 5); // Expecting 5 cars in the sorted list
	// Check if the cars are sorted by category in ascending order
	for (int i = 0; i < size(sortedByCategoryAsc) - 1; i++) {
		Car* car1 = get(sortedByCategoryAsc, i);
		Car* car2 = get(sortedByCategoryAsc, i + 1);
		assert(compareCarsByCategory(car1, car2) <= 0);
	}
	destroyList(sortedByCategoryAsc);

	// Sort cars by category in descending order
	MyList* sortedByCategoryDesc = sortCars(cs, compareCarsByCategory, -1);
	assert(sortedByCategoryDesc != NULL);
	assert(size(sortedByCategoryDesc) == 5); // Expecting 5 cars in the sorted list
	// Check if the cars are sorted by category in descending order
	for (int i = 0; i < size(sortedByCategoryDesc) - 1; i++) {
		Car* car1 = get(sortedByCategoryDesc, i);
		Car* car2 = get(sortedByCategoryDesc, i + 1);
		assert(compareCarsByCategory(car1, car2) >= 0);
	}
	destroyList(sortedByCategoryDesc);

	destroyService(cs);
}


void testAllService() {
	testCreateDeleteService();
	testAddCars();
	testModifyCar();
	testRentReturnCar();
	testFilterFunctions();
	testSortCars();
}