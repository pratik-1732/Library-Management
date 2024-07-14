#include <bits/stdc++.h>
using namespace std;

class Book
{
public:
    string id;
    string title;
    string author;
    bool isAvailable;

    Book(const string &id, const string &title, const string &author)
        : id(id), title(title), author(author), isAvailable(true) {}

    void displayDetails() const
    {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author
             << ", " << (isAvailable ? "Available" : "Checked Out") << endl;
    }
};

class Patron
{
public:
    string id;
    string name;
    vector<string> checkedOutBooks;

    Patron(const string &name) : name(name)
    {

        id = generatePatronId(name);
    }

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
            for (const auto &bookId : checkedOutBooks)
            {
                cout << bookId << " ";
            }
            cout << endl;
        }
    }

    void checkoutBook(const string &bookId)
    {
        checkedOutBooks.push_back(bookId);
    }

    void returnBook(const string &bookId)
    {
        auto it = find(checkedOutBooks.begin(), checkedOutBooks.end(), bookId);
        if (it != checkedOutBooks.end())
        {
            checkedOutBooks.erase(it);
        }
    }

private:
    string generatePatronId(const string &name) const
    {

        srand(time(0));
        int randomNumber = rand() % 1000;

        string id = name;
        transform(id.begin(), id.end(), id.begin(), ::tolower);
        id = id + "-" + to_string(randomNumber);

        return id;
    }
};

class Library
{
private:
    vector<Book> books;
    vector<Patron> patrons;

public:
    void addBook(const string &title, const string &author)
    {

        string id = generateBookId(title);

        books.emplace_back(id, title, author);
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

        for (const auto &patron : patrons)
        {
            if (patron.name == name)
            {
                cout << "Patron with this name already exists!" << endl;
                return;
            }
        }

        patrons.emplace_back(name);
        cout << "Patron added successfully!" << endl;
    }

    void displayPatrons() const
    {
        for (const auto &patron : patrons)
        {
            patron.displayDetails();
        }
    }

    void checkoutBook(const string &bookId, const string &patronName)
    {
        auto bookIt = find_if(books.begin(), books.end(),
                              [bookId](const Book &book)
                              { return book.id == bookId; });
        if (bookIt != books.end() && bookIt->isAvailable)
        {
            auto patronIt = find_if(patrons.begin(), patrons.end(),
                                    [patronName](const Patron &patron)
                                    { return patron.name == patronName; });
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

    void returnBook(const string &bookId, const string &patronName)
    {
        auto bookIt = find_if(books.begin(), books.end(),
                              [bookId](const Book &book)
                              { return book.id == bookId; });
        if (bookIt != books.end() && !bookIt->isAvailable)
        {
            auto patronIt = find_if(patrons.begin(), patrons.end(),
                                    [patronName](const Patron &patron)
                                    { return patron.name == patronName; });
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

private:
    string generateBookId(const string &title) const
    {

        srand(time(0));
        int randomNumber = rand() % 1000;

        string id = title;
        transform(id.begin(), id.end(), id.begin(), ::tolower);
        id.erase(remove_if(id.begin(), id.end(), ::isspace), id.end());
        id = id + "-" + to_string(randomNumber);

        return id;
    }
};

int main()
{
    Library library;
    int choice;

    while (true)
    {
        cout << "\nLibrary Management System " << endl;
        cout << "1. Add Book " << endl;
        cout << "2. Display Books " << endl;
        cout << "3. Add Patron " << endl;
        cout << "4. Display Patrons " << endl;
        cout << "5. Check Out Book " << endl;
        cout << "6. Return Book " << endl;
        cout << "7. Exit " << endl;
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
            string bookId, patronName;
            cout << "Enter book ID to check out: ";
            cin >> bookId;
            cout << "Enter patron name: ";
            cin.ignore();
            getline(cin, patronName);
            library.checkoutBook(bookId, patronName);
            break;
        }
        case 6:
        {
            string bookId, patronName;
            cout << "Enter book ID to return: ";
            cin >> bookId;
            cout << "Enter patron name: ";
            cin.ignore();
            getline(cin, patronName);
            library.returnBook(bookId, patronName);
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
