#include "Book.h"
#include <Vector>


class Repo
{
private:
    std::vector<Book> elems;

public:
    // Add a new element to the repository
    void add(const Book& elem);

    // Modify an existing element in the repository
    void modify(int pos, const Book& newElem);

    // Remove an element from the repository by position
    void remove(int pos);

    // Get all elements from the repository
    const std::vector<Book>& getAll() const;

    // Get one element from the repository by position
    const Book& getOne(int pos) const;
};
