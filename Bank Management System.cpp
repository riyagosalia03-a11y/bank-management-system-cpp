#include<iostream>
#include<fstream>
#include<conio.h>
#include<iomanip>
#include<string>
using namespace std;

// Fixed-size char arrays instead of std::string to allow safe binary file I/O
class Bank
{
    protected:
        char name[50];
        char acc_no[20];
        char acc_type;
        double balance;

    public:
        void get()
        {
            cout << "\t\t\t\t------------------------------------------------" << endl;
            cout << "\t\t\t\tENTER DETAILS: " << endl << endl;
            cout << "\t\t\t\tEnter name: ";
            cin.ignore();
            cin.getline(name, 50);
            cout << "\t\t\t\tEnter account number: ";
            cin.getline(acc_no, 20);
            cout << "\t\t\t\tEnter type of account \n\t\t\t\t(Savings-S / Current-C): ";
            cin >> acc_type;
            cout << "\t\t\t\tEnter opening balance: ";
            cin >> balance;
            cout << endl << endl << "\t\t\t\tAccount created successfully" << endl;
            cout << "\t\t\t\t------------------------------------------------" << endl;
        }

        void display() const
        {
            cout << "\t\t\t\t" << left << setw(15) << acc_no << setw(20) << name << setw(12) << fixed << setprecision(2) << balance << setw(3) << (char)toupper(acc_type) << endl;
            cout << "\t\t\t\t------------------------------------------------------------------------" << endl;
        }

        void deposit(double amt)
        {
            balance += amt;
            cout << endl << "\t\t\t\tTransaction successful" << endl;
        }

        bool withdraw(double amt)
        {
            // Use >= so balance can reach exactly the minimum
            if (balance - amt >= 1000.0)
            {
                balance -= amt;
                cout << endl << "\t\t\t\tTransaction successful" << endl;
                return true;
            }
            else
            {
                cout << endl << "\t\t\t\tInsufficient funds. Minimum balance of 1000 must be maintained." << endl;
                return false;
            }
        }

        string get_acc_no() const
        {
            return string(acc_no);
        }

        double get_balance() const
        {
            return balance;
        }
};

// --- Helper to print table header ---
void printHeader()
{
    cout << "\t\t\t\t------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\tACCOUNT DETAILS: " << endl << endl;
    cout << "\t\t\t\t------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t" << left << setw(15) << "Account id" << setw(20) << "Name" << setw(12) << "Balance" << setw(3) << "Type" << endl;
    cout << "\t\t\t\t------------------------------------------------------------------------" << endl;
}

// --- Write new account to file ---
void write()
{
    Bank b;
    b.get();
    fstream f("Bank.dat", ios::app | ios::binary);
    if (!f)
    {
        cout << "\t\t\t\tError: Could not open file." << endl;
        return;
    }
    f.write((char*)&b, sizeof(b));
    f.close();
}

// --- Display all accounts ---
void read()
{
    Bank b;
    fstream f("Bank.dat", ios::in | ios::binary);
    if (!f)
    {
        cout << "\t\t\t\tNo records found." << endl;
        return;
    }
    printHeader();
    while (f.read((char*)&b, sizeof(b)))
    {
        b.display();
    }
    f.close();
}

// --- Deposit amount ---
void bank_deposit()
{
    Bank b;
    fstream f("Bank.dat", ios::in | ios::out | ios::binary);
    if (!f)
    {
        cout << "\t\t\t\tError: Could not open file." << endl;
        return;
    }
    double amt;
    string a_no;
    bool found = false;
    cout << "\t\t\t\tEnter account number: ";
    cin >> a_no;
    while (f.read((char*)&b, sizeof(b)))
    {
        streampos pos = f.tellg();
        if (a_no == b.get_acc_no())
        {
            cout << "\t\t\t\tEnter amount to be deposited: ";
            cin >> amt;
            b.deposit(amt);
            // Seek back to the start of this record and overwrite
            f.seekp((streamoff)pos - (streamoff)sizeof(b));
            f.write((char*)&b, sizeof(b));
            cout << endl << "\t\t\t\tUpdated balance:" << endl << endl;
            printHeader();
            b.display();
            found = true;
            break;
        }
    }
    f.close();
    if (!found)
        cout << "\t\t\t\tInvalid account number." << endl;
}

// --- Withdraw amount ---
void bank_withdraw()
{
    Bank b;
    fstream f("Bank.dat", ios::in | ios::out | ios::binary);
    if (!f)
    {
        cout << "\t\t\t\tError: Could not open file." << endl;
        return;
    }
    double amt;
    string a_no;
    bool found = false;
    cout << "\t\t\t\tEnter account number: ";
    cin >> a_no;
    while (f.read((char*)&b, sizeof(b)))
    {
        streampos pos = f.tellg();
        if (a_no == b.get_acc_no())
        {
            cout << "\t\t\t\tEnter amount to be withdrawn: ";
            cin >> amt;
            if (b.withdraw(amt))
            {
                f.seekp((streamoff)pos - (streamoff)sizeof(b));
                f.write((char*)&b, sizeof(b));
            }
            cout << endl << "\t\t\t\tUpdated balance:" << endl << endl;
            printHeader();
            b.display();
            found = true;
            break;
        }
    }
    f.close();
    if (!found)
        cout << "\t\t\t\tInvalid account number." << endl;
}

// --- Display specific account ---
void specific_acc()
{
    Bank b;
    // Open read-only — no ios::out which could truncate the file
    fstream f("Bank.dat", ios::in | ios::binary);
    if (!f)
    {
        cout << "\t\t\t\tError: Could not open file." << endl;
        return;
    }
    string a_no;
    bool found = false;
    cout << "\t\t\t\tEnter account number: ";
    cin >> a_no;
    printHeader();
    while (f.read((char*)&b, sizeof(b)))
    {
        if (a_no == b.get_acc_no())
        {
            b.display();
            found = true;
            break;
        }
    }
    f.close();
    if (!found)
        cout << "\t\t\t\tInvalid account number." << endl;
}

// --- Accounts with balance > 2,00,000 ---
void greater_than_2_lakh()
{
    Bank b;
    fstream f("Bank.dat", ios::in | ios::binary);
    if (!f)
    {
        cout << "\t\t\t\tNo records found." << endl;
        return;
    }
    cout << "\t\t\t\t------------------------------------------------" << endl;
    cout << "\t\t\t\tACCOUNTS WITH BALANCE > 2,00,000: " << endl << endl;
    cout << "\t\t\t\t------------------------------------------------" << endl;
    cout << "\t\t\t\t" << left << setw(15) << "Account id" << setw(20) << "Name" << setw(12) << "Balance" << setw(3) << "Type" << endl;
    cout << "\t\t\t\t------------------------------------------------" << endl;
    while (f.read((char*)&b, sizeof(b)))
    {
        if (b.get_balance() > 200000.0)
            b.display();
    }
    f.close();
}

// --- Accounts with balance < 1000 (dormant / minimum balance) ---
void minimum_balance()
{
    Bank b;
    fstream f("Bank.dat", ios::in | ios::binary);
    if (!f)
    {
        cout << "\t\t\t\tNo records found." << endl;
        return;
    }
    cout << "\t\t\t\t------------------------------------------------" << endl;
    cout << "\t\t\t\tDORMANT ACCOUNTS (Balance < 1000): " << endl << endl;
    cout << "\t\t\t\t------------------------------------------------" << endl;
    cout << "\t\t\t\t" << left << setw(15) << "Account id" << setw(20) << "Name" << setw(12) << "Balance" << setw(3) << "Type" << endl;
    cout << "\t\t\t\t------------------------------------------------" << endl;
    while (f.read((char*)&b, sizeof(b)))
    {
        if (b.get_balance() < 1000.0)
            b.display();
    }
    f.close();
}

// --- Secure password input using getch ---
string getPassword()
{
    string pwd = "";
    while (true)
    {
        char c = getch();
        if (c == 13)        // Enter key
            break;
        else if (c == 8)    // Backspace
        {
            if (!pwd.empty())
            {
                pwd.pop_back();
                cout << "\b \b";
            }
        }
        else
        {
            pwd += c;
            cout << "*";
        }
    }
    cout << endl;
    return pwd;
}

int main()
{
    int n;
    int trial = 0;
    const string user_id = "admin";
    const string password = "admin123";

    while (trial < 3)
    {
        system("cls");
        cout << "\t\t\t\tSIGN IN TO YOUR ACCOUNT" << endl << endl;
        cout << "\t\t\t\t------------------------------------------------" << endl;

        string user_name, user_password, confirm_password;

        cout << "\t\t\t\tUsername: ";
        cin >> user_name;
        cin.ignore();

        cout << "\t\t\t\t------------------------------------------------" << endl;
        cout << "\t\t\t\tPassword: ";
        user_password = getPassword();

        cout << "\t\t\t\t------------------------------------------------" << endl;
        cout << "\t\t\t\tConfirm Password: ";
        confirm_password = getPassword();

        cout << endl;
        trial++;

        if (user_id == user_name && password == user_password && user_password == confirm_password)
        {
            do
            {
                system("cls");
                cout << endl;
                cout << "\t\t\t\t\t\t" << "BANK MANAGEMENT SYSTEM" << endl << endl;
                cout << "\t\t\t\t------------------------- MENU -------------------------" << endl << endl;
                cout << "\t\t\t\t1. CREATE ACCOUNT" << endl;
                cout << "\t\t\t\t2. DISPLAY ALL ACCOUNTS" << endl;
                cout << "\t\t\t\t3. DISPLAY SPECIFIC ACCOUNT" << endl;
                cout << "\t\t\t\t4. WITHDRAW" << endl;
                cout << "\t\t\t\t5. DEPOSIT" << endl;
                cout << "\t\t\t\t6. ACCOUNTS WITH BALANCE GREATER THAN 2,00,000" << endl;
                cout << "\t\t\t\t7. DISPLAY DORMANT ACCOUNTS" << endl;
                cout << "\t\t\t\t0. EXIT" << endl << endl;
                cout << "\t\t\t\tEnter your choice: ";
                cin >> n;
                system("cls");

                switch (n)
                {
                    case 1: write();              
					break;
                    case 2: read();               
					break;
                    case 3: specific_acc();       
					break;
                    case 4: bank_withdraw();      
					break;
                    case 5: bank_deposit();       
					break;
                    case 6: greater_than_2_lakh(); 
					break;
                    case 7: minimum_balance();    
					break;
                    case 0: cout << "\t\t\t\tExiting... Goodbye!" << endl; 
					break;
                    default: cout << "\t\t\t\tInvalid choice. Please try again." << endl; 
					break;
                }

                if (n != 0)
                {
                    cin.ignore();
                    cin.get();
                }

            } while (n != 0);

            break; // Exit the login loop after successful session
        }
        else
        {
            cout << "\t\t\t\tInvalid username or password." << endl;
            if (trial < 3)
            {
                cout << "\t\t\t\tAttempts remaining: " << (3 - trial) << endl;
            }
            cin.ignore();
            cin.get();
        }
    }

    if (trial == 3)
    {
        system("cls");
        cout << endl << endl;
        cout << "\t\t\t\tUser authentication failed. Too many incorrect attempts." << endl;
        cin.ignore();
        cin.get();
    }

    return 0;
}
