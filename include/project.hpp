#ifndef PROJECT_HPP
#define PROJECT_HPP

#include <string>

const int MAX_BOOKS = 10;

class Book {
private:
    std::string title;
    std::string author;
    int publicationYear;
    int rating;
    bool available;

public:
    Book();
    Book(std::string bookTitle, std::string bookAuthor, int year, int bookRating);

    std::string getTitle() const;
    std::string getAuthor() const;
    int getPublicationYear() const;
    int getRating() const;
    bool isAvailable() const;

    void markCheckedOut();
    void markReturned();

    static bool isValidYear(int year);
    static bool isValidRating(int rating);
    static bool isValidTitle(const std::string& title);
};

class BookShelf {
private:
    Book books[MAX_BOOKS];
    int count;

public:
    BookShelf();

    bool addBook(const Book& book);
    int getCount() const;
    Book getBookAt(int index) const;
    Book* getBooks();
    const Book* getBooks() const;
    int findBookByTitle(const std::string& title) const;
    void sortByTitle();
};

class BookNode {
public:
    Book data;
    BookNode* next;

    explicit BookNode(const Book& book);
};

class ReadingList {
private:
    BookNode* head;

public:
    ReadingList();
    ReadingList(const ReadingList& other) = delete;
    ReadingList& operator=(const ReadingList& other) = delete;
    ~ReadingList();

    void insertFront(const Book& book);
    int countBooks() const;
    BookNode* findBook(const std::string& title);
    const BookNode* findBook(const std::string& title) const;
    bool markBookCheckedOut(const std::string& title);
    bool removeBookByTitle(const std::string& title);
    void clear();
    bool isEmpty() const;
};

class CatalogReport {
public:
    static double calculateAverageRating(const Book books[], int count);
    static int readCatalogFile(const std::string& filename, Book books[], int maxItems);
    static bool writeCatalogReport(const std::string& filename, const Book books[], int count);
    static int findBookByTitle(const Book books[], int count, const std::string& title);
    static int findHighestRatedBookIndex(const Book books[], int count);
};

bool isValidMenuChoice(int choice);
void printMenu();
void printBook(const Book& book);

#endif
