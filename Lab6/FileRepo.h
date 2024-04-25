#include "Repo.h"
#include <fstream>
#include <sstream>

class FileRepo : public Repo
{
private:
	std::string fileName;

public:
	FileRepo(std::string repoFileName);

	//Writes all books to the file
	void writeToFile();

	//Loads all books from the file
	void loadFromFile();

	// Add a new element to the repository
	void add(const Book& elem) override;

	// Modify an existing element in the repository
	// @return Returns the book without modifications
	const Book modify(int pos, const Book& newElem) override;

	// Remove an element from the repository by position
	// @return Returns the book which was deleted
	const Book remove(int pos) override;
};