Bank Management System
A console-based bank management system built in C++ that provides essential banking operations including account creation, deposits, withdrawals, and account management with secure authentication.

Features
Secure Login System: Password-protected access with multiple authentication attempts
Account Management: Create and manage bank accounts (Savings/Current)
Transaction Operations:
Deposit funds
Withdraw funds (with minimum balance check)
Account Viewing:
Display all accounts
View specific account details
Filter accounts by balance criteria
Balance Filters:
View accounts with balance > ₹2,00,000
View dormant accounts (balance < ₹1,000)
Data Persistence: File-based storage using binary files
Prerequisites
C++ Compiler (GCC, MinGW, or Visual Studio)
Windows OS (uses conio.h for password masking)
Basic understanding of banking operations
Installation
Clone the repository:
bash
git clone https://github.com/yourusername/bank-management-system.git
cd bank-management-system
Compile the program:
bash
g++ "Bank Management System.cpp" -o BankSystem.exe
Run the executable:
bash
./BankSystem.exe
Usage
Login Credentials
Username: admin
Password: admin123
Menu Options
Create Account: Register a new bank account with personal details
Display All Accounts: View all registered accounts
Display Specific Account: Search and view a particular account
Withdraw: Withdraw funds from an account (minimum balance: ₹1,000)
Deposit: Deposit funds into an account
High Balance Accounts: View accounts with balance > ₹2,00,000
Dormant Accounts: View accounts with balance < ₹1,000
Exit: Close the application
Account Types
S: Savings Account
C: Current Account
Technical Details
Data Storage
Accounts are stored in Bank.dat binary file
Uses file stream operations for CRUD functionality
Data persists between program sessions
Security Features
Password masking during input
Maximum 3 login attempts
Password confirmation requirement
Minimum Balance Policy
Accounts must maintain a minimum balance of ₹1,000
Withdrawals are restricted if they breach this limit
Project Structure
bank-management-system/
│
├── Bank Management System.cpp    # Main source code
├── Bank.dat                       # Binary data file (auto-generated)
├── README.md                      # Project documentation
├── LICENSE                        # MIT License
└── .gitignore                     # Git ignore rules
Limitations
Single-user system (no concurrent access)
Windows-specific (uses conio.h)
No account deletion functionality
Basic security implementation
No transaction history tracking
Future Enhancements
Multi-user support with role-based access
Cross-platform compatibility
Account deletion and modification
Transaction history and statements
Interest calculation for savings accounts
Password encryption
GUI interface
Database integration (MySQL/SQLite)
Contributing
Contributions are welcome! Please follow these steps:

Fork the repository
Create a feature branch (git checkout -b feature/AmazingFeature)
Commit your changes (git commit -m 'Add some AmazingFeature')
Push to the branch (git push origin feature/AmazingFeature)
Open a Pull Request
License
This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgments
Built as an educational project to demonstrate file handling and OOP concepts in C++
Inspired by real-world banking systems
Contact
For questions or suggestions, please open an issue in the repository.

Note: This is an educational project and should not be used for actual banking operations without significant security enhancements.
