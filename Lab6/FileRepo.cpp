#include "FileRepo.h"

FileRepo::FileRepo(std::string repoFileName) : Repo{ }, fileName{ repoFileName }
{
    loadFromFile();
}

void FileRepo::writeToFile()
{
    std::ofstream file(fileName);
    for (const Book& book: Repo::getAll()) {
        file << book.toString();
    }
    file.close();
}

void FileRepo::loadFromFile()
{
    std::ifstream file(fileName);
    std::string line;
    while (std::getline(file, line)) {
        // Use stringstream to parse the line
        std::stringstream ss(line);

        // Variables to store book information
        std::string title, author, genre;
        int year = 0;

        // Temporary variables for parsing
        std::string temp;

        // Parse the line using delimiters
        while (std::getline(ss, temp, ';')) {
            std::istringstream iss(temp);
            std::string key, value;

            // Extract key and value pairs
            if (std::getline(iss, key, ':') && std::getline(iss, value)) {
                // Trim leading and trailing whitespaces
                key.erase(0, key.find_first_not_of(" \t"));
                key.erase(key.find_last_not_of(" \t") + 1);
                value.erase(0, value.find_first_not_of(" \t"));
                value.erase(value.find_last_not_of(" \t") + 1);

                // Match keys and assign values
                if (key == "Title") {
                    title = value;
                }
                else if (key == "Author") {
                    author = value;
                }
                else if (key == "Genre") {
                    genre = value;
                }
                else if (key == "Year") {
                    year = std::stoi(value);
                }
            }
        }

        // Add the book to the repository
        Repo::add(Book(title, author, genre, year));
    }
    file.close();
}


void FileRepo::add(const Book& elem)
{
    Repo::add(elem);
    writeToFile();
}

const Book FileRepo::modify(int pos, const Book& newElem)
{
    const Book modifiedBook = Repo::modify(pos,  newElem);
    writeToFile();
    return modifiedBook;
}

const Book FileRepo::remove(int pos)
{
    const Book deletedBook = Repo::remove(pos);
    writeToFile();
    return deletedBook;
}