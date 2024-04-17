#include "BookCartTests.h"
#include "BookCart.h"
#include <assert.h>
#include <sstream>

void testAddToCart() {
    BookCart cart;

    Book book1("Title 1", "Author 1", "Genre 1", 2000);
    Book book2("Title 2", "Author 2", "Genre 2", 2001);

    cart.addBook(book1);
    cart.addBook(book2);

    assert(cart.getNumberOfBooks() == 2);
}

void testEmpty() {
    BookCart cart;

    cart.addBook(Book("Title 1", "Author 1", "Genre 1", 2000));
    cart.addBook(Book("Title 2", "Author 2", "Genre 2", 2001));

    cart.emptyCart();

    assert(cart.getNumberOfBooks() == 0);
}

void testExport() {
    // Create a BookCart object
    BookCart cart;

    // Add some books to the cart
    cart.addBook(Book("Book 1", "Author 1", "Genre 1", 2000));
    cart.addBook(Book("Book 2", "Author 2", "Genre 2", 2001));
    cart.addBook(Book("Book 3", "Author 3", "Genre 3", 2002));

    // Export the cart to a CSV file
    std::string fileName = "test_export.csv";

    cart.exportCart(fileName);

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

void testAllBookCart() {
    testAddToCart();
    testEmpty();
    testExport();
}


