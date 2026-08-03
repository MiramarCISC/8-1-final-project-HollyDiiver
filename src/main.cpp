#include "project.hpp"
#include <iostream>
#include <string>

using namespace std;

int main() {
    int choice = -1;

    cout << "Library Tracker" << endl;
    cout << "A simple project for organizing and reviewing books." << endl;

    do {
        printMenu();
        cin >> choice;

        while (!isValidMenuChoice(choice)) {
            cout << "Invalid choice. Enter 0-4: ";
            cin >> choice;
        }

        switch (choice) {
            case 1: {
                BookShelf shelf;
                shelf.addBook(Book("Blood Meridian", "Cormac McCarthy", 1965, 5));
                shelf.addBook(Book("The Road", "Cormac McCarthy", 2006, 5));
                shelf.addBook(Book("The Daily Stoic", "Ryan Holiday", 2016, 4));
                shelf.addBook(Book("Call Of Cthulu", "H.P. Lovecraft", 1928, 4));

                cout << "Sample shelf contents:" << endl;
                for (int i = 0; i < shelf.getCount(); i++) {
                    printBook(shelf.getBookAt(i));
                }
                break;
            }

            case 2: {
                ReadingList list;
                list.insertFront(Book("Blood Meridian", "Cormac McCarthy", 1965, 5));
                list.insertFront(Book("The Road", "Cormac McCarthy", 2006, 5));

                cout << "Reading list contains " << list.countBooks() << " book(s)." << endl;
                list.markBookCheckedOut("Blood Meridian");
                cout << "Blood Meridian marked as checked out." << endl;
                break;
            }

            case 3: {
                Book books[MAX_BOOKS];
                int count = CatalogReport::readCatalogFile("data/catalog.txt", books, MAX_BOOKS);
                cout << "Loaded " << count << " book(s) from data/catalog.txt" << endl;
                break;
            }

            case 4: {
                Book books[MAX_BOOKS];
                int count = CatalogReport::readCatalogFile("data/catalog.txt", books, MAX_BOOKS);
                if (count > 0) {
                    CatalogReport::writeCatalogReport("catalog_report.txt", books, count);
                    cout << "Catalog report written to catalog_report.txt" << endl;
                }
                break;
            }

            case 0:
                cout << "Goodbye!" << endl;
                break;

            default:
                cout << "Unexpected choice." << endl;
                break;
        }

    } while (choice != 0);

    return 0;
}
