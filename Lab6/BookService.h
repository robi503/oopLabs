#include "Repo.h"
#include "BookCart.h"

class BookService
{
private:
    Repo repo;
    BookCart bookCart;

public:
    // Creates a book and adds it to the repository
    // @throws throws runtime_error if the book already exists in the repository
    void addBook(const std::string& title, const std::string& author, const std::string& genre, int year);

    // Adds a book to the cart by title
    // @returns number of elements in the cart
    int addBookToCart(const std::string& title);

    // Empties the cart
    // @returns number of elements in the cart
    int emptyCart();

    // Add n random books from the repo
    // @returns number of elements in the cart
    int generateCart(int n);

    // Exports the contents of the cart to a file in a csv format
    void exportCart(const std::string& fileName);

    // Modifies a book from a specified position
    // @throws throws exception if position is not valid
    void modifyBook(const int pos, const std::string& newTitle, const std::string& newAuthor, const std::string& newGenre, int newYear);

    // Deletes a book from a position
    // @throws throws exception if position is not valid
    void deleteBook(const int pos);

    // Returns all books from the repository
    const std::vector<Book>& getAllBooks() const;

    // Returns a book by its title
    // @throws throws exception if book is not found
    const Book& getBookByTitle(std::string title) const;

    // Returns books from a certaing genre
    const std::vector<Book> filterByGenre(std::string genre) const;

    // Returns books from a certaing year
    const std::vector<Book> filterByYear(int year) const;

    // Returns the sorted books, by a certain compare function
    const std::vector<Book> sortBooks(bool(*cmpFct)(const Book&, const Book&)) const;

    // Compares two books by title
    static bool compareBooksByTitle(const Book& book1, const Book& book2);

    // Compares two books by author
    static bool compareBooksByAuthor(const Book& book1, const Book& book2);

    // Compares two books by year and genre
    static bool compareBooksByYearAndGenre(const Book& book1, const Book& book2);
};
