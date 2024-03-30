#include "ui.h"

void printMenu() {
    printf("Car Rental System Menu\n\n");
    printf("1) Add a car\n");
    printf("2) Update existing car\n");
    printf("3) Rent a car\n");
    printf("4) Return a car\n");
    printf("5) View all cars\n");
    printf("6) View cars by given criteria (category, model)\n");
    printf("7) Sort cars by: model or category (ascending/descending)\n");
    printf("a) Add dummy\n");
    printf("q) Quit\n");
}

void run() {
    char option;
    int type = 0;
    printf("Enter 1 for dynamic list: \n");
    if (scanf(" %d", &type) != 1) {
        printf("Input error occurred.\n");
        return;
    }
    CarService* cs = createService(type);
    int run = 1;
    while (run) {
        printMenu();
        if (scanf(" %c", &option) != 1) {
            printf("Input error occurred.\n");
            break;
        }
        switch (option) {
        case '1':
            addCarPrompt(cs);
            break;
        case '2':
            modifyCarPrompt(cs);
            break;
        case '3':
            rentCarPrompt(cs);
            break;
        case '4':
            returnCarPrompt(cs);
            break;
        case '5':
            printCars(cs->l);
            break;
        case '6':
            filterCarsPrompt(cs);
            break;
        case '7':
            sortCarsPrompt(cs);
            break;
        case 'a':
            addDummy(cs);
            break;
        case 'q':
            printf("Exiting the program.\n");
            run = 0;
            destroyService(cs);
            break;
        default:
            printf("Invalid option. Try again.\n");
        }
    }
}

void printCar(const Car* car) {
    printf("License Plate: %s\n", car->licensePlate);
    printf("Model: %s\n", car->model);
    printf("Category: %s\n", car->category);
    if (car->rented) {
        printf("Rented: yes\n");
    }
    else {
        printf("Rented: no\n");
    }
}

int selectCriteriaPrompt() {
    char option;
    printf("Select criteria: \n");
    printf("1) Model\n");
    printf("2) Category\n");
    if (scanf(" %c", &option) != 1) {
        printf("Input error occurred.\n");
        return -1;
    }
    switch (option) {
    case '1':
        if (getchar() != '\n') {
            printf("Something went wrong.");
            return 0;
        }
        return 1;
    case '2':
        if (getchar() != '\n') {
            printf("Something went wrong.");
            return 0;
        }
        return 2;
    default:
        if (getchar() != '\n') {
            printf("Something went wrong.");
            return 0;
        }
        printf("Invalid option.\n");
        return -1;
    }
}


void printCars(MyList* l) {
    for (int i = 0; i < size(l); i++) {
        printf("[%d] ", i);
        printCar(get(l, i));
    }
}

void printCarValidationMessage(int result) {
    if (result == 0) {
        printf("Car added successfully!\n");
    }
    else if (result == 1) {
        printf("License plate is wrong.\n");
    }
    else if (result == 2) {
        printf("Model cannot be empty.\n");
    }
    else if (result == 3) {
        printf("Category cannot be empty.\n");
    }
}

void addCarPrompt(CarService* cs) {
    char licensePlate[20];
    char model[50];
    char category[20];

    if (getchar() != '\n'){
        printf("Something went wrong.");
        return;
    }
    printf("Enter license plate: ");
    fgets(licensePlate, sizeof(licensePlate), stdin);
    if (licensePlate[strlen(licensePlate) - 1] == '\n') {
        licensePlate[strlen(licensePlate) - 1] = '\0';
    }

    printf("Enter model: ");
    fgets(model, sizeof(model), stdin);
    if (model[strlen(model) - 1] == '\n') {
        model[strlen(model) - 1] = '\0';
    }

    printf("Enter category: ");
    fgets(category, sizeof(category), stdin);
    if (category[strlen(category) - 1] == '\n') {
        category[strlen(category) - 1] = '\0';
    }

    int result = add(cs, licensePlate, model, category);
    if (result == -1) {
        printf("Car cannot be created.\n");
    }
    else {
        printCarValidationMessage(result);
    }
}

void modifyCarPrompt(CarService* cs)
{
    if (getchar() != '\n') {
        printf("Something went wrong.");
        return;
    }

    printCars(cs->l);
    printf("Which car do you want to modify?\n");

    int index = -1;
    if (scanf("%d", &index) != 1) {
        printf("Invalid input. Please enter a valid index.\n");
        return;
    }

    if (getchar() != '\n') {
        printf("Something went wrong.");
        return;
    }
    char licensePlate[20];
    char model[50];
    char category[20];

    printf("Enter license plate: ");
    fgets(licensePlate, sizeof(licensePlate), stdin);
    if (licensePlate[strlen(licensePlate) - 1] == '\n') {
        licensePlate[strlen(licensePlate) - 1] = '\0';
    }

    printf("Enter model: ");
    fgets(model, sizeof(model), stdin);
    if (model[strlen(model) - 1] == '\n') {
        model[strlen(model) - 1] = '\0';
    }

    printf("Enter category: ");
    fgets(category, sizeof(category), stdin);
    if (category[strlen(category) - 1] == '\n') {
        category[strlen(category) - 1] = '\0';
    }

    int result = modify(cs, licensePlate, model, category, index);
    if (result == -1) {
        printf("Position is not valid.\n");
    }
    else {
        printCarValidationMessage(result);
    }
}

void rentCarPrompt(CarService* cs) {
    if (getchar() != '\n') {
        printf("Something went wrong.");
        return;
    }

    printCars(cs->l);
    printf("Which car do you want to rent?\n");

    int index = -1;
    if (scanf("%d", &index) != 1) {
        printf("Invalid input. Please enter a valid index.\n");
        return;
    }

    if (getchar() != '\n') {
        printf("Something went wrong.");
        return;
    }

    int result = rentCar(cs, index);
    if (result == -1) {
        printf("Position is invalid.\n");
    }
    else if (result == 1) {
        printf("Car is already rented.\n");
    }
    else {
        printf("Car rented successfully!\n");
    }
}

void returnCarPrompt(CarService* cs) {
    if (getchar() != '\n') {
        printf("Something went wrong.");
        return;
    }

    printCars(cs->l);
    printf("Which car do you want to rent?\n");

    int index = -1;
    if (scanf("%d", &index) != 1) {
        printf("Invalid input. Please enter a valid index.\n");
        return;
    }

    if (getchar() != '\n') {
        printf("Something went wrong.");
        return;
    }

    int result = returnRentedCar(cs, index);
    if (result == -1) {
        printf("Position is invalid.\n");
    }
    else if (result == 1) {
        printf("Car is not rented.\n");
    }
    else {
        printf("Car returned successfully!\n");
    }
}

void filterCarsPrompt(CarService* cs) {
    int opt = selectCriteriaPrompt();
    if (opt == 1) {
        char model[50];
        printf("Enter model: ");
        fgets(model, sizeof(model), stdin);
        if (model[strlen(model) - 1] == '\n') {
            model[strlen(model) - 1] = '\0';
        }
        MyList* fl = filterCarsByModel(cs, model);
        printCars(fl);
        destroyList(fl);
    }
    if (opt == 2) {
        char category[50];
        printf("Enter model: ");
        fgets(category, sizeof(category), stdin);
        if (category[strlen(category) - 1] == '\n') {
            category[strlen(category) - 1] = '\0';
        }
        MyList* fl = filterCarsByModel(cs, category);
        printCars(fl);
        destroyList(fl);
    }
}

void sortCarsPrompt(CarService* cs) {
    int opt = selectCriteriaPrompt();
    if (opt == 1) {
        printf("Enter direction: >0 for ascending, <0 for descending:\n");
        int direction = 0;
        if (scanf(" %d", &direction) != 1) {
            printf("Input error occurred.\n");
        }
        MyList* sl = sortCars(cs, compareCarsByModel, direction);
        printCars(sl);
        destroyList(sl);
    }
    if (opt == 2) {
        printf("Enter direction: <0 for ascending, >0 for descending:\n");
        int direction = 0;
        if (scanf(" %d", &direction) != 1) {
            printf("Input error occurred.\n");
        }
        MyList* sl = sortCars(cs, compareCarsByCategory, direction);
        printCars(sl);
        destroyList(sl);
    }
}

void addDummy(CarService* cs) {
    add(cs, "AB12AXY", "Tesla", "Sport");
    add(cs, "BC46AYZ", "Honda", "SUV");
    add(cs, "AR89AAB", "Ferrari", "Sport");
    add(cs, "BH12ACD", "Honda", "Sedan");
    add(cs, "MS45AEF", "Dacia", "SUV");
}