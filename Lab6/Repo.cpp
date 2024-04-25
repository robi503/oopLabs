#include "Repo.h"

void Repo::add(const Book& elem) {
    elems.push_back(elem);
}

const Book Repo::modify(int pos, const Book& newElem) {
    if (pos < 0 || pos >= elems.size()) {
        throw std::out_of_range("Invalid position");
    }
    Book originalBook = elems[pos];
    elems[pos] = newElem;
    return originalBook;
}

const Book Repo::remove(int pos) {
    if (pos < 0 || pos >= elems.size()) {
        throw std::out_of_range("Invalid position");
    }
    Book removedBook = elems[pos];
    elems.erase(elems.begin() + pos);
    return removedBook;
}


const std::vector<Book>& Repo::getAll() const {
    return elems;
}

const Book& Repo::getOne(int pos) const{
    if (pos < 0 || pos >= elems.size()) {
        throw std::out_of_range("Invalid position");
    }
    return elems[pos];
}

Repo::~Repo() {}