#include "Repo.h"

void Repo::add(const Book& elem) {
    elems.push_back(elem);
}

void Repo::modify(int pos, const Book& newElem) {
    if (pos < 0 || pos >= elems.size()) {
        throw std::out_of_range("Invalid position");
    }
    elems[pos] = newElem;
}

void Repo::remove(int pos) {
    if (pos < 0 || pos >= elems.size()) {
        throw std::out_of_range("Invalid position");
    }
    elems.erase(elems.begin() + pos);
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