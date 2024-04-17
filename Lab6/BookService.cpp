#include "BookService.h"
#include <algorithm>
#include <random>

void BookService::addBook(const std::string& title, const std::string& author, const std::string& genre, int year) {
    Book newBook(title, author, genre, year);
    for (const Book& book : repo.getAll()) {
        std::string message = "Book with title '" + title + "', author '" + author + "', genre '" + genre + "', year '" + std::to_string(year) + "' already exists in the repository.";
        if (newBook == book) {
            throw std::runtime_error(message);
        }
    }
    repo.add(newBook);
}

int BookService::addBookToCart(const std::string& title)
{
    try {
        Book book = getBookByTitle(title);
        bookCart.addBook(book);
        return bookCart.getNumberOfBooks();
    }
    catch (const std::exception) {
        throw;
    }
}

int BookService::emptyCart()
{
    bookCart.emptyCart();
    return bookCart.getNumberOfBooks();
}

int BookService::generateCart(int n)
{
    int numBooks = repo.getAll().size();
    if (numBooks == 0) {
        throw std::runtime_error("There are no books to be added to the cart.");
    }
    
    std::mt19937 mt{ std::random_device{}() };
    std::uniform_int_distribution<> dist(0, numBooks - 1);

    for (int i = 0; i < n; ++i) {
        // Generate a random index within the range of number of books in the repository
        int randomIndex = dist(mt);

        // Retrieve the book at the random index from the repository
        Book randomBook = repo.getOne(randomIndex);

        // Add the random book to the cart
        bookCart.addBook(randomBook);
    }
    return bookCart.getNumberOfBooks();
}

void BookService::exportCart(const std::string& fileName)
{
    bookCart.exportCart(fileName);
}

void BookService::deleteBook(int pos) {
    try {
        repo.remove(pos);
    }catch (const std::exception) {
        throw;
    }
}


void BookService::modifyBook(const int pos, const std::string& newTitle, const std::string& newAuthor, const std::string& newGenre, int newYear) {
    Book newBook(newTitle, newAuthor, newGenre, newYear);
    for (const Book& book : repo.getAll()) {
        std::string message = "Book with title '" + newTitle + "', author '" + newAuthor + "', genre '" + newGenre + "', year '" + std::to_string(newYear) + "' already exists in the repository.";
        if (newBook == book) {
            throw std::runtime_error(message);
        }
    }
    try {
        repo.modify(pos, newBook);
    }catch (const std::exception) {
        throw;
    }
}

const std::vector<Book>& BookService::getAllBooks() const {
    return repo.getAll();
}

const Book& BookService::getBookByTitle(std::string title) const{
    for (const Book& book : repo.getAll()) {
        if (title == book.getTitle()) {
            return book;
        }
    }
    throw std::runtime_error("Book with title '" + title + "' not found.");
}

const std::vector<Book> BookService::filterByGenre(std::string genre) const
{
    std::vector<Book> filteredBooks;
    for (const Book& book : repo.getAll()) {
        if (genre == book.getGenre()) {
            filteredBooks.push_back(book);
        }
    }
    return filteredBooks;
}

const std::vector<Book> BookService::filterByYear(int year) const
{
    std::vector<Book> filteredBooks;
    for (const Book& book : repo.getAll()) {
        if (year == book.getYear()) {
            filteredBooks.push_back(book);
        }
    }
    return filteredBooks;
}

const std::vector<Book> BookService::sortBooks(bool(*cmpFct)(const Book&, const Book&)) const
{
    std::vector<Book> sortedBooks;
    int n = repo.getAll().size();
    for (int i = 0; i < n; i++) {
        sortedBooks.push_back(repo.getOne(i));
    }

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (cmpFct(sortedBooks[j], sortedBooks[j + 1])) {
                std::swap(sortedBooks[j], sortedBooks[j + 1]);
            }
        }
    }
    return sortedBooks;
}

bool BookService::compareBooksByTitle(const Book& book1, const Book& book2)
{
    return book1.getTitle() > book2.getTitle();
}

bool BookService::compareBooksByAuthor(const Book& book1, const Book& book2)
{
    return book1.getAuthor() > book2.getAuthor();
}


bool BookService::compareBooksByYearAndGenre(const Book& book1, const Book& book2)
{
    if (book1.getYear() != book2.getYear()) {
        return book1.getYear() > book2.getYear();
    }
    return book1.getGenre() > book2.getGenre();
}
