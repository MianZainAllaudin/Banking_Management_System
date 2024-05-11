# Banking_Management_System
This project implements a banking management system using C++ and object-oriented programming (OOP) concepts. It provides functionality for managing user accounts, company accounts, and transactions, while ensuring data integrity and security.

Objectives:

The main objectives of this project are to demonstrate proficiency in OOP concepts such as abstraction, encapsulation, polymorphism, inheritance, association, aggregation, and composition. It aims to efficiently manage customer data for the Bank and provide necessary functionalities for different stakeholders.

Features

User Client: Can open a single user account, deposit/withdraw funds, view account balance/transaction history, transfer funds to other accounts.

Company Client: Can open a multiple user account, deposit/withdraw funds, view account balance/transaction history, transfer funds to user client accounts, request loans.

Banking Employee: Can login, view client accounts, approve/reject new account applications, approve/reject loan requests, view transaction history, freeze/close accounts.

Requirements

Accounts:-

User Client:

Open account with full name, address, phone, CNIC, login ID, password, estimated daily withdrawal limit.
Deposit/withdraw funds, view balance/transaction history, transfer funds.

Company Client:

Open account with company name, address, tax number, estimated daily withdrawal limit, account ID, password.

Deposit/withdraw funds, view balance/transaction history, transfer funds to user client accounts, request loans.

Banking Employee:

Login using user ID and password, view client accounts, approve/reject applications/loans, view transaction history, freeze/close accounts.

Files:-

users.txt: Store user client information.

companies.txt: Store company client information.

companies_employees.txt: Store company-employee relationships.

admin.txt: Store banking employee login information.

transactions.txt: Store transaction history.

cards.txt: Store credit card information.

Transactions

Deposit: Add funds to account.

Withdraw: Remove funds from account.

Transfer: Transfer funds between accounts.

Installation and Usage:-

Clone the repository:

bash

Copy code

git clone https://github.com/MianZainAllaudin/Banking_Management_System.git

Compile the source code:

bash

Copy code

g++ main.cpp -o banking_system

Run the executable:

bash

Copy code

./banking_system

Future Improvements

Implement GUI for better user interaction.

Add more security features such as OTP for transactions.

Improve error handling and logging mechanisms.

Contributors
Zain Allaudin
