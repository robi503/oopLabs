#pragma once
#include "Book.h"
#include <Vector>


class Repo
{
private:
    std::vector<Book> elems;

public:
    // Add a new element to the repository
    virtual void add(const Book& elem);

    // Modify an existing element in the repository
    // @return Returns the book without modifications
    virtual const Book modify(int pos, const Book& newElem);

    // Remove an element from the repository by position
    // @return Returns the book which was deleted
    virtual const Book remove(int pos);

    // Get all elements from the repository
    const std::vector<Book>& getAll() const;

    // Get one element from the repository by position
    const Book& getOne(int pos) const;

    virtual ~Repo();
};
