#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <ctime>
using namespace std;

// ========================= Book Class =========================
class Book {
public:
    int bookID;
    string title;
    string author;
    string genre;
    int stock;

    Book(int id = 0, string t = "", string a = "", string g = "", int s = 0)
        : bookID(id), title(t), author(a), genre(g), stock(s) {}

    void display() {
        cout << setw(5) << bookID << " | "
             << setw(20) << title << " | "
             << setw(15) << author << " | "
             << setw(10) << genre << " | "
             << setw(5) << stock << endl;
    }
};

// ========================= User Class =========================
class User {
public:
    int userID;
    string name;
    string role; // "student", "teacher"

    User(int id = 0, string n = "", string r = "")
        : userID(id), name(n), role(r) {}

    void display() {
        cout << setw(5) << userID << " | "
             << setw(20) << name << " | "
             << setw(10) << role << endl;
    }
};

// ========================= Transaction Class =========================
class Transaction {
public:
    int transactionID;
    int userID;
    int bookID;
    string issueDate;
    string returnDate;
    float fine;

    Transaction(int tid = 0, int uid = 0, int bid = 0, string issue = "", string ret = "", float f = 0.0)
        : transactionID(tid), userID(uid), bookID(bid),
          issueDate(issue), returnDate(ret), fine(f) {}

    void display() {
        cout << setw(5) << transactionID << " | "
             << setw(5) << userID << " | "
             << setw(5) << bookID << " | "
             << setw(12) << issueDate << " | "
             << setw(12) << returnDate << " | "
             << setw(6) << fine << endl;
    }
};


// ========================= Book Inventory Functions =========================

vector<Book> bookList;

// Save books to file
void saveBooksToFile() {
    ofstream fout("books.txt");
    for (const auto& book : bookList) {
        fout << book.bookID << "," << book.title << "," << book.author << ","
             << book.genre << "," << book.stock << endl;
    }
    fout.close();
}

// Load books from file
void loadBooksFromFile() {
    bookList.clear();
    ifstream fin("books.txt");
    string line;
    while (getline(fin, line)) {
        int id, stock;
        string title, author, genre;

        size_t pos = 0;
        vector<string> tokens;
        while ((pos = line.find(',')) != string::npos) {
            tokens.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        tokens.push_back(line); // last field

        if (tokens.size() == 5) {
            id = stoi(tokens[0]);
            title = tokens[1];
            author = tokens[2];
            genre = tokens[3];
            stock = stoi(tokens[4]);
            bookList.emplace_back(id, title, author, genre, stock);
        }
    }
    fin.close();
}

// Add a new book
void addBook() {
    int id, stock;
    string title, author, genre;

    cout << "Enter Book ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Title: ";
    getline(cin, title);
    cout << "Enter Author: ";
    getline(cin, author);
    cout << "Enter Genre: ";
    getline(cin, genre);
    cout << "Enter Stock: ";
    cin >> stock;

    bookList.emplace_back(id, title, author, genre, stock);
    cout << "Book added successfully!\n";
    saveBooksToFile();
}

// Display all books
void displayAllBooks() {
    cout << "\nAll Books in Library:\n";
    cout << "ID   | Title                | Author         | Genre     | Stock\n";
    cout << "---------------------------------------------------------------\n";
    for (const auto& book : bookList) {
        book.display();
    }
}

// Search books by title
void searchBookByTitle() {
    string query;
    cout << "Enter book title to search: ";
    cin.ignore();
    getline(cin, query);
    bool found = false;

    for (const auto& book : bookList) {
        if (book.title.find(query) != string::npos) {
            if (!found) {
                cout << "Books matching \"" << query << "\":\n";
                cout << "ID   | Title                | Author         | Genre     | Stock\n";
                cout << "---------------------------------------------------------------\n";
            }
            book.display();
            found = true;
        }
    }
    if (!found)
        cout << "No books found with title containing \"" << query << "\".\n";
}

void bookInventoryMenu() {
    int choice;
    loadBooksFromFile();
    do {
        cout << "\n--- Book Inventory Menu ---\n";
        cout << "1. Add New Book\n";
        cout << "2. Display All Books\n";
        cout << "3. Search Book by Title\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayAllBooks(); break;
            case 3: searchBookByTitle(); break;
            case 0: break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}

int main() {
    int mainChoice;
    do {
        cout << "\n=== Smart Library Management System ===\n";
        cout << "1. Book Inventory\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> mainChoice;

        switch (mainChoice) {
            case 1: bookInventoryMenu(); break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (mainChoice != 0);

    return 0;
}
vector<User> userList;

// Save users to file
void saveUsersToFile() {
    ofstream fout("users.txt");
    for (const auto& user : userList) {
        fout << user.userID << "," << user.name << "," << user.role << endl;
    }
    fout.close();
}

// Load users from file
void loadUsersFromFile() {
    userList.clear();
    ifstream fin("users.txt");
    string line;
    while (getline(fin, line)) {
        int id;
        string name, role;

        size_t pos = 0;
        vector<string> tokens;
        while ((pos = line.find(',')) != string::npos) {
            tokens.push_back(line.substr(0, pos));
            line.erase(0, pos + 1);
        }
        tokens.push_back(line);

        if (tokens.size() == 3) {
            id = stoi(tokens[0]);
            name = tokens[1];
            role = tokens[2];
            userList.emplace_back(id, name, role);
        }
    }
    fin.close();
}

// Add a new user
void addUser() {
    int id;
    string name, role;

    cout << "Enter User ID: ";
    cin >> id;
    cin.ignore();
    cout << "Enter Name: ";
    getline(cin, name);
    cout << "Enter Role (student/teacher): ";
    getline(cin, role);

    userList.emplace_back(id, name, role);
    cout << "User added successfully!\n";
    saveUsersToFile();
}

// Display all users
void displayAllUsers() {
    cout << "\nRegistered Users:\n";
    cout << "ID   | Name                 | Role     \n";
    cout << "----------------------------------------\n";
    for (const auto& user : userList) {
        user.display();
    }
}

void userManagementMenu() {
    int choice;
    loadUsersFromFile();
    do {
        cout << "\n--- User Management Menu ---\n";
        cout << "1. Add New User\n";
        cout << "2. Display All Users\n";
        cout << "0. Back to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addUser(); break;
            case 2: displayAllUsers(); break;
            case 0: break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
}


