#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
using namespace std;
const int N = 1e5;
struct books {
    string name; int id; int quantity;
    int total_borrowed = 0;
};
struct users {
    string name; int id_user;
    int id_books[100];
    int flag[N] = { 0 };
    int idx = 0;
    void set_id_book(int id) {
        id_books[idx] = id;
        flag[id_books[idx++]]++;
    }
    bool lol[N] = { 0 };
    void print_ids() {
        sort(id_books, id_books + idx);
        memset(lol, false, sizeof(lol));
        for (int i = 0; i < idx; ++i) {
            if (flag[id_books[i]] and !lol[id_books[i]]) {
                cout << id_books[i] << " ";
                lol[id_books[i]] = 1;
            }
        }
        cout << "\n";
    }
    bool search_book(int id) {
        int l = 0, r = idx - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (id_books[mid] == id) return true;
            if (id_books[mid] < id) {
                l = mid + 1;
            }
            else r = mid - 1;
        }
        return false;
    }
    void return_book(int id) {
        int l = 0, r = idx - 1;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (id_books[mid] == id) {
                flag[id_books[mid]]--; break;
            }
            if (id_books[mid] < id) {
                l = mid + 1;
            }
            else r = mid - 1;
        }
    }
};
bool comp_id(books& b1, books& b2) {
    return b1.id < b2.id;
}
bool comp_name(books& b1, books& b2) {
    return b1.name < b2.name;
}
users user[1000];
books book[1000];
int idx_book = 0, idx_user = 0;
struct Library_System {
    void start() {
        while (true) {
            int choice = menu();
            if (choice == 1) {
                Add_book();
            }
            else if (choice == 2) {
                search_books_by_prefix();
            }
            else if (choice == 3) {
                print_who_borrowed_book_by_name();
            }
            else if (choice == 4) {
                print_library_by_id();
            }
            else if (choice == 5) {
                print_library_by_name();
            }
            else if (choice == 6) {
                Add_user();
            }
            else if (choice == 7) {
                user_borrow_book();
            }
            else if (choice == 8) {
                user_return_book();
            }
            else if (choice == 9) {
                print_users();
            }
            else if (choice == 10) {
                cout << "Bye:)\n"; break;
            }
            else {
                cout << "Invalid choice , Try again\n";
            }
        }
    }
    int menu() {
        cout << "         Library Menu\n\n";
        cout << "1) add_book\n";
        cout << "2) search_books_by_prefix\n";
        cout << "3) print_who_borrowed_book_by_name\n";
        cout << "4) print_library_by_name\n";
        cout << "5) print_library_by_name\n";
        cout << "6) add_user\n";
        cout << "7) user_borrow_book\n";
        cout << "8) user_return_book\n";
        cout << "9) print_users\n";
        cout << "10) Exit\n\n";
        cout << "Enter your menu choice [1 : 10] :";
        int choice;
        cin >> choice;
        return choice;
    }
    void Add_book() {
        cout << "Enter book info : id & name & total quantity :";
        cin >> book[idx_book].id >> book[idx_book].name >> book[idx_book++].quantity;
    }
    void search_books_by_prefix() {
        cout << "Enter book name prefix :";
        string prefix; cin >> prefix;
        bool is_found = 0;
        for (int i = 0; i < idx_book; ++i) {
            string compare = book[i].name;
            if (prefix.size() <= compare.size()) {
                compare = compare.substr(0, prefix.size());
                if (prefix == compare) {
                    cout << book[i].name << "\n";
                    is_found = 1;
                }
            }
        }
        if (!is_found) {
            cout << "No books with such prefix\n";
        }
        cout << "\n";
    }
    void print_library_by_id() {
        sort(book, book + idx_book, comp_id);
        for (int i = 0; i < idx_book; ++i) {
            cout << "id = " << book[i].id << " name = " << book[i].name
                << " total_quantity " << book[i].quantity << " total_borrowed = "
                << book[i].total_borrowed << "\n";
        }
        cout << "\n";
    }
    void print_library_by_name() {
        sort(book, book + idx_book, comp_name);
        for (int i = 0; i < idx_book; ++i) {
            cout << "id = " << book[i].id << " name = " << book[i].name
                << " total_quantity " << book[i].quantity << " total_borrowed = "
                << book[i].total_borrowed << "\n";
        }
        cout << "\n";
    }
    void Add_user() {
        cout << "Enter your name & national id :";
        cin >> user[idx_user].name >> user[idx_user++].id_user;
    }
    int is_found_id_user(int idd, string user_name) {
        int id_user_name = -1;
        for (int i = 0; i < idd; ++i) {
            if (user[i].name == user_name) {
                id_user_name = i; break;
            }
        }
        return id_user_name;
    }
    int is_found_id_book(int idd, string book_name) {
        int id_book_name = -1;
        for (int i = 0; i < idd; ++i) {
            if (book[i].name == book_name) {
                id_book_name = i; break;
            }
        }
        return id_book_name;
    }
    void user_borrow_book() {
        cout << "Enter user name and book name :";
        string user_name, book_name;
        cin >> user_name >> book_name;
        int id_user_name = is_found_id_user(idx_user, user_name);
        int id_book_name = is_found_id_book(idx_book, book_name);
        if (id_user_name == -1 or id_book_name == -1) {
            cout << "The name of the user or name of the book doesn't exist , please Try again\n";
        }
        else {
            if (book[id_book_name].total_borrowed < book[id_book_name].quantity) {
                user[id_user_name].set_id_book(book[id_book_name].id);
                book[id_book_name].total_borrowed++;
            }
            else {
                cout << "Sorry, all copys from this book is borrowed\n";
            }
        }
        cout << "\n";
    }

    void print_users() {
        for (int i = 0; i < idx_user; ++i) {
            cout << "user " << user[i].name << " id " <<
                user[i].id_user << " borrowed books ids :";
            user[i].print_ids();
        }
        cout << "\n";
    }
    void print_who_borrowed_book_by_name() {
        cout << "Enter book name :";
        string book_name; cin >> book_name;
        int id_book = -1;
        for (int i = 0; i < idx_book; ++i) {
            if (book[i].name == book_name) {
                id_book = book[i].id; break;
            }
        }
        if (id_book == -1) {
            cout << "Invalid book name\n";
        }
        else {
            bool found = 0;
            for (int i = 0; i < idx_user; ++i) {
                if (user[i].search_book(id_book)) {
                    cout << user[i].name << "\n";
                    found = 1;
                }
            }
            if (!found) {
                cout << "this book isn't borrowed\n";
            }
            cout << "\n";
        }
    }
    void user_return_book() {
        cout << "Enter user name and book name :";
        string user_name, book_name;
        cin >> user_name >> book_name;
        int id_user_name = is_found_id_user(idx_user, user_name);
        int id_book_name = is_found_id_book(idx_book, book_name);
        if (id_user_name == -1 or id_book_name == -1) {
            cout << "The name of the user or name of the book doesn't exist , please Try again\n\n";
        }
        else {
            user[id_user_name].return_book(book[id_book_name].id);
            book[id_book_name].total_borrowed--;
        }
    }
};
int main() {
    cout << "\n     Welcome in my Library System\n\n";
    Library_System run;
    run.start();
    return 0;
}