#include <bits/stdc++.h>

using namespace std;

// Class to represent a book
class Book
{
public:
    int id;
    string title;
    string author;
    bool isAvailable;

    Book(int id, const string &title, const string &author)
        : id(id), title(title), author(author), isAvailable(true) {}

    void displayDetails() const
    {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author
             << ", " << (isAvailable ? "Available" : "Checked Out") << endl;
    }
};

// Class to represent a library patron
class Patron
{
public:
    int id;
    string name;
    vector<int> checkedOutBooks;

    Patron(int id, const string &name) : id(id), name(name) {}

    void displayDetails() const
    {
        cout << "Patron ID: " << id << ", Name: " << name << endl;
        if (checkedOutBooks.empty())
        {
            cout << "No books checked out." << endl;
        }
        else
        {
            cout << "Checked out books IDs: ";
            for (int bookId : checkedOutBooks)
            {
                cout << bookId << " ";
            }
            cout << endl;
        }
    }

    void checkoutBook(int bookId)
    {
        checkedOutBooks.push_back(bookId);
    }

    void returnBook(int bookId)
    {
        auto it = find(checkedOutBooks.begin(), checkedOutBooks.end(), bookId);
        if (it != checkedOutBooks.end())
        {
            checkedOutBooks.erase(it);
        }
    }
};

// Class to represent the library
class Library
{
private:
    vector<Book> books;
    vector<Patron> patrons;
    int nextBookId;
    int nextPatronId;

public:
    Library() : nextBookId(1), nextPatronId(1) {}

    void addBook(const string &title, const string &author)
    {
        books.emplace_back(nextBookId++, title, author);
        cout << "Book added successfully!" << endl;
    }

    void displayBooks() const
    {
        for (const auto &book : books)
        {
            book.displayDetails();
        }
    }

    void addPatron(const string &name)
    {
        patrons.emplace_back(nextPatronId++, name);
        cout << "Patron added successfully!" << endl;
    }

    void displayPatrons() const
    {
        for (const auto &patron : patrons)
        {
            patron.displayDetails();
        }
    }

    void checkoutBook(int bookId, int patronId)
    {
        auto bookIt = find_if(books.begin(), books.end(),
                              [bookId](const Book &book)
                              { return book.id == bookId; });
        if (bookIt != books.end() && bookIt->isAvailable)
        {
            auto patronIt = find_if(patrons.begin(), patrons.end(),
                                    [patronId](const Patron &patron)
                                    { return patron.id == patronId; });
            if (patronIt != patrons.end())
            {
                bookIt->isAvailable = false;
                patronIt->checkoutBook(bookId);
                cout << "Book checked out successfully!" << endl;
            }
            else
            {
                cout << "Patron not found!" << endl;
            }
        }
        else
        {
            cout << "Book not available or not found!" << endl;
        }
    }

    void returnBook(int bookId, int patronId)
    {
        auto bookIt = find_if(books.begin(), books.end(),
                              [bookId](const Book &book)
                              { return book.id == bookId; });
        if (bookIt != books.end() && !bookIt->isAvailable)
        {
            auto patronIt = find_if(patrons.begin(), patrons.end(),
                                    [patronId](const Patron &patron)
                                    { return patron.id == patronId; });
            if (patronIt != patrons.end())
            {
                bookIt->isAvailable = true;
                patronIt->returnBook(bookId);
                cout << "Book returned successfully!" << endl;
            }
            else
            {
                cout << "Patron not found!" << endl;
            }
        }
        else
        {
            cout << "Book is not checked out or not found!" << endl;
        }
    }
};

// Main function
int main()
{
    Library library;
    int choice;

    while (true)
    {
        cout << "\nLibrary Management System\n";
        cout << "1. Add Book\n";
        cout << "2. Display Books\n";
        cout << "3. Add Patron\n";
        cout << "4. Display Patrons\n";
        cout << "5. Check Out Book\n";
        cout << "6. Return Book\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string title, author;
            cout << "Enter book title: ";
            cin.ignore();
            getline(cin, title);
            cout << "Enter book author: ";
            getline(cin, author);
            library.addBook(title, author);
            break;
        }
        case 2:
            library.displayBooks();
            break;
        case 3:
        {
            string name;
            cout << "Enter patron name: ";
            cin.ignore();
            getline(cin, name);
            library.addPatron(name);
            break;
        }
        case 4:
            library.displayPatrons();
            break;
        case 5:
        {
            int bookId, patronId;
            cout << "Enter book ID to check out: ";
            cin >> bookId;
            cout << "Enter patron ID: ";
            cin >> patronId;
            library.checkoutBook(bookId, patronId);
            break;
        }
        case 6:
        {
            int bookId, patronId;
            cout << "Enter book ID to return: ";
            cin >> bookId;
            cout << "Enter patron ID: ";
            cin >> patronId;
            library.returnBook(bookId, patronId);
            break;
        }
        case 7:
            cout << "Exiting program. Goodbye!" << endl;
            return 0;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
