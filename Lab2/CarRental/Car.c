#include "Car.h"


const char counties[][3] = {
    "AB", "AR", "AG", "0B", "BC", "BH", "BN", "BT", "BV", "BR", "BZ",
    "CS", "CL", "CJ", "CT", "CV", "DB", "DJ", "GL", "GR", "GJ",
    "HR", "HD", "IL", "IS", "IF", "MM", "MH", "MS", "NT", "OT",
    "PH", "SM", "SJ", "SB", "SV", "TR", "TM", "TL", "VS", "VL", "VN"
};

Car* createCar(const char* licensePlate, const char* model, const char* category) {
    Car* car = malloc(sizeof(Car));
    if (car){
        car->licensePlate = _strdup(licensePlate);
        for (int i = 0; i < strlen(car->licensePlate); i++) {
            car->licensePlate[i] = toupper(car->licensePlate[i]);
        }
        car->model = _strdup(model);
        car->category = _strdup(category);
        car->rented = 0;
    }
    return car;
}

void destroyCar(Car* c) {
    free(c->licensePlate);
    free(c->model); 
    free(c->category); 
    free(c);
}


int validateLicensePlate(const char* licensePlate) {
    // Check if the license plate length is valid
    if (strlen(licensePlate) != 7) {
        return 1;
    }

    // Extracting county abbreviation
    char county[3];
    strncpy(county, licensePlate, 2);
    county[2] = '\0';

    int validCounty = 0;
    for (int i = 0; i < sizeof(counties) / sizeof(counties[0]); ++i) {
        if (strcmp(county, counties[i]) == 0) {
            validCounty = 1;
            break;
        }
    }
    if (!validCounty) {
        return 1;
    }

    // Extracting number part of the license plate
    char number[3];
    strncpy(number, licensePlate + 2, 2);
    number[2] = '\0';

    // Converting the number part to an integer and checking its validity
    int num = atoi(number);
    if (num < 1 || num > 99) {
        return 1;
    }

    // Extracting letter part of the license plate
    char letters[4];
    strncpy(letters, licensePlate + 4, 3);
    letters[3] = '\0';

    // Checking if the letter part contains only letters
    for (int i = 0; i < 3; ++i) {
        if (!((letters[i] >= 'A' && letters[i] <= 'Z') || (letters[i] >= 'a' && letters[i] <= 'z'))) {
            return 1;
        }
    }

    // If all checks passed, the license plate is valid
    return 0;
}

int validateCar(Car* c) {
    if (validateLicensePlate(c->licensePlate)) {
        return 1;
    }
    if (strlen(c->model) == 0) {
        return 2;
    }
    if (strlen(c->category) == 0) {
        return 3;
    }
    return 0;
}

int compareCarsByModel(const Car* a, const Car* b) {
    return strcmp(a->model, b->model);
}

int compareCarsByCategory(const Car* a, const Car* b) {
    return strcmp(a->category, b->category);
}

void testPlate() {
    assert(validateLicensePlate("AR99XYS") == 0);
    assert(validateLicensePlate("SV10MNO") == 0);

    assert(validateLicensePlate("") == 1);        
    assert(validateLicensePlate("AB123CDE") == 1);
    assert(validateLicensePlate("AB12CD") == 1);   

    assert(validateLicensePlate("XY123AB") == 1);  
    assert(validateLicensePlate("12B123C") == 1); 
    assert(validateLicensePlate("AB0CDYZ") == 1);
    assert(validateLicensePlate("AB100CD") == 1);

    assert(validateLicensePlate("AB1234Y") == 1); 
    assert(validateLicensePlate("AB1234XY") == 1);
}


void testCar() {
    Car* car = createCar("cJ10aBb","BMW X6", "suv");
    assert(validateCar(car) == 0);
    destroyCar(car);
    car = createCar("c10aBb", "BMW X6", "suv");
    assert(validateCar(car) == 1);
    destroyCar(car);
    car = createCar("cj100aBb", "BMW X6", "suv");
    assert(validateCar(car) == 1);
    destroyCar(car);
    car = createCar("cj1aBb", "BMW X6", "suv");
    assert(validateCar(car) == 1);
    destroyCar(car);
    car = createCar("cj10aBbb", "BMW X6", "suv");
    assert(validateCar(car) == 1);
    destroyCar(car);
    car = createCar("cj10a", "BMW X6", "suv");
    assert(validateCar(car) == 1);
    destroyCar(car);
    car = createCar("cj10ab1", "BMW X6", "suv");
    assert(validateCar(car) == 1);
    destroyCar(car);
    car = createCar("cj10abc", "", "suv");
    assert(validateCar(car) == 2);
    destroyCar(car);
    car = createCar("cj10abc", "BMW X6", "");
    assert(validateCar(car) == 3);
    destroyCar(car);
}

void testCompare() {
    Car* car1 = createCar("AB10XYZ", "BMW X6", "SUV");
    Car* car2 = createCar("BC20ABC", "Audi A4", "Sedan");
    Car* car3 = createCar("AG30DEF", "Tesla Model S", "Electric");
    Car* car4 = createCar("DE40GHI", "Audi Q5", "SUV");

    // Test cases for comparing cars by model names
    assert(compareCarsByModel(car1, car2) > 0); 
    assert(compareCarsByModel(car2, car3) < 0); 
    assert(compareCarsByModel(car3, car4) > 0); 
    assert(compareCarsByModel(car1, car4) > 0); 

    assert(compareCarsByCategory(car1, car2) < 0);
    assert(compareCarsByCategory(car2, car3) > 0);
    assert(compareCarsByCategory(car3, car4) < 0);
    assert(compareCarsByCategory(car1, car4) == 0);

    destroyCar(car1);
    destroyCar(car2);
    destroyCar(car3);
    destroyCar(car4);
}

void testAllCar() {
    testCar();
    testPlate();
    testCompare();
}