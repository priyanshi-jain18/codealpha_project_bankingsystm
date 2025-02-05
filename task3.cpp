#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;

// Transaction class to handle account transactions
class Transaction {
private:
    string type;
    double amount;
    string date;

public:
    Transaction(const string& type, double amount, const string& date)
        : type(type), amount(amount), date(date) {}

    void display() const {
        cout << left << setw(10) << type << "$" << setw(10) << amount << " on " << date << endl;
    }
};

// Account class to handle customer account operations
class Account {
private:
    string accountNumber;
    double balance;
    vector<Transaction> transactions;

public:
    Account(const string& accNumber, double initialBalance)
        : accountNumber(accNumber), balance(initialBalance) {}

    void deposit(double amount, const string& date) {
        if (amount > 0) {
            balance += amount;
            transactions.emplace_back("Deposit", amount, date);
            cout << "Deposit successful. New balance: $" << balance << endl;
        } else {
            cout << "Invalid deposit amount." << endl;
        }
    }

    void withdraw(double amount, const string& date) {
        if (amount > 0 && amount <= balance) {
            balance -= amount;
            transactions.emplace_back("Withdrawal", amount, date);
            cout << "Withdrawal successful. New balance: $" << balance << endl;
        } else {
            cout << "Invalid or insufficient funds." << endl;
        }
    }

    void displayAccountInfo() const {
        cout << "Account Number: " << accountNumber << endl;
        cout << "Balance: $" << balance << endl;
        cout << "Recent Transactions: " << endl;
        for (const auto& transaction : transactions) {
            transaction.display();
        }
    }

    const string& getAccountNumber() const {
        return accountNumber;
    }
};

// Customer class to manage individual customers
class Customer {
private:
    string name;
    string customerID;
    vector<Account> accounts;

public:
    Customer(const string& name, const string& customerID)
        : name(name), customerID(customerID) {}

    void createAccount(const string& accNumber, double initialDeposit) {
        accounts.emplace_back(accNumber, initialDeposit);
        cout << "Account created successfully for " << name << "." << endl;
    }

    void viewAccounts() const {
        cout << "Customer: " << name << " (ID: " << customerID << ")" << endl;
        for (const auto& account : accounts) {
            account.displayAccountInfo();
            cout << "-------------------------" << endl;
        }
    }

    Account* findAccount(const string& accNumber) {
        for (auto& account : accounts) {
            if (account.getAccountNumber() == accNumber) {
                return &account;
            }
        }
        return nullptr;
    }
};

// Main Banking System
class BankingSystem {
private:
    vector<Customer> customers;

public:
    void addCustomer(const string& name, const string& customerID) {
        customers.emplace_back(name, customerID);
        cout << "Customer " << name << " added successfully." << endl;
    }

    Customer* findCustomer(const string& customerID) {
        for (auto& customer : customers) {
            if (customerID == customerID) {
                return &customer;
            }
        }
        return nullptr;
    }

    void performBankingOperations() {
        string choice;
        while (true) {
            cout << "\n1. Add Customer\n2. Create Account\n3. Deposit\n4. Withdraw\n5. View Accounts\n6. Exit\nEnter choice: ";
            cin >> choice;

            if (choice == "1") {
                string name, id;
                cout << "Enter customer name: ";
                cin >> name;
                cout << "Enter customer ID: ";
                cin >> id;
                addCustomer(name, id);
            } else if (choice == "2") {
                string id, accNum;
                double initialDeposit;
                cout << "Enter customer ID: ";
                cin >> id;
                Customer* customer = findCustomer(id);
                if (customer) {
                    cout << "Enter account number: ";
                    cin >> accNum;
                    cout << "Enter initial deposit: ";
                    cin >> initialDeposit;
                    customer->createAccount(accNum, initialDeposit);
                } else {
                    cout << "Customer not found." << endl;
                }
            } else if (choice == "3") {
                string id, accNum, date;
                double amount;
                cout << "Enter customer ID: ";
                cin >> id;
                Customer* customer = findCustomer(id);
                if (customer) {
                    cout << "Enter account number: ";
                    cin >> accNum;
                    Account* account = customer->findAccount(accNum);
                    if (account) {
                        cout << "Enter deposit amount: ";
                        cin >> amount;
                        cout << "Enter date (YYYY-MM-DD): ";
                        cin >> date;
                        account->deposit(amount, date);
                    } else {
                        cout << "Account not found." << endl;
                    }
                } else {
                    cout << "Customer not found." << endl;
                }
            } else if (choice == "4") {
                string id, accNum, date;
                double amount;
                cout << "Enter customer ID: ";
                cin >> id;
                Customer* customer = findCustomer(id);
                if (customer) {
                    cout << "Enter account number: ";
                    cin >> accNum;
                    Account* account = customer->findAccount(accNum);
                    if (account) {
                        cout << "Enter withdrawal amount: ";
                        cin >> amount;
                        cout << "Enter date (YYYY-MM-DD): ";
                        cin >> date;
                        account->withdraw(amount, date);
                    } else {
                        cout << "Account not found." << endl;
                    }
                } else {
                    cout << "Customer not found." << endl;
                }
            } else if (choice == "5") {
                string id;
                cout << "Enter customer ID: ";
                cin >> id;
                Customer* customer = findCustomer(id);
                if (customer) {
                    customer->viewAccounts();
                } else {
                    cout << "Customer not found." << endl;
                }
            } else if (choice == "6") {
                cout << "Exiting..." << endl;
                break;
            } else {
                cout << "Invalid choice." << endl;
            }
        }
    }
};

int main() {
    BankingSystem bankSystem;
    bankSystem.performBankingOperations();
    return 0;
}
