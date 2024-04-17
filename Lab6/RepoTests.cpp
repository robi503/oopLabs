#include "Repo.h"
#include <assert.h>

// Test the add method of the Repo class
void testAdd() {
    Repo repo;
    Book book1("Title1", "Author1", "Genre1", 2022);
    repo.add(book1);
    assert(repo.getAll().size() == 1);
}

// Test the delete method of the Repo class
void testDelete() {
    Repo repo;
    Book book1("Title1", "Author1", "Genre1", 2022);
    Book book2("Title2", "Author2", "Genre2", 2022);
    repo.add(book1);
    repo.add(book2);
    repo.remove(0);
    assert(repo.getAll().size() == 1);
    assert(repo.getAll()[0].getTitle() == "Title2");
    bool ok = false;
    try {
        repo.remove(-1);
    }
    catch (const std::exception e) {
        ok = true;
    }
    assert(ok);
}

// Test the modify method of the Repo class
void testModify() {
    Repo repo;
    Book book1("Title1", "Author1", "Genre1", 2022);
    Book modifiedBook("Title2", "Author2", "Genre2", 2023);
    repo.add(book1);
    repo.modify(0, modifiedBook);
    assert(repo.getAll()[0].getTitle() == "Title2");
    bool ok = false;
    try {
        repo.modify(1,modifiedBook);
    }
    catch (const std::exception e) {
        ok = true;
    }
    assert(ok);
}

// Test the getAll method of the Repo class
void testGetAll() {
    Repo repo;
    Book book1("Title1", "Author1", "Genre1", 2022);
    Book book2("Title2", "Author2", "Genre2", 2023);
    repo.add(book1);
    repo.add(book2);
    assert(repo.getAll().size() == 2);
}

// Test the getOne method of the Repo class
void testGetOne() {
    Repo repo;
    Book book1("Title1", "Author1", "Genre1", 2022);
    Book book2("Title2", "Author2", "Genre2", 2023);
    repo.add(book1);
    repo.add(book2);
    assert(repo.getOne(1).getTitle() == "Title2");
    bool ok = false;
    try {
        repo.getOne(2);
    }
    catch (const std::exception e) {
        ok = true;
    }
    assert(ok);
}

// Run all tests for the Repo class
void testAllRepo() {
    testAdd();
    testDelete();
    testModify();
    testGetAll();
    testGetOne();
}