#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Function to create account
void createAccount() {
    string name;
    int balance;

    cout << "\n===== CREATE ACCOUNT =====\n";
    cout << "Enter username: ";
    cin >> name;

    cout << "Enter initial deposit: ";
    cin >> balance;

    ofstream file("accounts.txt", ios::app);

    if (file.is_open()) {
        file << name << " " << balance << endl;
        file.close();
        cout << "Account created successfully!\n";
    } else {
        cout << "Error opening file!\n";
    }
}

// Function to check balance
void checkBalance() {
    string name, fileName;
    int fileBalance;
    bool found = false;

    cout << "\n===== CHECK BALANCE =====\n";
    cout << "Enter username: ";
    cin >> name;

    ifstream file("accounts.txt");

    while (file >> fileName >> fileBalance) {
        if (fileName == name) {
            cout << "Your balance is: " << fileBalance << " PKR\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Account not found!\n";
    }
}

// Function to deposit money
void depositMoney() {
    string name, fileName;
    int fileBalance;
    int amount;
    bool found = false;

    cout << "\n===== DEPOSIT MONEY =====\n";
    cout << "Enter username: ";
    cin >> name;

    cout << "Enter amount to deposit: ";
    cin >> amount;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    while (file >> fileName >> fileBalance) {
        if (fileName == name) {
            fileBalance += amount;
            found = true;
        }
        temp << fileName << " " << fileBalance << endl;
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (found)
        cout << "Deposit successful!\n";
    else
        cout << "Account not found!\n";
}

// Function to withdraw money
void withdrawMoney() {
    string name, fileName;
    int fileBalance;
    int amount;
    bool found = false;

    cout << "\n===== WITHDRAW MONEY =====\n";
    cout << "Enter username: ";
    cin >> name;

    cout << "Enter amount to withdraw: ";
    cin >> amount;

    ifstream file("accounts.txt");
    ofstream temp("temp.txt");

    while (file >> fileName >> fileBalance) {
        if (fileName == name) {
            if (fileBalance >= amount) {
                fileBalance -= amount;
                cout << "Withdrawal successful!\n";
            } else {
                cout << "Insufficient balance!\n";
            }
            found = true;
        }
        temp << fileName << " " << fileBalance << endl;
    }

    file.close();
    temp.close();

    remove("accounts.txt");
    rename("temp.txt", "accounts.txt");

    if (!found)
        cout << "Account not found!\n";
}

int main() {
    int choice;

    do {
        cout << "\n==========================\n";
        cout << "   BANKING SYSTEM MENU\n";
        cout << "==========================\n";
        cout << "1. Create Account\n";
        cout << "2. Check Balance\n";
        cout << "3. Deposit Money\n";
        cout << "4. Withdraw Money\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: createAccount(); break;
            case 2: checkBalance(); break;
            case 3: depositMoney(); break;
            case 4: withdrawMoney(); break;
            case 5: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }

    } while (choice != 5);

    return 0;
}
