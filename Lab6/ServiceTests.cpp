#include "BookService.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include "ServiceTests.h"

// Test the addBook method of the BookService class
void testAddService() {
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    assert(service.getAllBooks().size() == 1);
    bool ok = false;
    try {
        service.addBook("Title1", "Author1", "Genre1", 2022);
    }
    catch (const std::exception) {
        ok = true;
    }
    assert(ok);
}

// Test the deleteBook method of the BookService class
void testDeleteService() {
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    service.deleteBook(0);
    assert(service.getAllBooks().size() == 0);
    bool ok = false;
    try {
        service.deleteBook(-1);
    }
    catch (const std::exception) {
        ok = true;
    }
    assert(ok);
}

// Test the modifyBook method of the BookService class
void testModifyService() {
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    service.modifyBook(0, "NewTitle", "NewAuthor", "NewGenre", 2023);
    assert(service.getAllBooks()[0].getTitle() == "NewTitle");
    bool ok = false;
    try {
        service.modifyBook(1,"Title2", "Author2", "Genre2", 2022);
    }
    catch (const std::exception) {
        ok = true;
    }
    assert(ok);
    ok = false;
    service.addBook("Title2", "Author2", "Genre2", 2022);
    try {
        service.modifyBook(0,"Title2", "Author2", "Genre2", 2022);
    }
    catch (const std::exception) {
        ok = true;
    }
    assert(ok);
}

// Test the getAllBooks method of the BookService class
void testGetAllService() {
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    service.addBook("Title2", "Author2", "Genre2", 2023);
    assert(service.getAllBooks().size() == 2);
}

// Test the getBookByTitle method of the BookService class
void testGetBookByTitleService() {
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    service.addBook("Title2", "Author2", "Genre2", 2023);

    // Test getting a book by an existing title
    Book book = service.getBookByTitle("Title1");
    assert(book.getTitle() == "Title1");

    // Test getting a book by a non-existing title
    bool exceptionThrown = false;
    try {
        service.getBookByTitle("NonExistingTitle");
    }
    catch (const std::exception) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

void testFilter()
{
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    service.addBook("Title2", "Author2", "Genre2", 2023);
    service.addBook("Title3", "Author3", "Genre1", 2023);

    const std::vector<Book> books = service.filterByGenre("Genre1");
    assert(books.size() == 2);
    assert(books[0].getTitle() == "Title1");
    assert(books[1].getTitle() == "Title3");

    const std::vector<Book> books1 = service.filterByYear(2023);
    assert(books1.size() == 2);
    assert(books1[0].getTitle() == "Title2");
    assert(books1[1].getTitle() == "Title3");
}

void testSort()
{
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    service.addBook("Title2", "Author2", "Genre2", 2023);
    service.addBook("Title3", "Author3", "Genre1", 2023);

    const std::vector<Book> sortedBooksByTitle = service.sortBooks(BookService::compareBooksByTitle);
    assert(sortedBooksByTitle.size() == 3);
    assert(sortedBooksByTitle[0].getTitle() == "Title1");
    assert(sortedBooksByTitle[1].getTitle() == "Title2");
    assert(sortedBooksByTitle[2].getTitle() == "Title3");

    const std::vector<Book> sortedBooksByAuthor = service.sortBooks(BookService::compareBooksByAuthor);
    assert(sortedBooksByAuthor.size() == 3);
    assert(sortedBooksByAuthor[0].getTitle() == "Title1");
    assert(sortedBooksByAuthor[1].getTitle() == "Title2");
    assert(sortedBooksByAuthor[2].getTitle() == "Title3");

    const std::vector<Book> sortedBooks = service.sortBooks(BookService::compareBooksByYearAndGenre);
    assert(sortedBooks.size() == 3);
    assert(sortedBooks[0].getTitle() == "Title1");
    assert(sortedBooks[1].getTitle() == "Title3");
    assert(sortedBooks[2].getTitle() == "Title2");
}

void testAddCart()
{
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    assert(service.addBookToCart("Title1") == 1);
    bool exceptionThrown = false;
    try {
        service.addBookToCart("Title2");
    }
    catch (const std::exception) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
}

void testEmptyCart()
{
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    assert(service.addBookToCart("Title1") == 1);
    assert(service.emptyCart() == 0);
}

void testExportCart()
{
    BookService service(new Repo);

    // Add some books to the cart
    service.addBook("Book 1", "Author 1", "Genre 1", 2000);
    service.addBook("Book 2", "Author 2", "Genre 2", 2001);
    service.addBook("Book 3", "Author 3", "Genre 3", 2002);

    service.addBookToCart("Book 1");
    service.addBookToCart("Book 2");
    service.addBookToCart("Book 3");

    // Export the cart to a CSV file
    std::string fileName = "test_export.csv";

    service.exportCart(fileName);

    // Open the exported file
    std::ifstream inFile(fileName);

    // Read and verify the contents of the CSV file
    std::string line;
    std::getline(inFile, line); // Skip header
    assert(line == "Title,Author,Genre,Year");

    int count = 0;
    while (std::getline(inFile, line)) {
        std::stringstream ss(line);
        std::string title, author, genre;
        int year;
        std::getline(ss, title, ',');
        std::getline(ss, author, ',');
        std::getline(ss, genre, ',');
        ss >> year;

        // Verify book data
        switch (count) {
        case 0:
            assert(title == "Book 1" && author == "Author 1" && genre == "Genre 1" && year == 2000);
            break;
        case 1:
            assert(title == "Book 2" && author == "Author 2" && genre == "Genre 2" && year == 2001);
            break;
        case 2:
            assert(title == "Book 3" && author == "Author 3" && genre == "Genre 3" && year == 2002);
            break;
        }
        count++;
    }

    // Close the file
    inFile.close();
}

void testGenerateCart()
{
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    service.addBook("Title2", "Author2", "Genre2", 2023);
    service.addBook("Title3", "Author3", "Genre1", 2023);
    assert(service.generateCart(3) == 3);
}

void testUndoAdd()
{
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    service.undo();
    assert(service.getAllBooks().size() == 0);
    bool ok = false;
    try {
        service.undo();
    }
    catch (std::out_of_range) {
        ok = true;
    }
    assert(ok);
}

void testUndoDelete()
{
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    service.deleteBook(0);
    service.undo();
    assert(service.getAllBooks().size() == 1);
    assert(service.getAllBooks()[0] == Book("Title1", "Author1", "Genre1", 2022));
}

void testUndoModify()
{
    BookService service(new Repo);
    service.addBook("Title1", "Author1", "Genre1", 2022);
    service.modifyBook(0, "NewTitle", "NewAuthor", "NewGenre", 2023);
    service.undo();
    assert(service.getAllBooks()[0] == Book("Title1", "Author1", "Genre1", 2022));
}


// Run all tests for the BookService class
void testAllService() {
    testAddService();
    testDeleteService();
    testModifyService();
    testGetAllService();
    testGetBookByTitleService();
    testFilter();
    testAddCart();
    testEmptyCart();
    testExportCart();
    testGenerateCart();
    testUndoAdd();
    testUndoDelete();
    testUndoModify();
    testSort();
}
