#include "project.hpp"
#include <cassert>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

bool nearlyEqual(double actual, double expected, double tolerance = 0.0001) {
    return fabs(actual - expected) <= tolerance;
}

void createTestCatalogFile(string filename) {
    ofstream out(filename);

    out << "Dune Herbert 1965 5 1" << endl;
    out << "Frankenstein Shelley 1818 4 0" << endl;
    out << "1984 Orwell 1949 5 1" << endl;

    out.close();
}

// Week 1: Program Basics
void testWeek1ProgramBasics() {
    Book book("Dune", "Herbert", 1965, 5);

    assert(book.getTitle() == "Dune");
    assert(book.getAuthor() == "Herbert");
    assert(Book::isValidYear(1965));
    assert(!Book::isValidYear(1800));
    assert(Book::isValidRating(5));
    assert(!Book::isValidRating(6));
}

// Week 2: Decisions and Loops
void testWeek2DecisionsAndLoops() {
    assert(Book::isValidTitle("Dune"));
    assert(!Book::isValidTitle(""));
    assert(Book::isValidRating(1));
    assert(!Book::isValidRating(0));

    BookShelf shelf;
    assert(shelf.addBook(Book("Dune", "Herbert", 1965, 5)));
    assert(shelf.addBook(Book("Frankenstein", "Shelley", 1818, 4)));
    assert(shelf.addBook(Book("1984", "Orwell", 1949, 5)));
    assert(shelf.getCount() == 3);
    assert(!shelf.addBook(Book("", "Unknown", 2000, 3)));
}

// Week 3: Functions and Program Design
void testWeek3FunctionsAndProgramDesign() {
    BookShelf shelf;
    shelf.addBook(Book("Dune", "Herbert", 1965, 5));
    shelf.addBook(Book("Frankenstein", "Shelley", 1818, 4));
    shelf.addBook(Book("1984", "Orwell", 1949, 5));

    assert(shelf.findBookByTitle("1984") == 2);
    assert(shelf.findBookByTitle("Missing") == -1);
    assert(nearlyEqual(CatalogReport::calculateAverageRating(shelf.getBooks(), shelf.getCount()), 4.6667));
}

// Week 4: Arrays, Searching, and Sorting
void testWeek4ArraysSearchingSorting() {
    BookShelf shelf;
    shelf.addBook(Book("Dune", "Herbert", 1965, 5));
    shelf.addBook(Book("1984", "Orwell", 1949, 5));
    shelf.addBook(Book("Frankenstein", "Shelley", 1818, 4));

    shelf.sortByTitle();

    assert(shelf.getBookAt(0).getTitle() == "1984");
    assert(shelf.getBookAt(1).getTitle() == "Dune");
    assert(shelf.getBookAt(2).getTitle() == "Frankenstein");
}

// Week 5: Strings and Structures
void testWeek5StringsAndStructures() {
    Book book("Pride and Prejudice", "Austen", 1813, 4);

    assert(book.getTitle() == "Pride and Prejudice");
    assert(book.getAuthor() == "Austen");
    assert(book.isAvailable());

    book.markCheckedOut();
    assert(!book.isAvailable());

    book.markReturned();
    assert(book.isAvailable());
}

// Week 6: Pointers, Dynamic Memory, and Linked Lists
void testWeek6LinkedLists() {
    ReadingList books;

    books.insertFront(Book("Dune", "Herbert", 1965, 5));
    books.insertFront(Book("1984", "Orwell", 1949, 5));

    assert(books.countBooks() == 2);
    assert(books.findBook("1984") != nullptr);
    assert(books.findBook("Missing") == nullptr);

    assert(books.markBookCheckedOut("Dune"));
    assert(books.removeBookByTitle("1984"));
    assert(books.countBooks() == 1);
    assert(books.findBook("1984") == nullptr);

    books.clear();
    assert(books.isEmpty());
}

// Week 7: File I/O and Integration
void testWeek7FileIO() {
    string inputFilename = "tests/resources/test_catalog_input.txt";
    string outputFilename = "tests/resources/test_catalog_report_output.txt";

    createTestCatalogFile(inputFilename);

    Book books[10];
    int count = CatalogReport::readCatalogFile(inputFilename, books, 10);

    assert(count == 3);
    assert(books[0].getTitle() == "Dune");
    assert(books[1].getTitle() == "Frankenstein");
    assert(nearlyEqual(CatalogReport::calculateAverageRating(books, count), 4.6667));
    assert(CatalogReport::findBookByTitle(books, count, "Dune") == 0);
    assert(CatalogReport::findBookByTitle(books, count, "Missing") == -1);
    assert(CatalogReport::findHighestRatedBookIndex(books, count) == 0);

    bool wroteReport = CatalogReport::writeCatalogReport(outputFilename, books, count);
    assert(wroteReport);

    ifstream in(outputFilename);
    assert(in.is_open());

    string contents;
    string line;
    while (getline(in, line)) {
        contents += line + "\n";
    }

    assert(contents.find("Catalog Report") != string::npos);
    assert(contents.find("Dune") != string::npos);
    assert(contents.find("available") != string::npos);
}

int main() {
    testWeek1ProgramBasics();
    testWeek2DecisionsAndLoops();
    testWeek3FunctionsAndProgramDesign();
    testWeek4ArraysSearchingSorting();
    testWeek5StringsAndStructures();
    testWeek6LinkedLists();
    testWeek7FileIO();

    cout << "All library tracker tests passed!" << endl;
    return 0;
}
