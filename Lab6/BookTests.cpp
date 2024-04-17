#include <iostream>
#include <assert.h>
#include "Book.h"
#include "BookTests.h"

void testBook() {
    // Create a Book object
    Book book("To Kill a Mockingbird", "Harper Lee", "Fiction", 1960);

    // Test getters
    assert(book.getTitle() == "To Kill a Mockingbird");
    assert(book.getAuthor() == "Harper Lee");
    assert(book.getGenre() == "Fiction");
    assert(book.getYear() == 1960);

    // Test toString method
    std::string expectedInfo = "Title: To Kill a Mockingbird; Author: Harper Lee; Genre: Fiction; Year: 1960\n";
    assert(book.toString() == expectedInfo);

    // Test setters
    book.setTitle("1984");
    book.setAuthor("George Orwell");
    book.setGenre("Dystopian fiction");
    book.setYear(1949);

    // Verify changes
    assert(book.getTitle() == "1984");
    assert(book.getAuthor() == "George Orwell");
    assert(book.getGenre() == "Dystopian fiction");
    assert(book.getYear() == 1949);
}

void testCopyConstructor() {
    // Create a book object
    Book originalBook("Original Title", "Original Author", "Original Genre", 2022);

    // Copy the book using the copy constructor
    Book copiedBook(originalBook);

    // Check if the copied book has the same values as the original one
    assert(copiedBook.getTitle() == originalBook.getTitle());
    assert(copiedBook.getAuthor() == originalBook.getAuthor());
    assert(copiedBook.getGenre() == originalBook.getGenre());
    assert(copiedBook.getYear() == originalBook.getYear());
}

void testEquals() {
    Book book1("Title", "Author", "Genre", 2022);
    Book book2("Title", "Author", "Genre", 2022);
    assert(book1 == book2);

    Book book3("Different Title", "Author", "Genre", 2022);
    assert(!(book1 == book3));

    Book book4("Title", "Different Author", "Genre", 2022);
    assert(!(book1 == book4));

    Book book5("Title", "Author", "Different Genre", 2022);
    assert(!(book1 == book5));

    Book book6("Title", "Author", "Genre", 2023);
    assert(!(book1 == book6));
}


void testAllBook() {
    testEquals();
    testBook();
    testCopyConstructor();
}