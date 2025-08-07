// ead >> x;
// read se x me jara
//         read
//     << x;
//     x se read me jara
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
// dfghdfghdgf
// yukyty
class BankAccount
{
private:
    string Name;
    int AccNumber;
    int long Balance;
    string CreationDate;
    string Type;
    string MobNumber;

public:
    void CreateAccount();
    void Deposit();
    void Withdraw();
    void Delete();
    void Print();
    void Transfer();
};
void BankAccount::CreateAccount()
{
    ifstream openfile("accno.txt");
    int lastno = 0;
    if (openfile >> lastno)
    {
        AccNumber = lastno;
    }
    else
        AccNumber = 1;

    openfile.close();
    cout << "Enter Name:\n";
    cin.ignore();
    getline(cin, Name); // space rhega bich me to

    // cin >> Name;
    do
    {
        cout << "Enter first amount deposited(must be abve 500Rs):\n";
        cin >> Balance;
        if (Balance < 500)
            cout << "min 500 rs required for the first time\n";
    } while (Balance < 500);

    cout << "Enter today's date:\n";
    cin >> CreationDate; // cin as no space in between
    cout << "Enter Account Type:\n";
    cin >> Type;
    cout << "Enter mobile number\n";
    cin >> MobNumber;

    ofstream file("BankData.txt", ios::app);
    file << AccNumber << "|" << Name << "|" << Balance << "|" << CreationDate << "|" << Type << "|" << MobNumber << endl;
    file.close();
    ofstream nextno("accno.txt");
    nextno << AccNumber + 1;
    nextno.close();
    cout << "Your Account number is " << AccNumber;
}
/*
void concept explaination()
{concepts:
The Problem We're Solving
When we read a line from the file like this:
123|John Doe|5000|2024-01-15|Savings|9876543210
We need to separate each piece of data (account number, name, balance, etc.) that's separated by the | character.
Step-by-Step Explanation:
1. stringstream ss(line);
cppstringstream ss(line);

Creates a stringstream object from the entire line
Think of it like putting the whole line into a "string processor" that can break it apart
Example: ss now contains "123|John Doe|5000|2024-01-15|Savings|9876543210"

2. Declare string variables to store each field:
cppstring accStr, name, balStr, date, type, mob;

These will hold each piece of data as strings (initially)

3. Extract each field using getline() with delimiter:
cppgetline(ss, accStr, '|');    // Reads until first '|'
getline(ss, name, '|');      // Reads until next '|'
getline(ss, balStr, '|');    // Reads until next '|'
getline(ss, date, '|');      // Reads until next '|'
getline(ss, type, '|');      // Reads until next '|'
getline(ss, mob, '|');       // Reads the rest
What happens:

accStr gets "123"
name gets "John Doe"
balStr gets "5000"
date gets "2024-01-15"
type gets "Savings"
mob gets "9876543210"

4. Convert strings to proper data types:
cppint accNum = stoi(accStr);    // "123" → 123 (integer)
long balance = stol(balStr);  // "5000" → 5000 (long integer)

stoi() = string to integer
stol() = string to long

Why This Approach?
Old Problem (using >> operator):
cpp// This FAILS with names like "John Doe"
read >> accNumber >> name >> balance;
// Would read: accNumber=123, name="John", balance tries to read "Doe" (ERROR!)
New Solution (using delimiters):
cpp// This WORKS with names containing spaces
getline(ss, name, '|');  // Reads everything until '|', including spaces
Visual Example:
File line: "123|John Doe|5000|2024-01-15|Savings|9876543210"
           ↓    ↓        ↓    ↓          ↓       ↓
         accStr name   balStr date      type    mob}
   */

void BankAccount::Deposit()
{
    int amount, accno;
    cout << "enter you Bank Accunt Number:\n";
    cin >> accno;
    cout << "enter amount to be deposited :\n";
    cin >> amount;
    ifstream readfile("BankData.txt");
    ofstream tempfile("temp.txt");
    string line;
    // BankAccount a;
    bool found = false;
    // while (readfile >> a.AccNumber >> a.Name >> a.Balance >> a.CreationDate >> a.Type >> a.MobNumber)
    while (getline(readfile, line))
    {
        stringstream ss(line);
        string StrAccno, Name, StrBalance, CreationDate, Type, MobNumber;
        getline(ss, StrAccno, '|');
        getline(ss, Name, '|');
        getline(ss, StrBalance, '|');
        getline(ss, CreationDate, '|');
        getline(ss, Type, '|');
        getline(ss, MobNumber, '|');
        int SearchAccno = stoi(StrAccno);
        long Balance = stol(StrBalance);

        if (SearchAccno == accno)
        {
            found = true;
            Balance = Balance + amount;
            cout << "Amount is deposited successfully\n";
        }
        tempfile << SearchAccno << "|" << Name << "|" << Balance << "|" << CreationDate << "|" << Type << "|" << MobNumber << endl;
    }
    remove("BankData.txt");
    rename("temp.txt", "BankData.txt");

    if (!found)

        cout << "Account number not found\n";
    readfile.close();
}
void BankAccount::Withdraw()
{
    int amount, accno;
    cout << "enter you Bank Accunt Number:\n";
    cin >> accno;

    ifstream readfile("BankData.txt");
    ofstream tempfile("temp.txt");
    // BankAccount a;
    string line;
    bool found = false;
    while (getline(readfile, line))
    {
        stringstream ss(line);
        string StrAccno, Name, StrBalance, CreationDate, Type, MobNumber;
        getline(ss, StrAccno, '|');
        getline(ss, Name, '|');
        getline(ss, StrBalance, '|');
        getline(ss, CreationDate, '|');
        getline(ss, Type, '|');
        getline(ss, MobNumber, '|');
        int SearchAccno = stoi(StrAccno);
        long Balance = stol(StrBalance);

        if (SearchAccno == accno)
        {
            found = true;
            do
            {
                cout << "enter amount to be deposited :\n";
                cin >> amount;
                if (amount > Balance)
                    cout << "Balance not suficient";
                else
                {
                    Balance = Balance - amount;
                    cout << "Amount is withdrawn successfully\n";
                }
            } while (amount > Balance);
        }
        tempfile << SearchAccno << "|" << Name << "|" << Balance << "|" << CreationDate << "|" << Type << "|" << MobNumber << endl;

        // tempfile << a.AccNumber << " " << a.Name << " " << a.Balance << " " << a.CreationDate << " " << a.Type << " " << a.MobNumber << endl;
    }
    readfile.close();
    remove("BankData.txt");
    rename("temp.txt", "BankData.txt");

    if (!found)

        cout << "Account number not found\n";
}
void BankAccount::Delete()
{
    int accno;
    cout << "enter account number to be deleted\n";
    cin >> accno;
    // BankAccount  b;
    ifstream readfile("BankData.txt");
    ofstream tempfile("temp.txt");
    string line;
    bool found = false;
    while (getline(readfile, line))
    {
        stringstream ss(line);
        string StrAccno, Name, StrBalance, CreationDate, Type, MobNumber;
        getline(ss, StrAccno, '|');
        getline(ss, Name, '|');
        getline(ss, StrBalance, '|');
        getline(ss, CreationDate, '|');
        getline(ss, Type, '|');
        getline(ss, MobNumber, '|');
        int SearchAccno = stoi(StrAccno);
        long Balance = stol(StrBalance);

        if (SearchAccno == accno)
        {
            found = true;

            cout << "Account deleted successfully";
            cout << "Account details were:\n"
                 << "Account Holder Name: " << Name << endl
                 << "Account Number: " << SearchAccno << endl
                 << "Balance: " << Balance << endl
                 << "Creation Date: " << CreationDate << endl
                 << "Account Type: " << Type << endl
                 << "Mobile Number: " << MobNumber << endl;
        }
        else
            tempfile << SearchAccno << "|" << Name << "|" << Balance << "|" << CreationDate << "|" << Type << "|" << MobNumber << endl;
    }
    tempfile.close();
    remove("BankData.txt");
    rename("temp.txt", "BankData.txt");
    if (!found)

        cout << "Account not found\n";
}
void BankAccount::Print()
{
    // BankAccount a;
    ifstream readfile("BankData.txt");
    string line;
    if (!readfile.is_open())
    {
        cout << "Unable to open file or no accounts exist.\n";
        return;
    }
    cout << "\n-------ALL ACOUNT DETAILS-------\n";
    bool hasaccounts = false;
    while (getline(readfile, line))
    {
        hasaccounts = true;
        stringstream ss(line);
        string StrAccno, Name, StrBalance, CreationDate, Type, MobNumber;
        getline(ss, StrAccno, '|');
        getline(ss, Name, '|');
        getline(ss, StrBalance, '|');
        getline(ss, CreationDate, '|');
        getline(ss, Type, '|');
        getline(ss, MobNumber, '|');
        int SearchAccno = stoi(StrAccno);
        long Balance = stol(StrBalance);

        cout << "-------------------------------------------------------------------------------------\n";
        cout << "Account Number: " << SearchAccno << endl
             << "Account Holder Name: " << Name << endl
             << "Balance: " << Balance << endl
             << "Creation Date: " << CreationDate << endl
             << "Account Type: " << Type << endl
             << "Mobile Number: " << MobNumber << endl;
        cout << "-------------------------------------------------------------------------------------\n";
    }
    if (!hasaccounts)
        cout << "NO Accounts in the bank\n";
    readfile.close();
}
void BankAccount::Transfer()
{
    int accno, transfaccno, amount;

    cout << "enter your account number:\n";
    cin >> accno;
    cout << "enter account no to which you want to transfer money:\n";
    cin >> transfaccno;
    cout << "enter amount to tranfer\n";
    cin >> amount;
    ifstream readfile("BankData.txt");
    // ifstream read1("BankData.txt");
    ofstream tempfile("temp.txt");
    // BankAccount a, receivertemp, sendertemp;
    string line;
    bool found = false;
    int senderbal = 0;
    bool senderfound = false, receiverfound = false, receiversaved = false;
    string SenderName, SenderCreationDate, SenderType, SenderMobNumber;
    long SenderBalance = 0;
    int SenderAccno = 0;
    string ReceiverName, ReceiverCreationDate, ReceiverType, ReceiverMobNumber;
    long ReceiverBalance = 0;
    int ReceiverAccno = 0;
    // bool found1 = false, found2 = false;
    // dono mese kons  find nahi hua uske liye 2 found use kar sakta but abhi ke liye skippped also me jabta found nahi hota tsbtak do while loop use kar sakta hun taki par custome will be bored ;
    while (getline(readfile, line))
    {
        stringstream ss(line);
        string StrAccno, Name, StrBalance, CreationDate, Type, MobNumber;
        getline(ss, StrAccno, '|');
        getline(ss, Name, '|');
        getline(ss, StrBalance, '|');
        getline(ss, CreationDate, '|');
        getline(ss, Type, '|');
        getline(ss, MobNumber, '|');
        int SearchAccno = stoi(StrAccno);
        long Balance = stol(StrBalance);
        if (accno == SearchAccno)
        {
            senderfound = true;

            if (amount <= Balance)
            {
                SenderName = Name, SenderCreationDate = CreationDate, SenderType = Type, SenderMobNumber = MobNumber;
                SenderBalance = Balance;
                SenderAccno = SearchAccno;
                senderbal = amount;
            }
            else
            {
                cout << "insufficient balance\n";
                tempfile << SearchAccno << "|" << Name << "|" << Balance << "|" << CreationDate << "|" << Type << "|" << MobNumber << endl;
                break;
            }
        }
        else if (SearchAccno == transfaccno)
        {
            receiverfound = true;
            ReceiverName = Name, ReceiverCreationDate = CreationDate, ReceiverType = Type, ReceiverMobNumber = MobNumber;
            ReceiverBalance = Balance;
            ReceiverAccno = SearchAccno;

            receiversaved = true;
        }
        else

            tempfile << SearchAccno << "|" << Name << "|" << Balance << "|" << CreationDate << "|" << Type << "|" << MobNumber << endl;
    }
    if (receiverfound && senderbal > 0)
    {
        ReceiverBalance = ReceiverBalance + senderbal;
        SenderBalance = SenderBalance - senderbal;
        tempfile << SenderAccno << "|" << SenderName << "|" << SenderBalance << "|" << SenderCreationDate << "|" << SenderType << "|" << SenderMobNumber << endl;
        tempfile << ReceiverAccno << "|" << ReceiverName << "|" << ReceiverBalance << "|" << ReceiverCreationDate << "|" << ReceiverType << "|" << ReceiverMobNumber << endl;
    }

    tempfile.close();
    remove("BankData.txt");
    rename("temp.txt", "BankData.txt");

    if (!senderfound || !receiverfound)
        cout << "one or both Accounts not found\n";
}

int main()
{
    BankAccount KKKBank;
    int choice;
    do
    {
        cout << "-----Bank MENU-----\n";
        cout << "Enter 1 for creating acount\n";
        cout << "Enter 2 for Money deposite\n";
        cout << "Enter 3 for money withdraw\n";
        cout << "Enter 4 for deleting acount\n";
        cout << "Enter 5 for amount tranfer\n";
        cout << "Enter 6 for print all acount details\n";
        cout << "Enter 7 for exit\n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            KKKBank.CreateAccount();
            break;
        case 2:
            KKKBank.Deposit();
            break;
        case 3:
            KKKBank.Withdraw();
            break;
        case 4:
            KKKBank.Delete();
            break;
        case 5:
            KKKBank.Transfer();
            break;
        case 6:
            KKKBank.Print();
            break;

        default:
            break;
        }

    } while (choice != 7);
    return 0;
}