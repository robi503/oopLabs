#include "Repo.h"
#include "FileRepo.h"
#include <assert.h>
#include "RepoTests.h"

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
    Book deletedBook = repo.remove(0);
    assert(deletedBook == book1);
    assert(repo.getAll().size() == 1);
    assert(repo.getAll()[0].getTitle() == "Title2");
    bool ok = false;
    try {
        repo.remove(-1);
    }
    catch (std::out_of_range) {
        ok = true;
    }
    assert(ok);
    ok = false;
    try {
        repo.remove(1);
    }
    catch (std::out_of_range) {
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
    Book originalBook = repo.modify(0, modifiedBook);
    assert(originalBook == book1);
    assert(repo.getAll()[0].getTitle() == "Title2");
    bool ok = false;
    try {
        repo.modify(1,modifiedBook);
    }
    catch (std::out_of_range) {
        ok = true;
    }
    assert(ok);
    ok = false;
    try {
        repo.remove(-1);
    }
    catch (std::out_of_range) {
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
    catch (std::exception) {
        ok = true;
    }
    assert(ok);
}

int countLines(const std::string& filename) {
    std::ifstream file(filename);

    int lineCount = 0;
    std::string line;
    while (std::getline(file, line)) {
        ++lineCount;
    }\
    file.close();
    return lineCount;
}

void clearFile(const std::string& filename) {
    std::ofstream file(filename, std::ios::out | std::ios::trunc);
    file.close();
}

void testAddFile()
{
    FileRepo fileRepo("testFileRepo.txt");
    Book book("title", "author", "genre", 1);
    fileRepo.add(book);
    int c = countLines("testFileRepo.txt");
    assert(c == 1);
    clearFile("testFileRepo.txt");
}

void testDeleteFile()
{
    FileRepo fileRepo("testFileRepo.txt");
    Book book("title", "author", "genre", 1);
    fileRepo.add(book);
    Book deletedBook = fileRepo.remove(0);
    assert(book == deletedBook);
    int c = countLines("testFileRepo.txt");
    assert(c == 0);
    clearFile("testFileRepo.txt");
}

void testModifyFile()
{
    FileRepo fileRepo("testFileRepo.txt");
    Book book("title", "author", "genre", 1);
    Book book1("title1", "author1", "genre1", 1);
    fileRepo.add(book);
    Book modifiedBook = fileRepo.modify(0,book1);
    assert(book == modifiedBook);
    int c = countLines("testFileRepo.txt");
    assert(c == 1);
    assert(fileRepo.getOne(0) == book1);
    clearFile("testFileRepo.txt");
}

void testLoadFromFile()
{
    std::ofstream file("testFileRepo.txt", std::ios::out | std::ios::trunc);
    Book book("title", "author", "genre", 1);
    Book book1("title1", "author1", "genre1", 1);
    file << book.toString() << book1.toString();
    file.close();
    FileRepo fileRepo("testFileRepo.txt");
    int c = countLines("testFileRepo.txt");
    assert(c == 2);
    assert(fileRepo.getOne(0) == book);
    assert(fileRepo.getOne(1) == book1);
    clearFile("testFileRepo.txt");
}


// Run all tests for the Repo class
void testAllRepo() {
    testAdd();
    testDelete();
    testModify();
    testGetAll();
    testAddFile();
    testDeleteFile();
    testModifyFile();
    testLoadFromFile();
    testGetOne();
}