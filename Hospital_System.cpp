#define _CRT_SECURE_NO_WARNINGS
#include<bits/stdc++.h>
using namespace std;
struct queuee {
    string names[6];
    int state[6];
    int indx = 0;
    void Add_back(string name, int st) {
        names[indx] = name; state[indx++] = st;
    }
    void Add_front(string name, int st) {
        ++indx;
        for (int j = indx - 1; j > 0; --j) {
            names[j] = names[j - 1];
            state[j] = state[j - 1];
        }
        names[0] = name;
        state[0] = st;
    }
    bool is_possible_to_add() {
        if (indx >= 5) return 0;
        return 1;
    }
    bool is_possible_to_get() {
        if (indx) return 1;
        return 0;
    }
    void print(int spec) {
        if (indx > 0) {
            cout << "There are " << indx << " patients in specialization " << spec + 1 << "\n";
            for (int i = 0; i < indx; ++i) {
                cout << names[i] << " ";
                if (state[i]) cout << "urgent\n";
                else cout << "regular\n";
            }
            cout << "\n";
        }
    }
    void get_front() {
        cout << names[0] << " please go with the Dr\n";
        --indx;
        for (int j = 0; j < indx; ++j) {
            names[j] = names[j + 1];
            state[j] = state[j + 1];
        }
        cout << "\n";
    }
};

struct Hospital_system {
    queuee specialization[21];
    void start() {
        while (true) {
            int choice;
            cout << "Enter your choice : \n";
            cout << "1) Add new patient\n2) Print all patient\n";
            cout << "3) Get next patient\n4) Exit\n";
            cin >> choice;
            if (choice == 4) {
                cout << "Bye(:\n"; break;
            }
            else if (choice == 1) {
                Add_new_patient();
            }
            else if (choice == 2) {
                print_all();
            }
            else if (choice == 3) {
                get_next_patient();
            }
            else {
                cout << "Invalid choice , Try again\n"; continue;
            }
        }
    }
    void Add_new_patient() {
        string name; int spec; int state;
        cout << "Enter the name of the patient : "; cin >> name;
        cout << "\nEnter the specialization of the patient : "; cin >> spec;
        cout << "\nEnter the state of the patient : "; cin >> state;
        --spec;
        bool check = specialization[spec].is_possible_to_add();
        if (!check) {
            cout << "Sorry we can't add more patients for this specialization\n";
        }
        else {
            if (state) {
                specialization[spec].Add_front(name, state);
            }
            else {
                specialization[spec].Add_back(name, state);
            }
            cout << "\n";
        }
    }
    void print_all() {
        for (int i = 0; i < 20; ++i) {
            specialization[i].print(i);
        }
    }
    void get_next_patient() {
        cout << "Enter  specialization : ";
        int spec; cin >> spec;
        --spec;
        bool check = specialization[spec].is_possible_to_get();
        if (!check) {
            cout << "No patients at the moment. Have rest, Dr\n";
        }
        else {
            specialization[spec].get_front();
        }
    }
};
int main() {
    cout << "         Welcome dear in my hospital system :)\n\n";
    Hospital_system run;
    run.start();
    return 0;
}