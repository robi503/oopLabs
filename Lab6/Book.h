#pragma once

#include <string>
#include <iostream>

class Book {
private:
    std::string title;
    std::string author;
    std::string genre;
    int year;

public:
    // Constructor
    Book(const std::string& title, const std::string& author, const std::string& genre, int year);

    // Copy constructor
    Book(const Book& book);

    // Getter methods
    std::string getTitle() const;
    std::string getAuthor() const;
    std::string getGenre() const;
    int getYear() const;

    // Setter methods
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setGenre(const std::string& genre);
    void setYear(int year);

    bool operator==(const Book& other) const;

    // String representation method
    std::string toString() const;
};

