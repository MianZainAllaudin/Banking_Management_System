#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <sstream>
#include <chrono>
#include <ctime>
#include <vector>

using namespace std;
struct UserInfo {
    string id;
    string name;
    string city;
    string CNIC;
    string loginID;
    string pass;
    int balance;
    double limit;
};

struct CompInfo {
    string id;
    string name;
    string address;
    string TAX_number;
    string loginID;
    string pass;
    int balance;
    double limit;
};

struct Card {
    string id;
    string number;
    string pin;
};

vector<Card> readCardsFromFile(const string& filename) {
    ifstream file(filename);
    vector<Card> cards;
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        Card card;
        char comma;
        getline(ss, card.id, ',');
        getline(ss, card.number, ',');
        getline(ss, card.pin, '\n');
        cards.push_back(card);
    }

    return cards;
}

void writeCardsToFile(const string& filename, const vector<Card>& cards) {
    ofstream file(filename);
    for (const auto& card : cards) {
        file << card.id << "," << card.number << ", " << card.pin << endl;
    }
}

void addPinToCard(vector<Card>& cards, const string& id, const string& pin) {
    for (auto& card : cards) {
        if (card.id == id) {
            card.pin = pin;
            break;
        }
    }
}
vector<CompInfo> readCompData(const string& filename) {
    vector<CompInfo> users;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        CompInfo user;
        char comma;
        getline(ss, user.id, ',');
        getline(ss, user.name, ',');
        getline(ss, user.address, ',');
        getline(ss, user.TAX_number, ',');
        getline(ss, user.loginID, ',');
        getline(ss, user.pass, ',');
        ss >> user.balance >> comma >> user.limit;
        users.push_back(user);
    }

    return users;
}

vector<UserInfo> readUserData(const string& filename) {
    vector<UserInfo> users;
    ifstream file(filename);
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        UserInfo user;
        char comma;
        getline(ss, user.id, ',');
        getline(ss, user.name, ',');
        getline(ss, user.city, ',');
        getline(ss, user.CNIC, ',');
        getline(ss, user.loginID, ',');
        getline(ss, user.pass, ',');
        ss >> user.balance >> comma >> user.limit;
        users.push_back(user);
    }

    return users;
}

void writeUserData(const string& filename, const vector<UserInfo>& users) {
    ofstream file(filename);

    for (const auto& user : users) {
        file << user.id << "," << user.name << "," << user.city << "," << user.CNIC << "," << user.loginID << "," << user.pass << "," << user.balance << "," << user.limit << endl;
    }
}

void writeCompData(const string& filename, const vector<CompInfo>& users) {
    ofstream file(filename);

    for (const auto& user : users) {
        file << user.id << "," << user.name << "," << user.address << "," << user.TAX_number << "," << user.loginID << "," << user.pass << "," << user.balance << "," << user.limit << endl;
    }
}

void modifyBalance(vector<UserInfo>& users, const string& id, int newBalance) {
    for (auto& user : users) {
        if (user.id == id) {
            user.balance = newBalance;
            break; // Assuming IDs are unique, no need to search further
        }
    }
}

void modifyBalanceForTransfer(vector<UserInfo>& users, const string& id, int amount) {
    for (auto& user : users) {
        if (user.id == id) {
            user.balance += amount;
            break; // Assuming IDs are unique, no need to search further
        }
    }
}

void modifyBalanceForComp(vector<CompInfo>& users, const string& id, int newBalance) {
    for (auto& user : users) {
        if (user.id == id) {
            user.balance = newBalance;
            break; // Assuming IDs are unique, no need to search further
        }
    }
}

void modifyBalanceForTransferOfComp(vector<CompInfo>& users, const string& id, int amount) {
    for (auto& user : users) {
        if (user.id == id) {
            user.balance += amount;
            break; // Assuming IDs are unique, no need to search further
        }
    }
}

class Transaction
{
private:
    string transactionDate;
    string userID;
    double amount;
    string transactionType;
    string targetUserID; // For transfer transactions

public:
    Transaction(const string& date, const string& user, double amt, const string& type)
        : transactionDate(date), userID(user), amount(amt), transactionType(type), targetUserID("")
    {
        auto now = chrono::system_clock::now();
        time_t time_now = chrono::system_clock::to_time_t(now);
        transactionDate = ctime(&time_now);

        // Remove newline character from transactionDate
        transactionDate.erase(transactionDate.find_last_not_of(" \n\r\t") + 1);
        ofstream outFile("transactions.txt", ios_base::app);
        if (outFile.is_open())
        {
            outFile << transactionDate << "," << userID << "," << amount << "," << transactionType;
            if (!targetUserID.empty())
            {
                outFile << "," << targetUserID;
            }
            outFile << endl;
            outFile.close();
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }

    Transaction(const string& date, const string& user, double amt, const string& type, const string& targetUser)
        : transactionDate(date), userID(user), amount(amt), transactionType(type), targetUserID(targetUser)
    {
        auto now = chrono::system_clock::now();
        time_t time_now = chrono::system_clock::to_time_t(now);
        transactionDate = ctime(&time_now);

        // Remove newline character from transactionDate
        transactionDate.erase(transactionDate.find_last_not_of(" \n\r\t") + 1);
        ofstream outFile("transactions.txt", ios_base::app);
        if (outFile.is_open())
        {
            outFile << transactionDate << "," << userID << "," << amount << "," << transactionType;
            if (!targetUserID.empty())
            {
                outFile << "," << targetUserID;
            }
            outFile << endl;
            outFile.close();
        }
        else
        {
            cout << "Error: Unable to open file for writing." << endl;
        }
    }
};

// class for Card Information
class card
{
public:
    const string card_num;

    void set_card_pin(string pin)
    {
        card_pin = pin;
    }

    string get_card_pin()
    {
        return card_pin;
    }

    card() : card_num(""), card_pin("") {}
    card(string num) : card_num(num) {}

protected:
    string card_pin;
};

// Base class for all account types
class BankAccount
{
protected:
    string userID;
    double balance;

public:
    BankAccount(string id)
    {
        userID = id;
        balance = 0;
    }

    BankAccount(string id, double balance)
    {
        userID = id;
        this->balance = balance;
    }

    virtual ~BankAccount()
    {

    }

    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
    virtual void transfer(string toUserID, double amount) = 0;
    virtual void viewBalance() = 0;
    virtual void viewTransactionHistory() = 0;
};

// class for account information
class account_type
{

public:
    string account;
    int account_limit;
    string account_restriction;
    account_type() : account("bronze"), account_limit(100000), account_restriction("User /  Back Client") {}
    account_type(string account, int account_limit, string account_restriction) : account(account), account_limit(account_limit), account_restriction(account) {}

    void display() const
    {
        cout << "Account Type: " << account << endl;
        cout << "Limit: " << account_limit << endl;
        cout << "Restrictions: " << account_restriction << endl;
    }

    ~account_type()
    {
    }
};

// Derived class for UserClient
class UserClient : public BankAccount, card
{
private:
    char* fullName;
    char* address;
    // char* phone;
    char* CNIC;
    char* loginID;
    char* password;
    double dailyWithdrawalLimit;
    account_type account_details;
    bool approved;

public:
    card card_details;
    UserClient(string id, const char* name, const char* addr, const char* cnic,
        const char* login, const char* pass, double limit)
        : BankAccount(id), approved(true)
    {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);

        address = new char[strlen(addr) + 1];
        strcpy(address, addr);

        // phone = new char[strlen(ph) + 1];
        // strcpy(phone, ph);

        CNIC = new char[strlen(cnic) + 1];
        strcpy(CNIC, cnic);

        loginID = new char[strlen(login) + 1];
        strcpy(loginID, login);

        password = new char[strlen(pass) + 1];
        strcpy(password, pass);

        dailyWithdrawalLimit = limit;

        if (0 <= dailyWithdrawalLimit <= 100000)
        {
            account_details.account = "Bronze";
            account_details.account_limit = 100000;
            account_details.account_restriction = "User / Bank Client";
        }
        else if (100000 <= dailyWithdrawalLimit <= 500000)
        {
            account_details.account = "Gold";
            account_details.account_limit = 50000;
            account_details.account_restriction = "User / Bank Client";
        }
        else
        {
            cout << "Invalid dailyWithdrawalLimit for User Client" << endl;
        }

        // File handling logic for adding this account in accounts list
    }

    ~UserClient()
    {
        delete[] fullName;
        delete[] address;
        // delete[] phone;
        delete[] CNIC;
        delete[] loginID;
        delete[] password;
    }

    UserClient(string id, const char* name, const char* addr, const char* cnic,
        const char* login, const char* pass, double balance, double limit)
        : BankAccount(id, balance), approved(true)
    {
        fullName = new char[strlen(name) + 1];
        strcpy(fullName, name);

        address = new char[strlen(addr) + 1];
        strcpy(address, addr);

        // phone = new char[strlen(ph) + 1];
        // strcpy(phone, ph);

        CNIC = new char[strlen(cnic) + 1];
        strcpy(CNIC, cnic);

        loginID = new char[strlen(login) + 1];
        strcpy(loginID, login);

        password = new char[strlen(pass) + 1];
        strcpy(password, pass);

        dailyWithdrawalLimit = limit;

        if (0 <= dailyWithdrawalLimit <= 100000)
        {
            account_details.account = "Bronze";
            account_details.account_limit = 100000;
            account_details.account_restriction = "User / Bank Client";
        }
        else if (100000 <= dailyWithdrawalLimit <= 500000)
        {
            account_details.account = "Gold";
            account_details.account_limit = 50000;
            account_details.account_restriction = "User / Bank Client";
        }
        else
        {
            cout << "Invalid dailyWithdrawalLimit for User Client" << endl;
        }

        // File handling logic for adding this account in accounts list
    }

    void set_approved(bool approval)
    {
        this->approved = approval;
    }

    bool get_approved()
    {
        return approved;
    }

    string get_userID()
    {
        return userID;
    }

    double get_daily_limit() {
        return this->dailyWithdrawalLimit;
    }

    void deposit(double amount) {
        if (approved && amount <= dailyWithdrawalLimit) {
            balance += amount;
            cout << balance << endl;
            Transaction transaction("current-date-placeholder", userID, amount, "Deposit");
            //transaction.saveToFile();
            vector<UserInfo> users = readUserData("users.txt");
            modifyBalance(users, this->userID, balance);
            writeUserData("users.txt", users);
        }

        else {
            cout << "Account Waiting for Approval" << endl;
        }
    }

    void withdraw(double amount) {
        if (approved && balance >= amount && amount <= dailyWithdrawalLimit) {
            balance -= amount;
            Transaction transaction("current-date-placeholder", userID, -amount, "Withdrawal");
            //transaction.saveToFile();
            vector<UserInfo> users = readUserData("users.txt");
            modifyBalance(users, this->userID, balance);
            writeUserData("users.txt", users);
        }
        else {
            cout << "Insufficient balance or limit exceeded." << endl;
            //cout << this->approved << " " << this->balance << " " << this->dailyWithdrawalLimit << endl;
        }
    }

    void transfer(string toUserID, double amount) {

        if (approved && balance >= amount && amount <= dailyWithdrawalLimit) {
            balance -= amount;
            //updateTransfer("users.txt", userID, amount, true);  // Subtract from sender
            //updateTransfer("users.txt", toUserID, amount, false); // Add to receiver
            Transaction transaction("current-date-placeholder", userID, -amount, "Transfer", toUserID);
            vector<UserInfo> users = readUserData("users.txt");
            modifyBalance(users, this->userID, balance);
            modifyBalanceForTransfer(users, toUserID, amount);
            writeUserData("users.txt", users);
        }

        else {
            cout << "Inefficient balance!!" << endl;
        }


    }

    void viewBalance() override
    {
        if (approved)
        {
            cout << "Balance: " << balance << endl;
        }
        else
        {
            cout << "Account Waiting for Approval" << endl;
        }
    }

    void viewTransactionHistory() override
    {
        if (approved)
        {
            // File Handling logic for reading transactions file and displaying it
            ifstream file("transactions.txt");
            string line;
            while (getline(file, line))
            {
                // Parse and display each transaction
                cout << line << endl;
            }
            file.close();
        }
        else
        {
            cout << "Account Waiting for Approval" << endl;
        }
    }

    string generateCardNumber()
    {
        srand(time(0)); // Seed random number generator
        string cardNumber;
        for (int i = 0; i < 16; ++i)
        {
            cardNumber += to_string(rand() % 10);
        }
        return cardNumber;
    }

    // Function to save user data to "users.txt"
    void saveUserDataAndApply()
    {
        ofstream app_file("account_approval.txt", ios::app); // Open file in append mode
        app_file << "User, " << this->userID << ", " << this->fullName << ", " << this->address << ", " << this->CNIC << ", " << this->loginID << ", " << this->password << ", " << this->balance << ", " << this->dailyWithdrawalLimit << endl;
        app_file.close();
    }

    void freezeAccount(const string& accountID) {
        ofstream outFile("users.txt", ios::app);
        if (outFile.is_open()) {
            outFile << accountID << endl;
            cout << "Account ID " << accountID << " has been frozen due to too many incorrect attempts." << endl;
        }
        else {
            cout << "Failed to open file: " << "users.txt" << endl;
        }
        outFile.close();
    }

};

// Derived class for CompanyClient
class CompanyClient : public BankAccount
{
private:
    char* companyName;
    char* companyAddress;
    char* taxNumber;
    double dailyWithdrawalLimit;
    char* accountID;
    char* accountPassword;
    char** employees;
    int numEmployees;
    account_type account_details;
    card card_details;
    double loan;
    bool approved;

public:
    CompanyClient(string id, const char* name, const char* addr, const char* taxNum,
        double limit, const char* accID, const char* pass)
        : BankAccount(id), numEmployees(0), approved(true), loan(0)
    {
        companyName = new char[strlen(name) + 1];
        strcpy(companyName, name);

        companyAddress = new char[strlen(addr) + 1];
        strcpy(companyAddress, addr);

        taxNumber = new char[strlen(taxNum) + 1];
        strcpy(taxNumber, taxNum);

        dailyWithdrawalLimit = limit;

        accountID = new char[strlen(accID) + 1];
        strcpy(accountID, accID);

        accountPassword = new char[strlen(pass) + 1];
        strcpy(accountPassword, pass);

        employees = nullptr;

        if (0 < dailyWithdrawalLimit < 100000)
        {
            account_details.account = "Bronze";
            account_details.account_limit = 100000;
            account_details.account_restriction = "User / Bank Client";
            this->dailyWithdrawalLimit = 100000;
        }
        else if (100000 < dailyWithdrawalLimit < 500000)
        {
            account_details.account = "Gold";
            account_details.account_limit = 50000;
            account_details.account_restriction = "User / Bank Client";
            this->dailyWithdrawalLimit = 500000;
        }
        else if (500000 < dailyWithdrawalLimit < 1000000)
        {
            account_details.account = "Business";
            account_details.account_limit = 100000;
            account_details.account_restriction = "Bank Client";
            this->dailyWithdrawalLimit = 1000000;
        }
        else
        {
            cout << "Invalid dailyWithdrawalLimit for User Client" << endl;
        }

        // File handling logic for adding this account in account_approval file for Approval
        // File handling logic for adding this account in company accounts list
    }

    CompanyClient(string id, const char* name, const char* addr, const char* taxNum,
        double limit, double balance, const char* accID, const char* pass)
        : BankAccount(id, balance), numEmployees(0), approved(true)
    {
        companyName = new char[strlen(name) + 1];
        strcpy(companyName, name);

        companyAddress = new char[strlen(addr) + 1];
        strcpy(companyAddress, addr);

        taxNumber = new char[strlen(taxNum) + 1];
        strcpy(taxNumber, taxNum);

        dailyWithdrawalLimit = limit;

        accountID = new char[strlen(accID) + 1];
        strcpy(accountID, accID);

        accountPassword = new char[strlen(pass) + 1];
        strcpy(accountPassword, pass);

        employees = nullptr;

        if (0 < dailyWithdrawalLimit < 100000)
        {
            account_details.account = "Bronze";
            account_details.account_limit = 100000;
            account_details.account_restriction = "User / Bank Client";
            this->dailyWithdrawalLimit = 100000;
        }
        else if (100000 < dailyWithdrawalLimit < 500000)
        {
            account_details.account = "Gold";
            account_details.account_limit = 50000;
            account_details.account_restriction = "User / Bank Client";
            this->dailyWithdrawalLimit = 500000;
        }
        else if (500000 < dailyWithdrawalLimit < 1000000)
        {
            account_details.account = "Business";
            account_details.account_limit = 100000;
            account_details.account_restriction = "Bank Client";
            this->dailyWithdrawalLimit = 1000000;
        }
        else
        {
            cout << "Invalid dailyWithdrawalLimit for User Client" << endl;
        }

        // File handling logic for adding this account in account_approval file for Approval
        // File handling logic for adding this account in company accounts list
    }

    ~CompanyClient()
    {
        delete[] companyName;
        delete[] companyAddress;
        delete[] taxNumber;
        delete[] accountID;
        delete[] accountPassword;

        if (employees)
        {
            for (int i = 0; i < numEmployees; ++i)
            {
                delete[] employees[i];
            }
            delete[] employees;
        }
    }

    void addEmployee(const char* employeeID)
    {
        char** newEmployees = new char* [numEmployees + 1];
        for (int i = 0; i < numEmployees; ++i)
        {
            newEmployees[i] = employees[i];
        }
        newEmployees[numEmployees] = new char[strlen(employeeID) + 1];
        strcpy(newEmployees[numEmployees], employeeID);

        delete[] employees;
        employees = newEmployees;
        ++numEmployees;

        // File Handling logic for adding this emplyee in the Company Employee file
    }

    void deposit(double amount) {

        if (approved && amount <= dailyWithdrawalLimit && amount > 0) {
            balance += amount;
            Transaction transaction("current-date-placeholder", userID, amount, "Deposit");
            //transaction.saveToFile();
            vector<CompInfo> users = readCompData("companies.txt");
            modifyBalanceForComp(users, this->userID, balance);
            writeCompData("companies.txt", users);
            //updateAccountFile("companies.txt", userID, balance);  // Update balance in companies.txt
        }
        else if (amount <= 0) {
            cout << "Enter Valid amount!" << endl;
        }
        else {
            cout << "Account Waiting for Approval" << endl;
            cout << dailyWithdrawalLimit << balance << endl;
        }
    }


    void withdraw(double amount) {
        if (approved && balance >= amount && amount <= dailyWithdrawalLimit && amount > 0) {
            balance -= amount;
            Transaction transaction("current-date-placeholder", userID, amount, "Deposit");
            //transaction.saveToFile();
            vector<CompInfo> users = readCompData("companies.txt");
            modifyBalanceForComp(users, this->userID, balance);
            writeCompData("companies.txt", users);
            //updateAccountFile("companies.txt", userID, balance);  // Update balance in companies.txt
        }
        else if (amount <= 0) {
            cout << "Enter Valid amount!" << endl;
        }

        else {
            cout << "Insufficient balance or limit exceeded." << endl;
        }
    }

    void transfer(string toUserID, double amount) {

        if (approved && balance >= amount && amount <= dailyWithdrawalLimit && amount > 0) {
            balance -= amount;
            //updateTransfer("users.txt", userID, amount, true);  // Subtract from sender
            //updateTransfer("users.txt", toUserID, amount, false); // Add to receiver
            Transaction transaction("current-date-placeholder", userID, -amount, "Transfer", toUserID);
            vector<CompInfo> users = readCompData("companies.txt");
            modifyBalanceForComp(users, this->userID, balance);
            modifyBalanceForTransferOfComp(users, toUserID, amount);
            writeCompData("companies.txt", users);
        }

        else if (amount <= 0) {
            cout << "Enter Valid amount!" << endl;
        }

        else {
            cout << "Inefficient balance!!" << endl;
        }
        //updateTransfer("companies.txt", userID, amount, true);  // Subtract from sender
        //updateTransfer("companies.txt", toUserID, amount, true); // Add to receiver
    }


    void viewBalance() override
    {
        if (approved)
        {
            cout << "Balance: " << balance << endl;
        }
        else
        {
            cout << "Account Waiting for Approval" << endl;
        }
    }

    void viewTransactionHistory() override
    {
        if (approved)
        {
            ifstream transactionFile("transactions.txt");
            string date, ID, amount, Type;

            if (transactionFile.is_open())
            {
                cout << "Transaction History for Account ID " << accountID << ":" << endl;
                cout << "Date\tID\tAmount\tType" << endl;
                while (transactionFile >> date >> ID >> amount >> Type)
                {
                    if (ID == accountID)
                    {
                        cout << date << "\t" << ID << "\t" << amount << "\t" << Type << endl;
                    }
                }
                transactionFile.close();
            }
            else
            {
                cout << " Unable to open transaction file." << endl;
            }
        }
        else
        {
            cout << "Account Waiting for Approval" << endl;
        }
    }

    void saveUserDataAndApply()
    {
        ofstream app_file("account_approval.txt", ios::app); // Open file in append mode
        app_file << "Company, " << this->userID << ", " << this->companyName << ", " << this->companyAddress << ", " << this->taxNumber << ", " << this->accountID << ", " << this->accountPassword << ", " << this->balance << ", " << this->dailyWithdrawalLimit << endl;
        app_file.close();
    }
    void applyForLoan(double amount) {
        ofstream loanFile("loan_applications.txt", ios::app);
        if (loanFile.is_open()) {
            loanFile << userID << "," << amount << endl;
            cout << "Loan application submitted successfully." << endl;
        }
        else {
            cout << "Error opening loan applications file." << endl;
        }
        loanFile.close();
    }

    void freezeAccount(const string& accountID) {
        ofstream outFile("companies.txt", ios::app);
        if (outFile.is_open()) {
            outFile << accountID << endl;
            cout << "Account ID " << accountID << " has been frozen due to too many incorrect attempts." << endl;
        }
        else {
            cout << "Failed to open file: " << "companies.txt" << endl;
        }
        outFile.close();
    }

    void set_loan(double amount) {
        this->loan = amount;
    }


};

// Class for BankingEmployee
class BankingEmployee
{
private:
    char* userID;
    char* password;
    string generateRandomCardNumber()
    {
        srand(time(0));
        string cardNumber;
        for (int i = 0; i < 16; ++i)
        {
            cardNumber = cardNumber + to_string(rand() % 10);
        }
        return cardNumber;
    }

public:
    BankingEmployee(const char* id, const char* pass)
    {
        userID = new char[strlen(id) + 1];
        strcpy(userID, id);

        password = new char[strlen(pass) + 1];
        strcpy(password, pass);
    }

    ~BankingEmployee()
    {
        delete[] userID;
        delete[] password;
    }

    void viewUserClients()
    {
        ifstream file("users.txt");
        if (!file.is_open())
        {
            cout << "Unable to open users file." << endl;
            return;
        }

        cout << "User ID\t\tUsername\t\tAddress\t\tCNIC\t\tLogin ID\tBalance\tWithdrawal limit" << endl;

        string userID, username, address, cnic, loginID, pass, line;
        double balance, withdrawal_limit;

        while (getline(file, line))
        {
            stringstream ss(line);
            char comma;
            getline(ss, userID, ',');
            getline(ss, username, ',');
            getline(ss, address, ',');
            getline(ss, cnic, ',');
            getline(ss, loginID, ',');
            getline(ss, pass, ',');
            ss >> balance >> comma >> withdrawal_limit;
            // getline(ss, balance, ',');
            // getline(ss, withdrawal_limit, ',');

            cout << userID << "\t\t" << username << "\t\t" << address << "\t\t" << cnic << "\t\t" << loginID << "\t\t" << balance << "\t\t" << withdrawal_limit << endl;
        }
        file.close();
    }
    void viewCompanyClients()
    {
        ifstream file("companies.txt");
        if (!file.is_open())
        {
            cout << "Unable to open users file." << endl;
            return;
        }

        cout << "Company ID\t\tCompany Name\t\tAddress\t\tTax Number\t\tLogin ID\tBalance\tWithdrawal Limit" << endl;

        string userID, username, address, cnic, loginID, pass, line;
        double balance, withdrawal_limit;

        //while (file >> userID >> username >> address >> cnic >> loginID >> pass >> balance >> withdrawal_limit)
        while (getline(file, line))
        {
            stringstream ss(line);
            char comma;
            getline(ss, userID, ',');
            getline(ss, username, ',');
            getline(ss, address, ',');
            getline(ss, cnic, ',');
            getline(ss, loginID, ',');
            getline(ss, pass, ',');
            ss >> balance >> comma >> withdrawal_limit;
            // getline(ss, balance, ',');
            // getline(ss, withdrawal_limit, ',');

            cout << userID << "\t\t\t" << username << "\t\t\t" << address << "\t\t\t" << cnic << "\t\t" << loginID << "\t\t" << balance << "\t\t" << withdrawal_limit << endl;
        }
        file.close();
    }
    void approveAccount()
    {
        ifstream inFile("account_approval.txt");
        if (!inFile)
        {
            cout << "Error: Unable to open input file: " << endl;
            return;
        }

        ofstream disFile("disapproved_accounts.txt", ios::app);
        if (!disFile)
        {
            cout << "Error: Unable to create temporary file." << endl;
            inFile.close();
            return;
        }

        string line, UserID;
        int lineCount = 0;
        while (getline(inFile, line))
        {
            lineCount++;

            istringstream iss(line);
            string type;
            getline(iss >> ws, type, ',');
            getline(iss >> ws, UserID, ',');
            // cout << type << endl;

            if (type == "User")
            {

                cout << "Account for Approval : " << endl;
                cout << "User ID\t\tUsername\t\tAddress\t\tCNIC\t\tLogin ID\t\tBalance" << endl;
                cout << line;
                cout << "Do you want to Approve this Account? (Yes/No): ";
                string choice;
                cin >> choice;

                ofstream userFile("users.txt", ios::app);
                if (!userFile)
                {
                    cout << "Error: Unable to create temporary file." << endl;
                    inFile.close();
                    return;
                }
                cout << "OK" << endl;
                if (choice == "Yes" || choice == "yes")
                {
                    string user_data;

                    string card_num = this->generateRandomCardNumber();

                    ofstream cardFile("cards.txt", ios::app);

                    if (!cardFile)
                    {
                        cout << "Error: Unable to open file." << endl;
                        inFile.close();
                        return;
                    }

                    // for (int i = 0; line[i] == ','; i++)
                    // {
                    //     UserID += line[i];
                    // }

                    cardFile << UserID << ", " << card_num;
                    getline(iss >> ws, user_data);
                    userFile << UserID << ", " << user_data << endl;

                    cardFile.close();
                }
                else if (choice == "No" || choice == "no")
                {
                    disFile << line << endl;
                }
                userFile.close();
            }

            else if (type == "Company")
            {

                cout << "Account for Approval : " << endl;
                cout << "Company ID\t\tCompany Name\t\tAddress\t\tTax Number\t\tLogin ID\t\tBalance" << endl;
                cout << line;
                cout << "Do you want to Approve this Account? (Yes/No): ";
                string choice;
                cin >> choice;

                ofstream compFile("companies.txt", ios::app);
                if (!compFile)
                {
                    cout << "Error: Unable to create temporary file." << endl;
                    inFile.close();
                    return;
                }

                if (choice == "Yes")
                {

                    string comp_data;
                    getline(iss >> ws, comp_data);
                    compFile << comp_data << endl;
                }

                else if (choice == "No")
                {
                    disFile << line << endl;
                }

                compFile.close();
            }
        }

        inFile.close();

        disFile.close();

        // Now all accounts are approved/disapproved so dropping the accounts from this file.
        ofstream app_File("account_approval.txt", ios::trunc);
        if (!app_File)
        {
            cout << "Error: Unable to open input file: " << endl;
            return;
        }
        app_File.close();
    }

    void approveLoans() {
        ifstream loanFile("loan_applications.txt");
        ofstream tempFile("temp_loan_applications.txt", ios::app);
        ofstream approvedLoansFile("approved_loans.txt", ios::app);

        if (!loanFile.is_open() || !approvedLoansFile.is_open() || !tempFile.is_open()) {
            cerr << "Error opening files." << endl;
            return;
        }

        string line;
        while (getline(loanFile, line)) {
            string companyID, amount;
            stringstream ss(line);
            getline(ss, companyID, ',');
            getline(ss, amount, ',');

            cout << "Loan Application: Company ID = " << companyID << ", Amount = $" << amount << endl;
            cout << "Approve this loan? (yes/no): ";
            string response;
            cin >> response;

            if (response == "yes" || response == "Yes") {
                approvedLoansFile << companyID << "," << amount << endl;
                cout << "Loan approved for Company ID: " << companyID << endl;
            }
            else {
                tempFile << line << endl;
                cout << "Loan not approved for Company ID: " << companyID << endl;
            }
        }

        loanFile.close();
        tempFile.close();
        approvedLoansFile.close();


        remove("loan_applications.txt");
        rename("temp_loan_applications.txt", "loan_applications.txt");
    }

    void rejectLoan(const char* companyID)
    {
        ofstream rejectionFile("loan_rejection.txt", ios::app);
        if (rejectionFile.is_open())
        {
            rejectionFile << companyID << endl;
            cout << "Loan for company with ID " << companyID << " has been rejected." << endl;
            rejectionFile.close();
        }
        else
        {
            cout << " Unable to open file for loan rejection." << endl;
        }
    }

    void viewTransactionHistory(string accountID)
    {
        ifstream transactionFile("transactions.txt");
        string date, ID, amount, Type, line, tmpID, recieverID;

        if (transactionFile.is_open())
        {
            cout << "Transaction History for Account ID " << accountID << ":" << endl;
            cout << "Date\t\t\t\tID\tAmount\tType\tReciever ID (only for transfer)" << endl;
            while (getline(transactionFile, line))
            {
                istringstream iss(line);

                getline(iss >> ws, date, ',');
                getline(iss >> ws, ID, ',');
                getline(iss >> ws, amount, ',');
                getline(iss >> ws, Type, ',');

                if (getline(iss >> ws, tmpID), ',') {
                    stringstream(tmpID) >> recieverID;
                }

                if (ID == accountID)
                {
                    cout << date << "\t" << ID << "\t" << amount << "\t" << Type << "\t" << recieverID << endl;
                }
            }
            transactionFile.close();
        }
        else
        {
            cout << " Unable to open transaction file." << endl;
        }
    }

    void freezeAccount(const string& accountID, const string& fileName) {
        ofstream outFile(fileName, ios::app);
        if (outFile.is_open()) {
            outFile << accountID << endl;
            cout << "Account ID " << accountID << " has been frozen due to too many incorrect attempts." << endl;
        }
        else {
            cout << "Failed to open file: " << fileName << endl;
        }
        outFile.close();
    }


    void closeAccount(const char* accountID)
    {
        ofstream closedFile("closed_accounts.txt", ios::app);
        if (closedFile.is_open())
        {
            closedFile << accountID << endl;
            cout << "Account with ID " << accountID << " has been closed." << endl;
            closedFile.close();
        }
        else
        {
            cout << "Unable to open file for closing account." << endl;
        }
    }
};

UserClient userLogin(bool& user_flag)
{
    string ID, password;
    user_flag = false;
    int failedAttempts = 0;
    while (!user_flag)
    {
        cout << "Enter User ID: ";
        cin >> ID;
        cout << "Enter Password: ";
        cin >> password;

        ifstream file("users.txt");
        if (!file.is_open())
        {
            cout << "Unable to open users file." << endl;
        }

        ifstream card_file("cards.txt");
        if (!file.is_open())
        {
            cout << "Unable to open users file." << endl;
        }

        string userID, username, address, cnic, loginID, pass;
        double balance, withdrawal_limit;

        string line;

        while (getline(file, line))
        {
            istringstream iss(line);
            string userID, username, address, cnic, loginID, pass;
            string balance, withdrawal_limit;

            getline(iss >> ws, userID, ',');
            getline(iss >> ws, username, ',');
            getline(iss >> ws, address, ',');
            getline(iss >> ws, cnic, ',');
            getline(iss >> ws, loginID, ',');
            getline(iss >> ws, pass, ',');
            getline(iss >> ws, balance, ',');
            getline(iss >> ws, withdrawal_limit, ',');

            double balance_int = stoi(balance);
            double withdrawal_limit_int = stoi(withdrawal_limit);

            //cout << withdrawal_limit_int;
            // cout << userID << "" << pass << " " << ID << " " << password << endl;
            if (ID == userID && password == pass)
            {
                string card_num, card_pin;
                UserClient user(userID.c_str(), username.c_str(), address.c_str(), cnic.c_str(), loginID.c_str(), pass.c_str(), balance_int, withdrawal_limit_int);
                while (getline(card_file, line))
                {
                    card_pin = "";
                    istringstream iss(line);
                    getline(iss >> ws, userID, ',');
                    getline(iss >> ws, card_num, ',');
                    getline(iss >> ws, card_pin, ',');

                    if (ID == userID && card_pin != "")
                    {
                        user.card_details.set_card_pin(card_pin);
                        cout << "account info found with card pin" << endl;
                        break;
                    }
                }

                cout << "Logged into the account successfully" << endl;
                user_flag = true;
                // Additional logic for user login can be added here
                return user;
            }
        }

        file.close();
        card_file.close();
    }

}

CompanyClient companyLogin()
{

    string emp_ID, comp_ID, pass, employee_ID, company_ID;
    bool user_flag = false;

    ifstream com_file("companies.txt");
    if (!com_file.is_open())
    {
        cout << "Unable to open users file." << endl;
    }

    ifstream emp_file("company_employees.txt");
    if (!emp_file.is_open())
    {
        cout << "Unable to open users file." << endl;
    }

    string ID, password;
    bool comp_flag = false;
    while (!comp_flag)
    {

        cout << "Enter Company ID: ";
        cin >> comp_ID;
        cout << "Enter Password: ";
        cin >> pass;
        cout << "Employee User ID:";
        cin >> emp_ID;

        string line;
        while (getline(com_file, line))
        {
            istringstream iss(line);
            string ID, comp_name, address, tax_number, loginID, password;
            string balance, withdrawal_limit;

            getline(iss >> ws, ID, ',');
            getline(iss >> ws, comp_name, ',');
            getline(iss >> ws, address, ',');
            getline(iss >> ws, tax_number, ',');
            getline(iss >> ws, loginID, ',');
            getline(iss >> ws, password, ',');
            getline(iss >> ws, balance, ',');
            getline(iss >> ws, withdrawal_limit, ',');

            double balance_int = stoi(balance);
            double withdrawal_limit_int = stoi(withdrawal_limit);
            // Assuming comp_ID and pass are read from somewhere
            if (comp_ID == ID && pass == password)
            {
                emp_file.clear();  // Reset flags in case EOF was reached in previous iteration
                emp_file.seekg(0); // Move back to the beginning of the file
                cout << "ok" << endl;

                string employee_ID, company_ID;
                while (getline(emp_file, line))
                {
                    istringstream emp_iss(line);
                    getline(emp_iss >> ws, employee_ID, ',');
                    getline(emp_iss >> ws, company_ID, ',');

                    if (comp_ID == company_ID && employee_ID == emp_ID)
                    {
                        // Found a matching employee
                        CompanyClient comp(ID.c_str(), comp_name.c_str(), address.c_str(), tax_number.c_str(), withdrawal_limit_int, balance_int, loginID.c_str(), password.c_str());
                        comp_flag = true;
                        cout << "Logged in successfully!" << endl;
                        return comp;
                        // Exit the inner loop since we found the user
                    }
                }
            }
        }
    }
}

BankingEmployee bankLogin()
{
    string loginID, password, ID, pass;
    bool user_flag = false;

    ifstream bank_file("admin.txt");
    if (!bank_file.is_open())
    {
        cout << "Unable to open bank admins file." << endl;
    }

    while (!user_flag)
    {
        cout << "Enter login ID: ";
        cin >> loginID;
        cout << "Enter password: ";
        cin >> password;

        bank_file.clear();  // Reset flags in case EOF was reached in previous iteration
        bank_file.seekg(0); // Move back to the beginning of the file

        string line;
        while (getline(bank_file, line))
        {
            istringstream iss(line);
            if (getline(iss >> ws, ID, ',') && getline(iss >> ws, pass, ','))
            {
                if (loginID == ID && password == pass)
                {
                    BankingEmployee admin(ID.c_str(), pass.c_str());
                    user_flag = true;
                    cout << "Logged in successfully!" << endl;
                    // Additional logic for bank login can be added here
                    return admin; // Exit the loop since we found the user
                }
            }
        }
    }

    bank_file.close();
}

void Menu()
{

    char ch;
    bool flag = false;
    bool user_flag = false;

    while (true)
    {
    Menu:
        cout << "---------------------------- BANKING MANAGEMENT SYSTEM ----------------------------" << endl;
        cout << "Press 1. for Login to Account" << endl;
        cout << "Press 2. for opening New Account" << endl;
        cout << "(To approve new account login by Bank Employee only by pressing first 1 then 3 then write user name and password from admin.txt file then approve the new account.)" << endl;
        cout << "Press 3. for Exit" << endl;
        cout << "Enter : ";
        cin >> ch;
        if (ch == '1')
        {
            while (true)
            {
                cout << "Press 1 for Login for User Account" << endl;
                cout << "Press 2 for Login for Company Affiliated Account" << endl;
                cout << "Press 3 for Login for Bank Employee" << endl;
                cout << "Press 4 for Menu" << endl;
                cout << "Enter: ";
                cin >> ch;

                if (ch == '1')
                {
                    UserClient user = userLogin(user_flag);
                    //cout << "limit : " <<  user.get_daily_limit();
                    int count = 0;
                    while (count < 3)
                    {
                        if (user_flag == false)
                        {
                            count++;
                            cout << "Login was unsuccessful! Try Again!" << endl;
                            UserClient user = userLogin(user_flag);
                        }

                        else
                        {
                            break;
                        }
                    }
                    if (count == 3)
                    {
                        user.freezeAccount(user.get_userID());
                    }

                    string tmp;

                    if (user.card_details.get_card_pin() == "")
                    {
                        string pin;
                        bool pin_flag = true;
                        while (true) {

                            cout << "Set you card pin (6 digits)" << endl;
                            cin >> pin;

                            if (pin.length() == 6) {
                                for (char digit : pin) {
                                    if (!isdigit(digit)) {
                                        pin_flag = false;
                                        break;
                                    }
                                }
                                if (pin_flag) {
                                    break;
                                }
                                else if (!pin_flag) {
                                    cout << "Kindly Enter valid Pin!!" << endl;
                                }
                            }
                            else {
                                cout << "Kindly Enter valid 6 digit Pin!!" << endl;
                            }
                        }


                        user.card_details.set_card_pin(pin);

                        fstream file("cards.txt");
                        if (!file)
                        {
                            cout << "File could not be opened" << endl;
                            return;
                        }

                        string ID = user.get_userID();

                        cout << ID;

                        // cout <<  "ID : " << ID;
                        string line, test_ID, file_ID, line_data;

                        bool found = false;
                        while (getline(file, line) && !found)
                        {
                            istringstream iss(line);
                            if (getline(iss, test_ID, ','))
                            {
                                stringstream(test_ID) >> file_ID;
                                cout << file_ID << " " << ID << endl;
                                if (ID == file_ID)
                                {
                                    found = true;
                                    cout << "found!";
                                    // getline(iss, line_data);
                                    // file.seekp(static_cast<int>(file.tellg()) - line_data.length(), ios::cur);
                                    // file << ", " << pin;
                                    vector<Card> cards = readCardsFromFile("cards.txt");

                                    // Adding pin to card with ID 2
                                    addPinToCard(cards, file_ID, pin);

                                    writeCardsToFile("cards.txt", cards);
                                    break;
                                }
                            }
                        }

                        file.close();
                        //delete[] ID;
                    }

                    while (true)
                    {
                        char ch;
                        cout << "Press 1 to Deposit" << endl;
                        cout << "Press 2 to Withdraw" << endl;
                        cout << "Press 3 to Transfer" << endl;
                        cout << "Press 4 for Menu" << endl;
                        cout << "Enter : ";
                        cin >> ch;

                        if (ch == '1')
                        {
                            int amount;
                            cout << "Enter amount :";
                            cin >> amount;
                            user.viewBalance();
                            user.deposit(amount);
                            //break;
                        }
                        else if (ch == '2')
                        {
                            int amount;
                            cout << "Enter amount :";
                            cin >> amount;
                            user.withdraw(amount);
                            //break;
                        }
                        else if (ch == '3')
                        {
                            int amount;
                            string ID;
                            cout << "Enter amount :";
                            cin >> amount;
                            cout << "Reciever Account ID: ";
                            cin >> ID;
                            user.transfer(ID, amount);
                            //break;
                        }

                        else if (ch == '4') {
                            break;
                        }

                        else
                        {
                            cout << "Invalid Input!!" << endl;
                        }
                    }

                    break;
                }
                else if (ch == '2')
                {
                    CompanyClient comp = companyLogin();

                    while (true)
                    {
                        char ch;
                        cout << "Press 1 to Deposit" << endl;
                        cout << "Press 2 to Withdraw" << endl;
                        cout << "Press 3 to Transfer" << endl;
                        cout << "Press 4 to Request Loan" << endl;
                        cout << "Press 5 for Menu" << endl;
                        cout << "Enter : ";
                        cin >> ch;

                        if (ch == '1')
                        {
                            int amount;
                            cout << "Enter amount :";
                            cin >> amount;
                            comp.deposit(amount);
                            //break;
                        }
                        else if (ch == '2')
                        {
                            int amount;
                            cout << "Enter amount :";
                            cin >> amount;
                            comp.withdraw(amount);
                            //break;
                        }
                        else if (ch == '3')
                        {
                            int amount;
                            string ID;
                            cout << "Enter amount :";
                            cin >> amount;
                            cout << "Reciever Account ID: ";
                            cin >> ID;
                            comp.transfer(ID, amount);
                            //break;
                        }
                        else if (ch == '4')
                        {
                            int amount;
                            cout << "Enter the amount for loan:";
                            cin >> amount;
                            comp.applyForLoan(amount);
                            //break;
                        }

                        else if (ch == '5') {
                            break;
                        }

                        else
                        {
                            cout << "Invalid input" << endl;
                        }
                    }
                }
                else if (ch == '3')
                {
                    BankingEmployee admin = bankLogin();

                    while (true)
                    {
                        char ch;
                        cout << "Press 1 to Approve Accounts" << endl;
                        cout << "Press 2 to View all User Accounts" << endl;
                        cout << "Press 3 to View all Company Accounts" << endl;
                        cout << "Press 4 to Approve Loan" << endl;
                        cout << "Press 5 to View Transaction History of the Bank" << endl;
                        cout << "Press 6 for Menu" << endl;

                        cin >> ch;

                        if (ch == '1')
                        {
                            admin.approveAccount();
                        }
                        if (ch == '2')
                        {
                            admin.viewUserClients();
                        }
                        if (ch == '3')
                        {
                            admin.viewCompanyClients();
                        }
                        if (ch == '4')
                        {
                            admin.approveLoans();
                        }
                        if (ch == '5')
                        {
                            string ID;
                            cout << "Enter Account ID to view transaction history: ";
                            cin >> ID;
                            admin.viewTransactionHistory(ID);
                        }

                        else if (ch == '6') {
                            break;
                        }

                        else {
                            cout << "Enter Valid Option!!" << endl;
                        }
                    }
                }
                else if (ch == '4')
                {
                    break;
                }

                else
                {
                    cout << "Invalid Input" << endl;
                }
            }
        }

        else if (ch == '2')
        {
            while (true)
            {
                char ch;
                cout << "Press 1 to Create User Account" << endl;
                cout << "Press 2 to Create Company Account" << endl;
                cout << "Press 3 to Menu" << endl;
                cout << "Enter...   ";
                cin >> ch;
                if (ch == '1')
                {

                    string userID, username, address, CNIC, login, password;
                    double withdrawal_limit;

                    while (true) {
                        string line, file_ID;
                        cout << "Enter User ID:";
                        cin >> userID;
                        ifstream user_file("users.txt");

                        if (!user_file) {
                            cerr << "Unable to open the file!";
                            return;
                        }
                        bool file_flag = false;
                        while (getline(user_file, line)) {
                            istringstream iss(line);
                            getline(iss >> ws, file_ID, ',');
                            if (file_ID == userID) {
                                cout << "This ID already Exists. Kindly Enter any other ID!!" << endl;
                                file_flag = true;
                                break;
                            }
                        }
                        if (!file_flag) {
                            break;
                        }
                    }

                    cout << "Enter Username: ";
                    cin >> username;
                    cout << "Enter Address: ";
                    cin >> address;

                    while (true) {
                        bool CNIC_flag = true;
                        cout << "Enter CNIC: ";
                        cin >> CNIC;

                        if (CNIC.length() == 13) {
                            for (char digit : CNIC) {
                                if (!isdigit(digit)) {
                                    CNIC_flag = false;
                                    break;
                                }
                            }
                            if (CNIC_flag) {
                                break;
                            }
                            else if (!CNIC_flag) {
                                cout << "Kindly Enter Valid CNIC!!" << endl;
                            }
                        }
                        else {
                            cout << "Kindly Enter Valid 13 digit CNIC!!" << endl;
                        }
                    }

                    cout << "Enter Login ID: ";
                    cin >> login;
                    cout << "Enter Password: ";
                    cin >> password;
                    cout << "Your Estimated Daily Withdrawal limit : ";
                    cin >> withdrawal_limit;

                    // remaining code for exceptional handling

                    UserClient user(userID, username.c_str(), address.c_str(), CNIC.c_str(), login.c_str(), password.c_str(), withdrawal_limit);
                    user.saveUserDataAndApply();
                    cout << "Successfully Applied for the Account. Wait for the Approval" << endl;
                }

                else if (ch == '2')
                {
                    string compID, comp_name, address, tax_number, login, password;
                    double withdrawal_limit;
                    while (true) {
                        string line, file_ID;
                        cout << "Enter User ID:";
                        cin >> compID;
                        ifstream user_file("companies.txt");

                        if (!user_file) {
                            cerr << "Unable to open the file!";
                            return;
                        }
                        bool file_flag = false;
                        while (getline(user_file, line)) {
                            istringstream iss(line);
                            getline(iss >> ws, file_ID, ',');
                            if (file_ID == compID) {
                                cout << "This ID already Exists. Kindly Enter any other ID!!" << endl;
                                file_flag = true;
                                break;
                            }
                        }
                        if (!file_flag) {
                            break;
                        }
                    }
                    cout << "Enter Username: ";
                    cin >> comp_name;
                    cout << "Enter Address: ";
                    cin >> address;
                    cout << "Enter CNIC: ";
                    cin >> tax_number;
                    cout << "Enter Login ID: ";
                    cin >> login;
                    cout << "Enter Password: ";
                    cin >> password;
                    cout << "Your Estimated Daily Withdrawal limit : ";
                    cin >> withdrawal_limit;

                    // remaining code for exceptional handling
                    CompanyClient comp(compID, comp_name.c_str(), address.c_str(), tax_number.c_str(), withdrawal_limit, login.c_str(), password.c_str());
                    comp.saveUserDataAndApply();
                    cout << "Successfully Applied for the Account. Wait for the Approval" << endl;
                }

                else if (ch == '3')
                {
                    goto Menu;
                }

                else
                {
                    cout << "Invalid Input" << endl;
                }
            }
        }
        else if (ch == '3')
        {
            cout << "Thanks for Using!" << endl;
            return;
        }

        else
        {
            cout << "Invalid Input" << endl;
        }
    }
}

int main()
{
    Menu();

    return 0;
}