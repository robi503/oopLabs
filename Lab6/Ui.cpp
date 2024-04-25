#include "Ui.h"

void Ui::printMenu() const {
    std::cout << "Menu:\n";
    std::cout << "1. Add book\n";
    std::cout << "2. Modify book\n";
    std::cout << "3. Delete book\n";
    std::cout << "4. Get all books\n";
    std::cout << "5. Get book by title\n";
    std::cout << "6. Filter books\n";
    std::cout << "7. Sort books\n";
    std::cout << "8. Add to cart\n";
    std::cout << "9. Generate cart\n";
    std::cout << "u. Undo\n";
    std::cout << "e. Empty cart\n";
    std::cout << "x. Export cart\n";
    std::cout << "a. Add dummy\n";
    std::cout << "q. Quit\n";
}

Ui::Ui() : service {new FileRepo("books.txt")}{ }

void Ui::handleAdd() {
    std::string title, author, genre;
    int year;

    std::cout << "Enter title: ";
    std::getline(std::cin, title);

    std::cout << "Enter author: ";
    std::getline(std::cin, author);

    std::cout << "Enter genre: ";
    std::getline(std::cin, genre);

    std::string yearStr;
    std::cout << "Enter year: ";
    std::getline(std::cin, yearStr);

    try {
        year = std::stoi(yearStr);
        service.addBook(title, author, genre, year);
        std::cout << "Book added successfully!\n";
    }
    catch (const std::invalid_argument) {
        std::cout << "Invalid year input. Please enter a valid integer for the year.\n";
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << "\n";
    }
}


void Ui::handleModify()
{
    printAllBooks();
    std::cout << "Enter book you wish to modify:\n";
    int position = -1;
    std::string posStr;
    std::getline(std::cin, posStr);
    try {
        position = std::stoi(posStr);
    }
    catch (const std::invalid_argument) {
        std::cout << "Invalid input. Please enter a valid integer.\n";
        return;
    }

    std::string title, author, genre;
    int year;

    std::cout << "Enter title: ";
    std::getline(std::cin, title);

    std::cout << "Enter author: ";
    std::getline(std::cin, author);

    std::cout << "Enter genre: ";
    std::getline(std::cin, genre);

    std::string yearStr;
    std::cout << "Enter year: ";
    std::getline(std::cin, yearStr);

    try {
        year = std::stoi(yearStr);
        service.modifyBook(position, title, author, genre, year);
        std::cout << "Book modified successfully!\n";
    }catch (const std::invalid_argument) {
        std::cout << "Invalid year input. Please enter a valid integer for the year.\n";
    }catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}

void Ui::handleDelete()
{
    printAllBooks();
    std::cout << "Enter book you wish to delete:\n";
    int position = -1;
    std::string posStr;
    std::getline(std::cin, posStr);
    try {
        position = std::stoi(posStr);
    }
    catch (const std::invalid_argument) {
        std::cout << "Invalid input. Please enter a valid integer.\n";
        return;
    }
    try {
        service.deleteBook(position);
        std::cout << "Book deleted successfully!\n";
    }catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}

void Ui::printAllBooks() const {
    std::cout << "All books:\n";
    for (size_t i = 0; i < service.getAllBooks().size(); i++) {
        std::cout << "[" << i << "]" << service.getAllBooks()[i].toString();
    }
}

void Ui::handleAddToCart()
{
    std::cout << "Enter the title of the book:\n";
    std::string title;
    std::getline(std::cin, title);
    try {
        std::cout << "Books in cart: " << service.addBookToCart(title) << "\n";
    }
    catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}

void Ui::handleGetOne() const
{
    std::cout << "Enter the title of the book:\n";
    std::string title;
    std::getline(std::cin, title);
    try {
        std::cout << service.getBookByTitle(title).toString();
    }catch (const std::exception& e) {
        std::cout << e.what() << "\n";
    }
}

void Ui::handleEmptyCart()
{
    std::cout << service.emptyCart() << "\n";
}

void Ui::handleFilter() const
{
    std::cout << "Enter the criteria you want to filter by:\n";
    std::string criteria;
    std::getline(std::cin, criteria);
    if (criteria != "genre" && criteria != "year") {
        std::cout << "Valid criteria are: genre, year\n";
        return;
    }
    if (criteria == "genre") {
        std::cout << "Enter the genre you want to filter by:\n";
        std::string genre;
        std::getline(std::cin, genre);
        const std::vector<Book> books = service.filterByGenre(genre);
        for (const Book& book : books) {
            std::cout << book.toString();
        }
    }
    if (criteria == "year") {
        std::cout << "Enter the year you want to filter by:\n";
        std::string yearStr;
        std::getline(std::cin, yearStr);
        try {
            int year = std::stoi(yearStr);
            const std::vector<Book> books = service.filterByYear(year);
            for (const Book& book : books) {
                std::cout << book.toString();
            }
        }
        catch (const std::invalid_argument) {
            std::cout << "Invalid input. Please enter a valid integer.\n";
            return;
        }
    }
}

void Ui::handleGenerateCart()
{
    std::cout << "Enter the number of books to add:\n";
    std::string nStr;
    std::getline(std::cin, nStr);
    try {
        int n = std::stoi(nStr);
        std::cout << service.generateCart(n) << "\n";
    }
    catch (const std::invalid_argument) {
        std::cout << "Invalid input. Please enter a valid integer.\n";
        return;
    }
    catch (const std::runtime_error& e) {
        std::cout << e.what() << "\n";
        return;
    }
}

void Ui::handleSort() const
{
    std::cout << "Enter the criteria you want to sort by:\n";
    std::string criteria;
    std::getline(std::cin, criteria);
    if (criteria != "title" && criteria != "author" && criteria != "year") {
        std::cout << "Valid criteria are: title, author, year\n";
        return;
    }
    if (criteria == "title") {
        const std::vector<Book> books = service.sortBooks(BookService::compareBooksByTitle);
        for (const Book& book : books) {
            std::cout << book.toString();
        }
    }
    if (criteria == "year") {
        const std::vector<Book> books = service.sortBooks(BookService::compareBooksByYearAndGenre);
        for (const Book& book : books) {
            std::cout << book.toString();
        }
    }
    if (criteria == "author") {
        const std::vector<Book> books = service.sortBooks(BookService::compareBooksByAuthor);
        for (const Book& book : books) {
            std::cout << book.toString();
        }
    }
}

void Ui::handleExportCart()
{
    std::cout << "Enter the file name where you want to export:\n";
    std::string fileName;
    std::getline(std::cin, fileName);

    if (fileName.size() < 4 || fileName.substr(fileName.size() - 4) != ".csv") {
        std::cout << "Error: File name must end with '.csv'. Please provide a valid file name.\n";
        return;
    }

    service.exportCart(fileName);
}


void Ui::addDummy() {
    service.addBook("To Kill a Mockingbird", "Harper Lee", "Fiction", 1960);
    service.addBook("1984", "George Orwell", "Dystopian fiction", 1949);
    service.addBook("The Great Gatsby", "F. Scott Fitzgerald", "Fiction", 1925);
    service.addBook("Pride and Prejudice", "Jane Austen", "Romance", 1813);
    service.addBook("The Catcher in the Rye", "J.D. Salinger", "Fiction", 1951);
}

void Ui::handleUndo()
{
    try {
        service.undo();
        std::cout << "Undo successful\n";
    }
    catch (const std::exception &e){
        std::cout << e.what() << std::endl;
    }
}

void Ui::run() {
    while (running) {
        printMenu();
        char choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        switch (choice) {
        case '1':
            handleAdd();
            break;
        case '2':
            handleModify();
            break;
        case '3':
            handleDelete();
            break;
        case '4':
            printAllBooks();
            break;
        case '5':
            handleGetOne();
            break;
        case '6':
            handleFilter();
            break;
        case '7':
            handleSort();
            break;
        case '8':
            handleAddToCart();
            break;
        case '9':
            handleGenerateCart();
            break;
        case 'u':
            handleUndo();
            break;
        case 'e':
            handleEmptyCart();
            break;
        case 'x':
            handleExportCart();
            break;
        case 'a':
            addDummy();
            break;
        case 'q':
            running = false;
            std::cout << "Exiting...\n";
            break;
        default:
            std::cout << "Invalid choice. Please try again.\n";
            break;
        }
    }
}
