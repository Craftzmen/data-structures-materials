#include <iostream>

using namespace std;

class BookNodeItem {
public:
    string bookItemTitle;
    string bookItemAuthor;
    int bookItemISBNNumber;
    BookNodeItem* nextBookItem;
    
    BookNodeItem(string title, string author, int isbn) {
        bookItemTitle = title;
        bookItemAuthor = author;
        bookItemISBNNumber = isbn;
        nextBookItem = nullptr;
    }
};

class LibraryManagementSystem {
private:
    BookNodeItem* listHead;
    
public:
    LibraryManagementSystem() {
        listHead = nullptr;
    }
    
    ~LibraryManagementSystem() {
        BookNodeItem* tempVar = listHead;
        while (tempVar != nullptr) {
            BookNodeItem* nextNode = tempVar->nextBookItem;
            delete tempVar;
            tempVar = nextNode;
        }
    }
    
    void displayAllBookItems() {
        if (listHead == nullptr) {
            cout << "No books available." << endl;
            return;
        }
        
        BookNodeItem* tempVar = listHead;
        cout << "Books in the list:" << endl;
        while (tempVar != nullptr) {
            cout << "Title: " << tempVar->bookItemTitle << endl;
            cout << "Author: " << tempVar->bookItemAuthor << endl;
            cout << "ISBN Number: " << tempVar->bookItemISBNNumber << endl;
            tempVar = tempVar->nextBookItem;
        }
    }
    
    void insertInBookListItems(string bookItemTitle, string bookItemAuthor, int bookItemISBNNumber) {
        BookNodeItem* newBookNodeItem = new BookNodeItem(bookItemTitle, bookItemAuthor, bookItemISBNNumber);

        if (listHead == nullptr) {
            listHead = newBookNodeItem;
        } else {
            BookNodeItem* tempVar = listHead;
            while (tempVar->nextBookItem != nullptr) {
                tempVar = tempVar->nextBookItem;
            }
            tempVar->nextBookItem = newBookNodeItem;
        }
        cout << "Book added successfully." << endl;
    }
    
    void searchForABookItem(int targetISBNItem) {
        if (listHead == nullptr) {
            cout << "No books available." << endl;
            return;
        }
        
        BookNodeItem* tempVar = listHead;
        while (tempVar != nullptr) {
            if (tempVar->bookItemISBNNumber == targetISBNItem) {
                cout << "Book with ISBN " << targetISBNItem << " found." << endl;
                cout << "Title: " << tempVar->bookItemTitle << endl;
                cout << "Author: " << tempVar->bookItemAuthor << endl;
                return;
            }
            tempVar = tempVar->nextBookItem;
        }
        cout << "Book with ISBN " << targetISBNItem << " not found." << endl;
    }
    
    void deleteInBookListItem(int targetISBNItem) {
        if (listHead == nullptr) {
            cout << "No books available." << endl;
            return;
        }
        
        BookNodeItem* tempVar = listHead;
        BookNodeItem* prevVar = nullptr;

        while (tempVar != nullptr && tempVar->bookItemISBNNumber != targetISBNItem) {
            prevVar = tempVar;
            tempVar = tempVar->nextBookItem;
        }
        
        if (tempVar == nullptr) {
            cout << "Book with ISBN " << targetISBNItem << " not found." << endl;
            return;
        }
        
        if (prevVar == nullptr) {
            listHead = tempVar->nextBookItem;
        } else {
            prevVar->nextBookItem = tempVar->nextBookItem;
        }
        
        delete tempVar;
        cout << "Book with ISBN " << targetISBNItem << " deleted successfully." << endl;
    }
    
    void countBookItems() {
        int itemCount = 0;
        BookNodeItem* tempVar = listHead;
        while (tempVar != nullptr) {
            itemCount++;
            tempVar = tempVar->nextBookItem;
        }
        cout << "Total number of books: " << itemCount << endl;
    }
    
    void findOldestNewestBookItems() {
        if (listHead == nullptr) {
            cout << "No books available." << endl;
            return;
        }
        
        BookNodeItem* oldestBookItem = listHead;
        BookNodeItem* newestBookItem = listHead;
        BookNodeItem* tempVar = listHead->nextBookItem;

        while (tempVar != nullptr) {
            if (tempVar->bookItemISBNNumber < oldestBookItem->bookItemISBNNumber) {
                oldestBookItem = tempVar;
            }
            if (tempVar->bookItemISBNNumber > newestBookItem->bookItemISBNNumber) {
                newestBookItem = tempVar;
            }
            tempVar = tempVar->nextBookItem;
        }

        cout << "Oldest Book:" << endl;
        cout << "Title: " << oldestBookItem->bookItemTitle << endl;
        cout << "Author: " << oldestBookItem->bookItemAuthor << endl;
        cout << "ISBN Number: " << oldestBookItem->bookItemISBNNumber << endl;

        cout << "Newest Book:" << endl;
        cout << "Title: " << newestBookItem->bookItemTitle << endl;
        cout << "Author: " << newestBookItem->bookItemAuthor << endl;
        cout << "ISBN Number: " << newestBookItem->bookItemISBNNumber << endl;
    }
};

int main() {
    LibraryManagementSystem library;
    int choiceOption;
    string bookItemTitle, bookItemAuthor;
    int bookItemISBNNumber;
    
    do {
        cout << "\nLibrary Management System:" << endl;
        cout << "1. Insert a new book" << endl;
        cout << "2. Display all books" << endl;
        cout << "3. Search for a book by ISBN number" << endl;
        cout << "4. Delete a book by ISBN number" << endl;
        cout << "5. Count total number of books" << endl;
        cout << "6. Find the oldestBookItem and newestBookItem book" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter your choiceOption: ";
        cin >> choiceOption;

        switch (choiceOption) {
            case 1:
                cout << "Enter book Item Title: ";
                cin.ignore();
                getline(cin, bookItemTitle);
                cout << "Enter book Item Author: ";
                getline(cin, bookItemAuthor);
                cout << "Enter book Item ISBN number: ";
                cin >> bookItemISBNNumber;
                library.insertInBookListItems(bookItemTitle, bookItemAuthor, bookItemISBNNumber);
                break;
            case 2:
                library.displayAllBookItems();
                break;
            case 3:
                cout << "Enter book Item ISBN number to search: ";
                cin >> bookItemISBNNumber;
                library.searchForABookItem(bookItemISBNNumber);
                break;
            case 4:
                cout << "Enter book Item ISBN number to delete: ";
                cin >> bookItemISBNNumber;
                library.deleteInBookListItem(bookItemISBNNumber);
                break;
            case 5:
                library.countBookItems();
                break;
            case 6:
                library.findOldestNewestBookItems();
                break;
            case 7:
                cout << "Exiting library management program." << endl;
                break;
            default:
                cout << "Invalid choice option. Please try again Boooyaaahhhh." << endl;
        }
    } while (choiceOption != 7);
    
    return 0;
}