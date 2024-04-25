#include "BookCart.h"

void BookCart::addBook(const Book& book)
{
	books.push_back(book);
}

void BookCart::emptyCart()
{
	books.clear();
}

size_t BookCart::getNumberOfBooks() const
{
	return books.size();
}

void BookCart::exportCart(const std::string& fileName) const {
    std::ofstream outFile(fileName, std::ios_base::trunc);
    outFile << "Title,Author,Genre,Year\n";
    for (const Book& book : books) {
        outFile << book.getTitle() << ","
            << book.getAuthor() << ","
            << book.getGenre() << ","
            << book.getYear() << "\n";
    }
    outFile.close();
}