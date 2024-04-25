#include "Book.h"
#include <Vector>
#include <fstream>
#include <stdexcept>

class BookCart
{
private:
	std::vector<Book> books;

public:
	//Adds a book to the cart
	void addBook(const Book& book);

	//Empties the cart
	void emptyCart();

	//Returns the number of books in the cart
	size_t getNumberOfBooks() const;

	//Exports books from cart in a csv format
	void exportCart(const std::string& fileName) const;
};

