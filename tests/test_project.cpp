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

    out << "Blood Meridian|Cormac McCarthy|1965|5|1" << endl;
    out << "The Road|Cormac McCarthy|2006|5|0" << endl;
    out << "The Daily Stoic|Ryan Holiday|2016|4|1" << endl;
    out << "Call Of Cthulu|H.P. Lovecraft|1928|4|0" << endl;

    out.close();
}

// Week 1: Program Basics
void testWeek1ProgramBasics() {
    Book book("Blood Meridian", "Cormac McCarthy", 1965, 5);

    assert(book.getTitle() == "Blood Meridian");
    assert(book.getAuthor() == "Cormac McCarthy");
    assert(Book::isValidYear(1965));
    assert(!Book::isValidYear(1800));
    assert(Book::isValidRating(5));
    assert(!Book::isValidRating(6));
}

// Week 2: Decisions and Loops
void testWeek2DecisionsAndLoops() {
    assert(Book::isValidTitle("Blood Meridian"));
    assert(!Book::isValidTitle(""));
    assert(Book::isValidRating(1));
    assert(!Book::isValidRating(0));

    BookShelf shelf;
    assert(shelf.addBook(Book("Blood Meridian", "Cormac McCarthy", 1965, 5)));
    assert(shelf.addBook(Book("The Road", "Cormac McCarthy", 2006, 5)));
    assert(shelf.addBook(Book("The Daily Stoic", "Ryan Holiday", 2016, 4)));
    assert(shelf.getCount() == 3);
    assert(!shelf.addBook(Book("", "Unknown", 2000, 3)));
}

// Week 3: Functions and Program Design
void testWeek3FunctionsAndProgramDesign() {
    BookShelf shelf;
    shelf.addBook(Book("Blood Meridian", "Cormac McCarthy", 1965, 5));
    shelf.addBook(Book("The Road", "Cormac McCarthy", 2006, 5));
    shelf.addBook(Book("The Daily Stoic", "Ryan Holiday", 2016, 4));

    assert(shelf.findBookByTitle("The Road") == 1);
    assert(shelf.findBookByTitle("Missing") == -1);
    assert(nearlyEqual(CatalogReport::calculateAverageRating(shelf.getBooks(), shelf.getCount()), 4.6667));
}

// Week 4: Arrays, Searching, and Sorting
void testWeek4ArraysSearchingSorting() {
    BookShelf shelf;
    shelf.addBook(Book("Blood Meridian", "Cormac McCarthy", 1965, 5));
    shelf.addBook(Book("The Road", "Cormac McCarthy", 2006, 5));
    shelf.addBook(Book("The Daily Stoic", "Ryan Holiday", 2016, 4));

    shelf.sortByTitle();

    assert(shelf.getBookAt(0).getTitle() == "Blood Meridian");
    assert(shelf.getBookAt(1).getTitle() == "The Daily Stoic");
    assert(shelf.getBookAt(2).getTitle() == "The Road");
}

// Week 5: Strings and Structures
void testWeek5StringsAndStructures() {
    Book book("The Daily Stoic", "Ryan Holiday", 2016, 4);

    assert(book.getTitle() == "The Daily Stoic");
    assert(book.getAuthor() == "Ryan Holiday");
    assert(book.isAvailable());

    book.markCheckedOut();
    assert(!book.isAvailable());

    book.markReturned();
    assert(book.isAvailable());
}

// Week 6: Pointers, Dynamic Memory, and Linked Lists
void testWeek6LinkedLists() {
    ReadingList books;

    books.insertFront(Book("Blood Meridian", "Cormac McCarthy", 1965, 5));
    books.insertFront(Book("The Road", "Cormac McCarthy", 2006, 5));

    assert(books.countBooks() == 2);
    assert(books.findBook("The Road") != nullptr);
    assert(books.findBook("Missing") == nullptr);

    assert(books.markBookCheckedOut("Blood Meridian"));
    assert(books.removeBookByTitle("The Road"));
    assert(books.countBooks() == 1);
    assert(books.findBook("The Road") == nullptr);

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

    assert(count == 4);
    assert(books[0].getTitle() == "Blood Meridian");
    assert(books[1].getTitle() == "The Road");
    assert(nearlyEqual(CatalogReport::calculateAverageRating(books, count), 4.5));
    assert(CatalogReport::findBookByTitle(books, count, "Blood Meridian") == 0);
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
    assert(contents.find("Blood Meridian") != string::npos);
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
