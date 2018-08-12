#include <iostream>
using namespace std;

// PROJECT CLASS
class Account
{
    int acc_num;
    char name[25];
    int dep;
    char type;

public:
    void menu(); // Function to display menu choices.
    void new_account(); // Function to create new account.
    void balance_enquiry() const; // Function to show account balance.
    void modify(); // Function to modify account data.
    void deposit(int); // Function to add amount to account balance.
    void withdraw(int); // Function to subtract amount from account balance.
    void show() const; // Function to show all account data.
    int return_acc_num() const; // Function to return account number.
    int return_dep() const; // Function to return account balance.
    int return_type() const; // Function to return type of account.
}; // Class ends here.

void Account::menu()
{
    cout << "1. NEW ACCOUNT" << endl;
    cout << "2. DEPOSIT" << endl;
    cout << "3. WITHDRAWAL" << endl;
    cout << "4. BALANCE ENQUIRY" << endl;
    cout << "5. ACCOUNT HOLDERS" << endl;
    cout << "6. CLOSE ACCOUNT" << endl;
    cout << "7. MODIFY ACCOUNT" << endl;
    cout << "8. EXIT" << endl;
}

void Account::new_account()
{
    // How can I assign a number (in order) for new account?
    do
    {
        cout << "Enter an account number (1 - 100): ";
        cin >> acc_num;
    } while (acc_num < 1 || acc_num > 100);

    cout << "Enter name of the account holder: ";
    cin.ignore();
    cin.getline(name, 25);

    cout << endl << "Enter type of account (C = Checking, S = Savings: ";
    cin >> type;
    type = toupper(type);

    cout << endl << "Enter initial amount to deposit: ";
    cin >> dep;

    cout << endl << "ACCOUNT CREATED..." << endl;
}

void Account::balance_enquiry() const
{
    cout << "Account Number: " << acc_num << endl;
    cout << "Account Holder Name: " << name << endl;
    cout << "Type of Account: " << type << endl;
    cout << "Account Balance: " << dep << endl;
}

void Account::modify()
{
    cout << "Account Number: " << acc_num << endl;
    cout << "Modify Account Holder Name: ";
    cin.ignore();
    cin.getline(name, 25);

    cout << "Modify Account Type: ";
    cin >> type;
    type = toupper(type);
}

void Account::deposit (int x)
{
    dep += x;
}

void Account::withdraw(int x)
{
    dep -= x;
}

void Account::show() const
{
    cout << acc_num << setw(25) << " " << name << setw(25) << " " << type << setw(25) << dep << endl;
}

int Account:: return_acc_num() const
{
    return acc_num;
}

int Account:: return_dep() const
{
    return dep;
}

char Account::return_type() const
{
    return type;
}

// FUNCTION DECLARATION
void write_acc(); // Function to write a record in a binary file.
void display_specific(int); // Function to display account data.
void mod_acc(int); // Function to modify record in file.
void delete_acc(int); // Function to delete record in file.
void display_all(); // Function to display all accounts data.
void deposit_withdraw(int, int); // Function to deposit/withdraw to/from account.
void introduction(); // My (Creator) introduction.

int main()
{
    int choice = 0;
    int num = 0;

    do 
    {
        cout << "Welcome to HKO Bank. What can we help you with today?" << endl;
        cout << endl << menu() << endl;
        cout << "Please select a number choice: ";
        cin >> choice;
    } while (choice < 1 || choice > 8);

    switch (choice)
    {
        case 1:
            write_acc();
            break;
    
        case 2:
            cout << "Enter Account Number: ";
            cin >> num;
            deposit_withdraw(num, 1);
            break;
    
        case 3:
            cout << "Enter Account Number: ";
            cin >> num;
            deposit_withdraw(num, 2);
            break;
        
        case 4:
            cout << "Enter Account Number: ";
            cin >> num;
            display_specific(num);
            break;
    
        case 5:
            display_all();
            break;
   
        case 6:
            cout << "Enter Account Number: ";
            cin >> num;
            delete_acc(num);
            break;
    
        case 7:
            cout << "Enter Account Number: ";
            cin >> num;
            mod_acc(num);
            break;
    
        case 8:
            cout << "THANKS FOR USING HKO BANK. COME AGAIN!" << endl;
            break;
    }

    return 0;
}

// FUNCTION TO WRITE IN FILE
void write_acc()
{
    Account acc;
    ofstream newfile;
    newfile.open ("account.txt");
    acc.new_account();
    newfile.write(reinterpret_cast<char *> (&acc), sizeof(Account)); // Not sure what this does??? Recheck.
    newfile.close();
}

// FUNCTION TO READ SPECIFIC RECORD FROM FILE
void display_specific(int n)
{
    Account acc;
    bool flag = false; // Not sure what this does? Recheck...
    ifstream file;
    file.open("account.txt");
    if(!file)
    {
        cout << "FILE ERROR. PRESS ANY KEY TO CONTINUE..." << endl;
        return;
    }

    cout << "BALANCE INFORMATION: " << endl;
    while (file.read(reinterpret_cast<char *> (&acc), sizeof(Account)))
    {
        if (acc.return_acc_num() == n) // Not sure what this does? Recheck...
        {
            acc.show();
            flag = true;
        }
    }

    file.close();
    if (flag == false) // Not sure what this does? Recheck...
    {
        cout << "ERROR. ACCOUNT NUMBER DOES NOT EXIST." << endl;
    }
}

// FUNCTION TO MODIFY RECORD OF FILE
void mod_acc(int n)
{
    bool found = false;
    Account acc;
    fstream File;
    File.open("account.txt");
    if (!File)
    {
        cout << "FILE ERROR. PRESS ANY KEY TO CONTINUE..." << endl;
        return;
    }

    while (!File.eof() && found == false)
    {
        File.read(reinterpret_cast<char *> (&acc), sizeof(Account));
        if (acc.return_acc_num() == n)
        {
            acc.show();
            cout << "Enter new data for the account modification: ";
            acc.modify();
            int pos = (-1)*static_cast<int>(sizeof(Account));
            File.write(reinterpret_cast<char *> (&acc), sizeof(Account));

            cout << "RECORD HAS BEEN UPDATED." << endl;
            found = true;
        }
    }

    File.close();
    if (found == false)
    {
        cout << "ERROR. RECORD NOT FOUND." << endl;
    }
}

// FUNCTION TO DELETE RECORD OF FILE
void delete_acc(int n)
{
    Account acc;
    ifstream file;
    ofstream file;

    file.open("account.txt")
    if (!file)
    {
        cout << "ERROR. PRESS ANY KEY TO CONTINUE..." << endl;
        return;
    }

    file.open("temporary.txt");
    while (file.read(reinterpret_cast<char *> (&acc), sizeof(Account)))
    {
        if (acc.return_acc_num() != n)
        {
            file.write(reinterpret_cast<char *> (&acc), sizeof(Account));
        }
    }

    file.close();
    file.close();
    remove("account.txt");
    rename("temporary.txt", "account.txt");
    cout << "RECORD DELETED." << endl;
}

// FUNCTION TO DISPLAY ALL ACCOUNTS
void display_all()
{
    Account acc;
    ifstream file;
    file.open("account.txt");
    if(!file)
    {
        "ERROR. PRESS ANY KEY TO CONTINUE..." << endl;
        return;
    }

    cout << "ACCOUNT HOLDERS: " << endl;
    cout << "ACCOUNT NO.:       NAME        TYPE        BALANCE" << endl;
    while (file.read(reinterpret_cast<char *> (&acc), sizeof(Account)))
    {
        acc.report();
    }
    file.close();
}

// FUNCTION TO DEPOSIT & WITHDRAW AMOUNTS
void deposit_withdraw(int n, int choice)
{
    int amount;
	bool found = false;
	Account acc;
	fstream File;
	File.open("account.txt");
	if(!File)
	{
		cout << "ERROR. PRESS ANY KEY TO CONTINUE..." << endl;
		return;
	}

	while (!File.eof() && found == false)
	{
		File.read(reinterpret_cast<char *> (&acc), sizeof(Account));
		if(acc.return_acc_num() == n)
		{
			acc.show();
			if (choice == 1)
			{
				cout << "Enter Deposit Amount: ";
				cin >> amount;
				acc.deposit(amount);
			}

			if (choice == 2)
			{
				cout << "Enter Withdrawal Amount: ";
				cin >> amount;
				
                int bal = acc.return_dep() - amount;
				acc.withdraw(amount);
			}

			int position =(-1)*static_cast<int>(sizeof(acc));
			File.write(reinterpret_cast<char *> (&acc), sizeof(Account));
			cout << "RECORD UPDATED." << endl;
			found = true;
	       }
         }
	File.close();
	if (found == false)
    {
		cout << "RECORD NOT FOUND." << endl;
    }
}

// INTRODUCTION FUNCTION 
void introduction()
{
    cout << "---------- HKO BANK PROJECT ----------" << endl;
    cout << "-------- MADE BY: HATICE OZEN --------" << endl;
    cout << "---- RAMAPO COLLEGE OF NEW JERSEY ----" << endl;
}