#include "project.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

Book::Book() {
    title = "";
    author = "";
    publicationYear = 2000;
    rating = 3;
    available = true;
}

Book::Book(string bookTitle, string bookAuthor, int year, int bookRating) {
    title = bookTitle;
    author = bookAuthor;

    if (isValidYear(year)) {
        publicationYear = year;
    } else {
        publicationYear = 2000;
    }

    if (isValidRating(bookRating)) {
        rating = bookRating;
    } else {
        rating = 3;
    }

    available = true;
}

string Book::getTitle() const {
    return title;
}

string Book::getAuthor() const {
    return author;
}

int Book::getPublicationYear() const {
    return publicationYear;
}

int Book::getRating() const {
    return rating;
}

bool Book::isAvailable() const {
    return available;
}

void Book::markCheckedOut() {
    available = false;
}

void Book::markReturned() {
    available = true;
}

bool Book::isValidYear(int year) {
    return year >= 1900 && year <= 2100;
}

bool Book::isValidRating(int rating) {
    return rating >= 1 && rating <= 5;
}

bool Book::isValidTitle(const string& title) {
    return !title.empty();
}

BookShelf::BookShelf() {
    count = 0;
}

bool BookShelf::addBook(const Book& book) {
    if (!Book::isValidTitle(book.getTitle()) || count >= MAX_BOOKS) {
        return false;
    }

    books[count] = book;
    count++;
    return true;
}

int BookShelf::getCount() const {
    return count;
}

Book BookShelf::getBookAt(int index) const {
    if (index < 0 || index >= count) {
        return Book();
    }

    return books[index];
}

Book* BookShelf::getBooks() {
    return books;
}

const Book* BookShelf::getBooks() const {
    return books;
}

int BookShelf::findBookByTitle(const string& title) const {
    for (int i = 0; i < count; i++) {
        if (books[i].getTitle() == title) {
            return i;
        }
    }

    return -1;
}

void BookShelf::sortByTitle() {
    for (int start = 0; start < count - 1; start++) {
        int minIndex = start;

        for (int i = start + 1; i < count; i++) {
            if (books[i].getTitle() < books[minIndex].getTitle()) {
                minIndex = i;
            }
        }

        Book temp = books[start];
        books[start] = books[minIndex];
        books[minIndex] = temp;
    }
}

BookNode::BookNode(const Book& book) {
    data = book;
    next = nullptr;
}

ReadingList::ReadingList() {
    head = nullptr;
}

ReadingList::~ReadingList() {
    clear();
}

void ReadingList::insertFront(const Book& book) {
    BookNode* newNode = new BookNode(book);
    newNode->next = head;
    head = newNode;
}

int ReadingList::countBooks() const {
    int total = 0;
    const BookNode* current = head;

    while (current != nullptr) {
        total++;
        current = current->next;
    }

    return total;
}

BookNode* ReadingList::findBook(const string& title) {
    BookNode* current = head;

    while (current != nullptr) {
        if (current->data.getTitle() == title) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

const BookNode* ReadingList::findBook(const string& title) const {
    const BookNode* current = head;

    while (current != nullptr) {
        if (current->data.getTitle() == title) {
            return current;
        }
        current = current->next;
    }

    return nullptr;
}

bool ReadingList::markBookCheckedOut(const string& title) {
    BookNode* found = findBook(title);

    if (found == nullptr) {
        return false;
    }

    found->data.markCheckedOut();
    return true;
}

bool ReadingList::removeBookByTitle(const string& title) {
    if (head == nullptr) {
        return false;
    }

    if (head->data.getTitle() == title) {
        BookNode* nodeToRemove = head;
        head = head->next;
        delete nodeToRemove;
        return true;
    }

    BookNode* current = head;

    while (current->next != nullptr) {
        if (current->next->data.getTitle() == title) {
            BookNode* nodeToRemove = current->next;
            current->next = nodeToRemove->next;
            delete nodeToRemove;
            return true;
        }
        current = current->next;
    }

    return false;
}

void ReadingList::clear() {
    BookNode* current = head;

    while (current != nullptr) {
        BookNode* nextNode = current->next;
        delete current;
        current = nextNode;
    }

    head = nullptr;
}

bool ReadingList::isEmpty() const {
    return head == nullptr;
}

double CatalogReport::calculateAverageRating(const Book books[], int count) {
    if (books == nullptr || count <= 0) {
        return 0.0;
    }

    int total = 0;
    for (int i = 0; i < count; i++) {
        total += books[i].getRating();
    }

    return static_cast<double>(total) / count;
}

int CatalogReport::readCatalogFile(const string& filename, Book books[], int maxItems) {
    if (books == nullptr || maxItems <= 0) {
        return 0;
    }

    ifstream in(filename);
    if (!in.is_open()) {
        return 0;
    }

    int count = 0;

    while (count < maxItems) {
        string line;
        if (!getline(in, line)) {
            break;
        }

        if (line.empty()) {
            continue;
        }

        string title;
        string author;
        int year = 0;
        int rating = 0;
        int availableFlag = 0;

        stringstream lineStream(line);
        string titleField;
        string authorField;
        string yearField;
        string ratingField;
        string availableField;

        getline(lineStream, titleField, '|');
        getline(lineStream, authorField, '|');
        getline(lineStream, yearField, '|');
        getline(lineStream, ratingField, '|');
        getline(lineStream, availableField, '|');

        if (!titleField.empty() && !authorField.empty() && !yearField.empty() && !ratingField.empty() && !availableField.empty()) {
            title = titleField;
            author = authorField;
            year = stoi(yearField);
            rating = stoi(ratingField);
            availableFlag = stoi(availableField);
        } else {
            stringstream fallbackStream(line);
            if (!(fallbackStream >> title >> author >> year >> rating >> availableFlag)) {
                continue;
            }
        }

        Book book(title, author, year, rating);
        if (availableFlag == 1) {
            book.markReturned();
        } else {
            book.markCheckedOut();
        }

        books[count] = book;
        count++;
    }

    return count;
}

bool CatalogReport::writeCatalogReport(const string& filename, const Book books[], int count) {
    if (books == nullptr || count < 0) {
        return false;
    }

    ofstream out(filename);
    if (!out.is_open()) {
        return false;
    }

    out << fixed << setprecision(2);
    out << "Catalog Report" << endl;
    out << "Title Author Year Rating Status" << endl;

    for (int i = 0; i < count; i++) {
        out << books[i].getTitle() << " "
            << books[i].getAuthor() << " "
            << books[i].getPublicationYear() << " "
            << books[i].getRating() << " "
            << (books[i].isAvailable() ? "available" : "checked out")
            << endl;
    }

    out << "Average rating: " << calculateAverageRating(books, count) << endl;
    return true;
}

int CatalogReport::findBookByTitle(const Book books[], int count, const string& title) {
    if (books == nullptr || count <= 0) {
        return -1;
    }

    for (int i = 0; i < count; i++) {
        if (books[i].getTitle() == title) {
            return i;
        }
    }

    return -1;
}

int CatalogReport::findHighestRatedBookIndex(const Book books[], int count) {
    if (books == nullptr || count <= 0) {
        return -1;
    }

    int highestIndex = 0;
    int highestRating = books[0].getRating();

    for (int i = 1; i < count; i++) {
        if (books[i].getRating() > highestRating) {
            highestRating = books[i].getRating();
            highestIndex = i;
        }
    }

    return highestIndex;
}

bool isValidMenuChoice(int choice) {
    return choice >= 0 && choice <= 4;
}

void printMenu() {
    cout << "\nLibrary Tracker Menu" << endl;
    cout << "1. Show a sample shelf" << endl;
    cout << "2. Show a reading list" << endl;
    cout << "3. Load catalog from file" << endl;
    cout << "4. Show catalog report" << endl;
    cout << "0. Exit" << endl;
    cout << "Choose an option: ";
}

void printBook(const Book& book) {
    cout << book.getTitle() << " by " << book.getAuthor()
         << " (" << book.getPublicationYear() << ")"
         << " Rating: " << book.getRating()
         << " Status: " << (book.isAvailable() ? "available" : "checked out")
         << endl;
}
