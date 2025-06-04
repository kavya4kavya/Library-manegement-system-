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

