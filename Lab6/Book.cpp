#include "Book.h"

// Constructor
Book::Book(const std::string& title, const std::string& author, const std::string& genre, int year) :
    title(title), author(author), genre(genre), year(year) {}

// Copy constructor
Book::Book(const Book& book) {
    this->title = book.title;
    this->author = book.author;
    this->genre = book.genre;
    this->year = book.year;
    std::cout << "Created copy \n";
}

// Getter methods
std::string Book::getTitle() const {
    return title;
}

std::string Book::getAuthor() const {
    return author;
}

std::string Book::getGenre() const {
    return genre;
}

int Book::getYear() const {
    return year;
}

// Setter methods
void Book::setTitle(const std::string& newTitle) {
    this->title = newTitle;
}

void Book::setAuthor(const std::string& newAuthor) {
    this->author = newAuthor;
}

void Book::setGenre(const std::string& newGenre) {
    this->genre = newGenre;
}

void Book::setYear(int newYear) {
    this->year = newYear;
}

bool Book::operator==(const Book& other) const
{
    return title == other.title && author == other.author && genre == other.genre && year == other.year;
}

// String representation method
std::string Book::toString() const {
    std::string info = "Title: " + title + "; ";
    info += "Author: " + author + "; ";
    info += "Genre: " + genre + "; ";
    info += "Year: " + std::to_string(year) + "\n";
    return info;
}
