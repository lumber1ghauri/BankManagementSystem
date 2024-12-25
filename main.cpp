#include <iostream>
#include <fstream>
#include <random>
#include <Windows.h>
// #include <ctime>
#include <algorithm>
#include <iomanip>

using namespace std;

void intro();

class User
{
private:
    string contactnum;
    static int count;

protected:
    string password;
    string name;
    int accountnum = 0;
    float initial_deposit;
    char accounttype;

public:
    User();
    void obtain_and_store_info();
    int randomize_acc_num();
    string set_password();
    string generate_password();
    static mt19937 &get_random_engine();
};

class login
{
    string nam[100], pass[100], cont_num[100];
    int acc_number[100];
    char acc_type[100];
    float initial_bal[100];

protected:
    int acc_num;

public:
    void swich();
    void Bill();
    void Tax();
    void Funds();
};
class manager
{
protected:
    string name;
    string passcode;
    string acc_num;
    string user_name[40];
    string user_accnum[40];
    string account;
    char acc_type[40];
    double initialBalance[40];
    string user_pin[40];
    string phone_no[40];

public:
    manager(string n, string p) : name(n), passcode(p)
    {
    }
    void display_data();
    void modify_data();
    void delete_account();
    void search_foracc();
    void write_to_file();
    void read_from_file();
    int delete_acc();

    void mainmenu();
    bool manager_passcode(string p)
    {
        // cout << "Enter Manager Pin \n";
        // cin >> passcode;
        if (passcode == p)
        {
            cout << "Correct Pin Entered \n ";
            cout << "Welcome Branch Manager " << name << endl;
            return true;
        }
        else
        {
            cout << "Warning !!!!!!! , Wrong Pin Entered \n ";
            return false;
        }
    }
};

int User::count = 0;

int main()
{
    intro();
    char ch;

    do
    {
        system("cls");

        cout << endl
             << endl
             << endl; // Menu for the user
        cout << right << setw(50) << "\t\t MAIN MENU \n";
        cout << right << setw(50) << "     1. Client \n ";
        cout << right << setw(50) << "     2. Manager \n ";
        cout << right << setw(47) << "     3. Exit \n ";

        cout << " For Client interface press 1 or for Manager interface press 2\t\t";
        cin >> ch;

        switch (ch)
        {
        case '1':
        {
            int choice;
            do
            {
                system("cls");
                cout << endl
                     << endl
                     << endl; // Menu for the user
                cout << right << setw(50) << "\t\t MAIN MENU \n";
                cout << right << setw(50) << "  1. Create new account \n";
                cout << right << setw(38) << "2. Log In \n";

                cout << right << setw(36) << "3. Exit \n";

                cout << "\n\n Please enter the number according to the operation you want to perform \t";
                cin >> choice;

                switch (choice)
                {
                case 1:
                {
                    system("cls");
                    User newUser;
                    newUser.obtain_and_store_info();
                    break;
                }
                case 2:
                {
                    system("cls");
                    login l;
                    l.swich();
                    break;
                }
                case 3:
                {
                    // Exit
                    cout << " \n\n\t\tThanks for using our bank services \n\n";
                    break;
                }
                default:
                    cout << "Invalid choice. Please enter a valid option." << endl;
                    break;
                }

                cout << "\n\n\t\tPress any key to continue.......";
                cin.ignore();
                cin.get();

            } while (choice != 3);
            break;
        }
        case '2':
        {
            manager bankManager("Modasir", "2334");
            string dp;

            cout << "Enter Your 4-digit Pin   \n ";
            cin >> dp;

            if (bankManager.manager_passcode(dp))
            {
                system("cls");
                bankManager.mainmenu();
            }
            else
            {
                cout << "Exit \n ";
            }
            break;
        }
        case '3':
            cout << " \n\n\t\tThanks for using our bank services \n\n";
            break;
        default:
            cout << " You entered an invalid choice. Please try again.";
            break;
        }

        cout << "\n\n\t\tPress any key to continue.......";
        cin.ignore();
        cin.get();

    } while (ch != '3');

    return 0;
}

User::User() : contactnum(""), initial_deposit(0), password("")
{
    count++;
}

void User::obtain_and_store_info()
{
    cout << "\t\t Please provide the below-mentioned information.\n\n";
    cout << "Enter your name: \t";
    cin >> name;

    cout << "\nEnter your active phone number: \t";
    cin.ignore();
    cin >> contactnum;

    cout << "\nPlease specify the type of account you want to open.\n ('S' for SAVING and 'C' for current): \t";
    cin >> accounttype;

    if (accounttype == 's' || accounttype == 'S')
    {
        cout << "\nYou can deposit a minimum of 5000 and a maximum of 10,000,000 Rs.\n";
        cout << "Enter the initial amount: \t";
        cin >> initial_deposit;

        // Validate initial deposit amount for savings account
        while (initial_deposit < 5000 || initial_deposit > 10000000)
        {
            cout << "\nInvalid deposit amount. Please enter a valid amount: \t";
            cin >> initial_deposit;
        }
    }
    else if (accounttype == 'c' || accounttype == 'C')
    {
        cout << "\nYou can deposit a minimum of 10000 and a maximum of 1,000,000 Rs.\n";
        cout << "\nEnter the initial amount: \t";
        cin >> initial_deposit;

        // Validate initial deposit amount for the current account
        while (initial_deposit < 10000 || initial_deposit > 1000000)
        {
            cout << "\nInvalid deposit amount. Please enter a valid amount: \t";
            cin >> initial_deposit;
        }
    }
    else
    {
        cout << "\nInvalid account type.\n";
        return;
    }

    cout << "\nDeposit amount accepted: \t" << initial_deposit << " Rs.\n";

    accountnum = randomize_acc_num();
    password = set_password();

    ofstream outputfile("user-info.txt", ios::app);

    if (outputfile.is_open())
    {

        outputfile << name << "\t";
        outputfile << accountnum << "\t";
        outputfile << password << "\t";
        outputfile << accounttype << "\t";
        outputfile << contactnum << "\t";
        outputfile << initial_deposit << "\n";

        outputfile.close();
    }
    else
    {
        cout << "Error opening file." << endl;
    }

    cout << " \n\t\tYour account number is: " << accountnum;
    cout << " \n\t\tYour password is: " << password;

    // sleep function here

    cout << "\nYour id is creating please wait";
    for (int i = 0; i < 4; i++)
    {
        cout << ".";
        Sleep(1000);
    }
    cout << "\a";
    cout << "\n\nYour id is created successfully " << endl;
}

int User::randomize_acc_num()
{
    fstream file("account number.txt", ios::in | ios::out | ios::app);

    if (!file)
    {
        cout << "Error opening file." << endl;
        return -1;
    }

    int acc_num;
    bool isUnique = false;
    const int MAX_ACCOUNTS = 100;

    int count = 0;
    while (file >> acc_num)
    {
        if (++count >= MAX_ACCOUNTS)
        {
            cout << "Maximum account numbers reached." << endl;
            file.close();
            return -1;
        }
    }

    mt19937 &random_engine = get_random_engine();
    uniform_int_distribution<int> dist(10000, 99999);

    int new_accountnum;
    do
    {
        new_accountnum = dist(random_engine);
        isUnique = true;

        file.clear();
        file.seekg(0);

        while (file >> acc_num)
        {
            if (new_accountnum == acc_num)
            {
                isUnique = false;
                break;
            }
        }
    } while (!isUnique);

    file.clear();
    file.seekp(0, ios::end);
    file << new_accountnum << endl;

    file.close();

    return new_accountnum;
}

mt19937 &User::get_random_engine()
{
    static mt19937 random_engine(static_cast<unsigned>(time(nullptr)));
    return random_engine;
}

string User::set_password()
{
    char choice;
    string pass;
    cout << "Do you want to set a password? (Y/N): ";
    cin >> choice;

    if (choice == 'Y' || choice == 'y')
    {
        cout << "Enter your 4-digit password: ";
        cin >> pass;

        while (pass.length() != 4 || !all_of(pass.begin(), pass.end(), ::isdigit))
        {
            cout << "Invalid password! Please enter a 4-digit password: ";
            cin >> pass;
        }

        cout << "Password set successfully!" << endl;
    }
    else if (choice == 'N' || choice == 'n')
    {
        pass = generate_password();
        cout << "Your generated password is: " << pass << endl;
    }
    else
    {
        cout << "Invalid choice." << endl;
    }

    return pass;
}

string User::generate_password()
{
    mt19937 &random_engine = get_random_engine();
    uniform_int_distribution<int> dist(1000, 9999); // Range for 4-digit password

    int generatedPassword = dist(random_engine);
    return to_string(generatedPassword); // Convert int to string
}

void login ::swich()
{
    int n = 0;
    int index = -1;

    ifstream ifile("user-info.txt");

    if (!ifile)
    {
        cout << "Error opening file." << endl; // Display error message if file cannot be opened
    }
    else
    {
        // Read customer information from the file
        do
        {
            ifile >> nam[n] >> acc_number[n] >> pass[n] >> acc_type[n] >> cont_num[n] >> initial_bal[n];
            n++;
        } while (!ifile.eof());
    }

    ifile.close(); // Close the file

    string pswd;

    cout << "Enter your account number: \t";
    cin >> acc_num;
    cout << "\nEnter your password: \t";
    cin >> pswd;

    cout << "Please wait";

    for (int i = 0; i < 4; i++)
    {
        cout << ".";
        Sleep(1000);
    }
    bool accountFound = false;

    // Search for the customer by name
    for (int m = 0; m < n; m++)
    {
        if (acc_num == acc_number[m] && pswd == pass[m])
        {
            index = m;
            accountFound = true;
            break;
        }
        /*else
        {
            cout << " Invalid account number or password\n";
            break;
        }*/
    }

    if (!accountFound)
    {
        cout << "\nAccount not found. Please check your account number and password.\n";
        return; // Exit the function
    }

    cout << "\nLogin Successful";

    for (int i = 0; i < 4; i++)
    {
        cout << ".";
        Sleep(1000);
    }

    char ch;

    do
    {

        system("cls");

        cout << "\n\t\t Welcome " << nam[index] << ". Please enter the operation./n";
        cout << endl
             << endl
             << endl; // Menu for the user
                      //  cout << right << setw(50) << "\t\t \n";
        cout << right << setw(43) << " 1. Check Info. \n";
        cout << right << setw(45) << " 2. Bill Payments \n";
        cout << right << setw(35) << " 3. Tax \n";
        cout << right << setw(45) << " 4. Fund Transfer \n";
        cout << right << setw(36) << " 5. Exit \n";

        cout << "\n\n Please enter the number according to the operation you want to perform \t";
        cin >> ch;

        switch (ch)
        {
        case '1':
        {
            system("cls");
            cout << "Name :\t\t\t" << nam[index] << endl;
            cout << "Account Number :\t" << acc_number[index] << endl;
            cout << "Account Type :\t\t" << acc_type[index] << endl;
            cout << "Contact Number :\t" << cont_num[index] << endl;
            cout << "Balance :\t\t" << initial_bal[index] << endl;

            break;
        }

        case '2':
        {
            // Display customers list
            system("cls");
            Bill();
            break;
        }
        case '3':
        {
            system("cls");
            Tax();

            break;
        }
        case '4':
        {
            system("cls");
            Funds();
            break;
        }

        case '5':
        {
            // Exit

            break;
        }
        default:
            cout << "Invalid choice. Please enter a valid option." << endl;
            break;
        }

        cout << "\n\n\t\tPress any key to continue.......";
        cin.ignore();
        cin.get();

    } while (ch != '5');
}

void login ::Bill()
{
    int n = 0;
    int index = -1;

    ifstream ifile("user-info.txt");

    if (!ifile)
    {
        cout << "Error opening file." << endl; // Display error message if file cannot be opened
    }
    else
    {
        // Read customer information from the file
        do
        {
            ifile >> nam[n] >> acc_number[n] >> pass[n] >> acc_type[n] >> cont_num[n] >> initial_bal[n];
            n++;
        } while (!ifile.eof());
    }

    ifile.close(); // Close the file

    // Search for the customer by name
    for (int m = 0; m < n; m++)
    {
        if (acc_num == acc_number[m])
        {
            index = m;
            break;
        }
    }

    char ch;
    // do{

    cout << "\n\n\nSelect the option you want to pay the bill of: \n";
    cout << "\n\n\t\t\t 1.Gas Bill ";
    cout << "\n\n\t\t\t 2.Electricity Bill ";
    cout << "\n\n\t\t\t 3.Credit Card Bill ";
    cout << "\n\n\t\t\t 4.Loan Installment \t\t\t";
    cout << "\n\n\t\t\t 5.Internet Service Provider Bill \t\t\t";
    cout << "\n\n\t\t\t 6. Exit ";

    cin >> ch;
    float amount, balance;

    switch (ch)
    {
    case '1':
        system("cls");
        balance = initial_bal[index];

        cout << " Your available balance is \t" << balance << endl;

        cout << "\n\nEnter the amount of your Gas bill: \t\t";
        cin >> amount;

        if (amount < balance)
        {
            cout << "\n\nYour bill has been paid.\n"
                 << endl
                 << endl;
            cout << " \n\t\tNOTE: \t 5% Bank charges are also deducted " << endl
                 << endl;
            balance = (balance - amount) * 0.95; // Deduct 10%
            initial_bal[index] = balance;

            cout << "\nYour updated balance is: \t" << initial_bal[index] << " Rs" << endl
                 << endl;

            ofstream myfile("user-info.txt", ios::out); // Open file in ios::app mode
            if (!myfile)
            {
                cout << "Error opening file." << endl;
            }
            else
            {
                // Write updated customer information to the file
                for (int i = 0; i < n - 1; i++)
                {
                    myfile << nam[i] << " \t" << acc_number[i] << " \t" << pass[i] << " \t" << acc_type[i] << "\t" << cont_num[i] << " \t" << initial_bal[i] << endl;
                }
                myfile.close();
                cout << "\nFile updated successfully." << endl;
            }
        }
        else
        {
            cout << "\n\n\t\tInsufficient balance to pay the bill." << endl;
        }
        break;

    case '2':
        system("cls");
        balance = initial_bal[index];

        cout << " Your available balance is \t" << balance << endl;

        cout << "\n\nEnter the amount of your Electricity bill: \t\t";
        cin >> amount;

        if (amount < balance)
        {
            cout << "\n\nYour bill has been paid.\n"
                 << endl
                 << endl;
            cout << " \n\t\tNOTE: \t 7% Bank charges are also deducted " << endl
                 << endl;
            balance = (balance - amount) * 0.93; // Deduct 10%
            initial_bal[index] = balance;

            cout << "\nYour updated balance is: \t" << initial_bal[index] << " Rs" << endl
                 << endl;

            ofstream myfile("user-info.txt", ios::out); // Open file in ios::app mode
            if (!myfile)
            {
                cout << "Error opening file." << endl;
            }
            else
            {
                // Write updated customer information to the file
                for (int i = 0; i < n - 1; i++)
                {
                    myfile << nam[i] << " \t" << acc_number[i] << " \t" << pass[i] << " \t" << acc_type[i] << "\t" << cont_num[i] << " \t" << initial_bal[i] << endl;
                }
                myfile.close();
                cout << "\nFile updated successfully." << endl;
            }
        }
        else
        {
            cout << "\n\n\t\tInsufficient balance to pay the bill." << endl;
        }
        break;

    case '3':
        system("cls");
        balance = initial_bal[index];

        cout << " Your available balance is \t" << balance << endl;

        cout << "\n\nEnter the amount of your credit card bill: \t\t";
        cin >> amount;

        if (amount < balance)
        {
            cout << "\n\nYour bill has been paid.\n"
                 << endl
                 << endl;
            cout << " \n\t\tNOTE: \t 8% Bank charges are also deducted " << endl
                 << endl;
            balance = (balance - amount) * 0.92; // Deduct 10%
            initial_bal[index] = balance;

            cout << "\nYour updated balance is: \t" << initial_bal[index] << " Rs" << endl
                 << endl;

            ofstream myfile("user-info.txt", ios::out); // Open file in ios::app mode
            if (!myfile)
            {
                cout << "Error opening file." << endl;
            }
            else
            {
                // Write updated customer information to the file
                for (int i = 0; i < n - 1; i++)
                {
                    myfile << nam[i] << " \t" << acc_number[i] << " \t" << pass[i] << " \t" << acc_type[i] << "\t" << cont_num[i] << " \t" << initial_bal[i] << endl;
                }
                myfile.close();
                cout << "\nFile updated successfully." << endl;
            }
        }
        else
        {
            cout << "\n\n\t\tInsufficient balance to pay the bill." << endl;
        }
        break;

    case '4':
        system("cls");
        balance = initial_bal[index];

        cout << " Your available balance is \t" << balance << endl;

        cout << "\n\nEnter the amount of your single Installment(as decided): \t\t";
        cin >> amount;

        if (amount < balance)
        {
            int install;
            cout << " Enter the number of your installments you are willing to pay. \n";
            cout << " On single installment 10 percent tax will be deducted.\n";
            cout << " On two installment 8 percent tax will be deducted.\n";
            cout << " On three installment 6 percent tax will be deducted.\n";

            cin >> install;

            if (install == 1)
            {

                cout << "\n\nYour Installment has been paid.\n"
                     << endl
                     << endl;
                cout << " \n\t\tNOTE: \t 10% Bank charges are also deducted " << endl
                     << endl;
                amount *= install;
                cout << " Total amount of your installments: " << amount << endl;
                balance = (balance - amount) * 0.9; // Deduct 10%
                initial_bal[index] = balance;
            }
            else if (install == 2)
            {
                cout << "\n\nYour bill has been paid.\n"
                     << endl
                     << endl;
                cout << " \n\t\tNOTE: \t 8% Bank charges are also deducted " << endl
                     << endl;
                amount *= install;
                cout << " Total amount of your installments: " << amount << endl;
                balance = (balance - amount) * 0.92; // Deduct 10%
                initial_bal[index] = balance;
            }
            else
            {
                cout << "\n\nYour bill has been paid.\n"
                     << endl
                     << endl;
                cout << " \n\t\tNOTE: \t 6% Bank charges are also deducted " << endl
                     << endl;
                amount *= install;
                cout << " Total amount of your installments: " << amount << endl;
                balance = (balance - amount) * 0.94; // Deduct 10%
                initial_bal[index] = balance;
            }

            cout << "\nYour updated balance is: \t" << initial_bal[index] << " Rs" << endl
                 << endl;

            ofstream myfile("user-info.txt", ios::out); // Open file in ios::app mode
            if (!myfile)
            {
                cout << "Error opening file." << endl;
            }
            else
            {
                // Write updated customer information to the file
                for (int i = 0; i < n - 1; i++)
                {
                    myfile << nam[i] << " \t" << acc_number[i] << " \t" << pass[i] << " \t" << acc_type[i] << "\t" << cont_num[i] << " \t" << initial_bal[i] << endl;
                }
                myfile.close();
                cout << "\nFile updated successfully." << endl;
            }
        }
        else
        {
            cout << "\n\n\t\tInsufficient balance to pay the bill." << endl;
        }
        break;

    case '5':

        system("cls");
        balance = initial_bal[index];

        cout << " Your available balance is \t" << balance << endl;

        cout << "\n\nEnter the amount of your credit card bill: \t\t";
        cin >> amount;

        if (amount < balance)
        {
            cout << "\n\nYour bill has been paid.\n"
                 << endl
                 << endl;
            cout << " \n\t\tNOTE: \t 8% Bank charges are also deducted " << endl
                 << endl;
            balance = (balance - amount) * 0.92; // Deduct 10%
            initial_bal[index] = balance;

            cout << "\nYour updated balance is: \t" << initial_bal[index] << " Rs" << endl
                 << endl;

            ofstream myfile("user-info.txt", ios::out); // Open file in ios::app mode
            if (!myfile)
            {
                cout << "Error opening file." << endl;
            }
            else
            {
                // Write updated customer information to the file
                for (int i = 0; i < n - 1; i++)
                {
                    myfile << nam[i] << " \t" << acc_number[i] << " \t" << pass[i] << " \t" << acc_type[i] << "\t" << cont_num[i] << " \t" << initial_bal[i] << endl;
                }
                myfile.close();
                cout << "\nFile updated successfully." << endl;
            }
        }
        else
        {
            cout << "\n\n\t\tInsufficient balance to pay the bill." << endl;
        }
        break;

    default:

        cout << " Please select the correct option as mentioned above. \n";
    }
    cout << "\n\n\t\tPress any key to continue.......";
    cin.ignore();
    cin.get();

    //  } while (ch != '6');
}

void login ::Tax()
{
    int n = 0;
    int index = -1;

    ifstream ifile("user-info.txt");

    if (!ifile)
    {
        cout << "Error opening file." << endl; // Display error message if file cannot be opened
    }
    else
    {
        // Read customer information from the file
        do
        {
            ifile >> nam[n] >> acc_number[n] >> pass[n] >> acc_type[n] >> cont_num[n] >> initial_bal[n];
            n++;
        } while (!ifile.eof());
    }

    ifile.close(); // Close the file

    // Search for the customer by name
    for (int m = 0; m < n; m++)
    {
        if (acc_num == acc_number[m])
        {
            index = m;
            break;
        }
    }

    char ch;

    cout << "\n\n\nSelect the category of Tax you want to pay: \n";
    cout << "\n\n\t\t\t 1.Income Tax ";
    cout << "\n\n\t\t\t 2.Motor Vehicle Tax ";

    cin >> ch;
    float balance;

    switch (ch)
    {
    case '1':
        float income, tax;
        system("cls");
        balance = initial_bal[index];

        cout << " Your available balance is \t" << balance << endl;

        cout << "\n\nEnter your Total Income per month: \t\t";
        cin >> income;

        if (income > 0 && income < 200000)
        {

            cout << " \n\t\tNOTE: \t 2% Bank charges will also deducted " << endl
                 << endl;

            tax = income * 0.02;
            cout << " 2 percent tax deducted from your income is: \t" << tax << endl;
        }
        else if (income > 200000 && income < 500000)
        {

            cout << " \n\t\tNOTE: \t 3% Bank charges will also deducted " << endl
                 << endl;

            tax = income * 0.03;
            cout << " 3 percent tax deducted from your income is: \t" << tax << endl;
        }
        else if (income > 500000)
        {

            cout << " \n\t\tNOTE: \t 5% Bank charges will also be deducted " << endl
                 << endl;

            tax = income * 0.05;
            cout << " 5 percent tax deducted from your income is: \t" << tax << endl;
        }

        if (tax < balance)
        {

            cout << "\n\nYour Tax has been paid.\n"
                 << endl
                 << endl;
            balance = balance - tax; // Deduct 10%
            initial_bal[index] = balance;

            cout << "\nYour updated balance is: \t" << initial_bal[index] << " Rs" << endl
                 << endl;

            ofstream myfile("user-info.txt", ios::out); // Open file in ios::app mode
            if (!myfile)
            {
                cout << "Error opening file." << endl;
            }
            else
            {
                // Write updated customer information to the file
                for (int i = 0; i < n - 1; i++)
                {
                    myfile << nam[i] << " \t" << acc_number[i] << " \t" << pass[i] << " \t" << acc_type[i] << "\t" << cont_num[i] << " \t" << initial_bal[i] << endl;
                }
                myfile.close();
                // cout << "\nFile updated successfully." << endl;
            }
        }
        else
        {
            cout << "\n\n\t\tInsufficient balance to pay the tax." << endl;
        }

        break;

    case '2':
        system("cls");

        balance = initial_bal[index];

        cout << " Your available balance is \t" << balance << endl;
        char choice;

        cout << " Select the category of your vehicle 'B' for bike or 'C' for car \n";
        cin >> choice;

        switch (choice)
        {
        case 'b':
        case 'B':
            int tax;
            system("cls");
            balance = initial_bal[index];

            cout << " Your available balance is \t" << balance << endl;
            int type;

            cout << "\n\nEnter the engine type of your bike: \t\t";
            cin >> type;

            if (type > 50 && type < 70)
            {

                cout << " \n\t\tNOTE: \t Tax applied on 70CC bike is 1000 " << endl
                     << endl;
                tax = 1000;
            }
            else if (type > 70 && type < 100)
            {

                cout << " \n\t\tNOTE: \t Tax applied on bikes that are above 70CC is 2500 " << endl
                     << endl;
                tax = 2500;
            }
            else if (type > 100 && type < 150)
            {

                cout << " \n\t\tNOTE: \t Tax applied on 70CC bike is 5000 " << endl
                     << endl;
                tax = 5000;
            }

            if (tax < balance)
            {

                cout << "\n\nYour Tax has been paid.\n"
                     << endl
                     << endl;
                balance = balance - tax; // Deduct 10%
                initial_bal[index] = balance;

                cout << "\nYour updated balance is: \t" << initial_bal[index] << " Rs" << endl
                     << endl;

                ofstream myfile("user-info.txt", ios::out); // Open file in ios::app mode
                if (!myfile)
                {
                    cout << "Error opening file." << endl;
                }
                else
                {
                    // Write updated customer information to the file
                    for (int i = 0; i < n - 1; i++)
                    {
                        myfile << nam[i] << " \t" << acc_number[i] << " \t" << pass[i] << " \t" << acc_type[i] << "\t" << cont_num[i] << " \t" << initial_bal[i] << endl;
                    }
                    myfile.close();
                    // cout << "\nFile updated successfully." << endl;
                }
            }
            else
            {
                cout << "\n\n\t\tInsufficient balance to pay the tax." << endl;
            }

            break;

        case 'c':
        case 'C':

            system("cls");
            balance = initial_bal[index];

            cout << " Your available balance is \t" << balance << endl;

            cout << "\n\nEnter the engine type of your car: \t\t";
            cin >> type;

            if (type > 660 && type < 1000)
            {

                cout << " \n\t\tNOTE: \t Tax applied on cars above 660CC and less then 1000CC is 10000 " << endl
                     << endl;
                tax = 10000;
            }
            else if (type > 1000 && type < 1800)
            {

                cout << " \n\t\tNOTE: \t Tax applied on cars above 1000CC and less then 1800CC is 15000 " << endl
                     << endl;
                tax = 15000;
            }
            else if (type > 1800)
            {

                cout << " \n\t\tNOTE: \t Tax applied on cars above 1800CC is 20000 " << endl
                     << endl;
                tax = 20000;
            }

            if (tax < balance)
            {

                cout << "\n\nYour Tax has been paid.\n"
                     << endl
                     << endl;
                balance = balance - tax; // Deduct 10%
                initial_bal[index] = balance;

                cout << "\nYour updated balance is: \t" << initial_bal[index] << " Rs" << endl
                     << endl;

                ofstream myfile("user-info.txt", ios::out); // Open file in ios::app mode
                if (!myfile)
                {
                    cout << "Error opening file." << endl;
                }
                else
                {
                    // Write updated customer information to the file
                    for (int i = 0; i < n - 1; i++)
                    {
                        myfile << nam[i] << " \t" << acc_number[i] << " \t" << pass[i] << " \t" << acc_type[i] << "\t" << cont_num[i] << " \t" << initial_bal[i] << endl;
                    }
                    myfile.close();
                    // cout << "\nFile updated successfully." << endl;
                }
            }
            else
            {
                cout << "\n\n\t\tInsufficient balance to pay the tax." << endl;
            }

            break;

        default:
            cout << " You entered invalid vehicle category.\n";
        }

        /*if (amount < balance)
        {
            cout << "\n\nYour bill has been paid.\n" << endl << endl;
            cout << " \n\t\tNOTE: \t 7% Bank charges are also deducted " <<endl <<endl;
            balance = (balance - amount) * 0.93; // Deduct 10%
            initial_bal[index] = balance;

            cout << "\nYour updated balance is: \t" << initial_bal[index] << " Rs" << endl << endl;

            ofstream myfile("user-info.txt", ios::out); // Open file in ios::app mode
            if (!myfile)
            {
                cout << "Error opening file." << endl;
            }
            else
            {
                // Write updated customer information to the file
                for (int i = 0; i < n-1; i++)
                {
                    myfile << nam[i] << " \t" << acc_number[i] << " \t" << pass[i] << " \t" << acc_type[i] << "\t"<< cont_num[i] << " \t" << initial_bal[i] << endl;
                }
                myfile.close();
                cout << "\nFile updated successfully." << endl;
            }
        }
        else
        {
            cout << "\n\n\t\tInsufficient balance to pay the bill." << endl;
        }
        break;

       /*  case '3':
        system("cls");
        balance =initial_bal[index];

        cout << " Your available balance is \t" << balance << endl;


        cout << "\n\nEnter the amount of your credit card bill: \t\t";
        cin >> amount;


        if (amount < balance)
        {
            cout << "\n\nYour bill has been paid.\n" << endl << endl;
            cout << " \n\t\tNOTE: \t 8% Bank charges are also deducted " <<endl <<endl;
            balance = (balance - amount) * 0.92; // Deduct 10%
            initial_bal[index] = balance;

            cout << "\nYour updated balance is: \t" << initial_bal[index] << " Rs" << endl << endl;

            ofstream myfile("user-info.txt", ios::out); // Open file in ios::app mode
            if (!myfile)
            {
                cout << "Error opening file." << endl;
            }
       q     else
            {
                // Write updated customer information to the file
                for (int i = 0; i < n-1; i++)
                {
                    myfile << nam[i] << " \t" << acc_number[i] << " \t" << pass[i] << " \t" << acc_type[i] << "\t"<< cont_num[i] << " \t" << initial_bal[i] << endl;
                }
                myfile.close();
                cout << "\nFile updated successfully." << endl;
            }
        }
        else
        {
            cout << "\n\n\t\tInsufficient balance to pay the bill." << endl;
        }
        break;
*/
    }
}

void login::Funds()
{
    string nam[100], pass[100], cont_num[100], acc_type[100];
    int acc_number[100];
    float initial_bal[100];

    system("cls");

    int n = 0;
    int sender_index = -1;
    int receiver_index = -1;

    ifstream ifile("user-info.txt");

    if (!ifile)
    {
        cout << "Error opening file." << endl;
        return;
    }
    else
    {
        // Read customer information from the file
        do
        {
            ifile >> nam[n] >> acc_number[n] >> pass[n] >> acc_type[n] >> cont_num[n] >> initial_bal[n];
            n++;
        } while (!ifile.eof());
    }

    ifile.close(); // Close the file

    int sender_accnum, receiver_accnum;
    cout << "Enter your account number: ";
    cin >> sender_accnum;

    for (int m = 0; m < n; m++)
    {
        if (sender_accnum == acc_number[m])
        {
            sender_index = m;
            break;
        }
    }

    if (sender_index == -1)
    {
        cout << "Sender account not found." << endl;
        return;
    }

    cout << "Enter the account number you want to transfer funds to: ";
    cin >> receiver_accnum;

    for (int m = 0; m < n; m++)
    {
        if (receiver_accnum == acc_number[m])
        {
            receiver_index = m;
            break;
        }
    }

    if (receiver_index == -1)
    {
        cout << "Receiver account not found." << endl;
        return;
    }

    float sender_balance = initial_bal[sender_index];
    cout << "Your available balance is " << sender_balance << " Rs" << endl;

    float amount;
    cout << "\nEnter the amount you want to transfer: ";
    cin >> amount;

    if (amount < sender_balance)
    {
        sender_balance -= amount;
        initial_bal[sender_index] = sender_balance;
        initial_bal[receiver_index] += amount;

        cout << "\nYour amount has been transferred." << endl;
        cout << "Your updated balance is: " << sender_balance << " Rs" << endl;

        ofstream myfile("user-info.txt", ios::out);
        if (!myfile)
        {
            cout << "Error opening file." << endl;
            return;
        }
        else
        {
            for (int i = 0; i < n - 1; i++)
            {
                myfile << nam[i] << " " << acc_number[i] << " " << pass[i] << " " << acc_type[i] << " " << cont_num[i] << " " << initial_bal[i] << endl;
            }
            myfile.close();
        }
    }
    else
    {
        cout << "\nInsufficient balance to transfer the amount." << endl;
    }
}

void intro()
{
    // Display the introductory text and wait for user input
    cout << right << setw(50) << "\n\n\n\t\t        ********COMSATS UNIVERSITY ISLAMABAD, LAHORE********** \n";
    cout << right << setw(50) << " \n\n\n\n\n\t\t\t        **********BANK*********** ";
    cout << right << setw(50) << " \n\t\t\t       *********MANAGEMENT*********** ";
    cout << right << setw(50) << " \n\t\t\t        *********SYSTEM********** ";
    cout << " \n\n\n\n\n\t\t Develop by \t\t||||||||| WADI UR REHMAN ||||||||||| \n";
    cout << " \n\t\t Develop by \t\t||||||||| Abdur Rehman Gujjer ||||||||||| \n";
    cout << " \n\t\t Develop by \t\t||||||||| Junaid Zaheer ||||||||||| \n";
    cout << " \n\n\t\t Roll number:\t\t |||||||||||| FA22-BCE-006 ||||||||||\n";
    cout << " \n\n\t\t Roll number:\t\t |||||||||||| FA22-BCE-039 ||||||||||\n";
    cout << " \n\n\t\t Roll number:\t\t |||||||||||| FA22-BCE-045 ||||||||||\n";
    cout << " \n\n\n\n\t\t\t\t\t\t PRESS ENTER TO CONTINUE.";
    cin.get();
}

void manager::mainmenu()
{
    int choice;
    // system("cls");

    do
    {

        system("cls");
        cout << " 1. Display All Accounts \n ";
        cout << "2. Modify An Account \n ";
        cout << "3. Delete an account  \n ";
        cout << "4. Search for account  \n ";
        cout << "5. Exit \n ";

        cout << "Please Enter Your Choice \n ";
        cin >> choice;
        cin.ignore();
        // system("cls");

        switch (choice)
        {
        case 1:
            /*system("pause");
             // Wait for user input before clearing the screen

            */
            system("cls");
            display_data();

            break;
        case 2:
            system("cls");
            modify_data();
            break;
        case 3:
            system("cls");
            delete_account();
            break;
        case 4:
            system("cls");
            search_foracc();
            break;
        case 5:
            system("cls");
            cout << "Exiting Program \n ";
            for (int i = 0; i < 4; i++)
            {
                cout << ".";
                Sleep(1000);
            }
            break;
        default:
            cout << "Enter A valid Option \n ";
            break;
        }
        cout << "Press any key to continue \n ";
        cin.ignore();
        cin.get();
    } while (choice != 5);
}

void manager::search_foracc()
{
    string search_accnum;
    cout << "Enter account number to search: ";
    cin >> search_accnum;

    ifstream myinfile("user-info.txt");
    bool found = false;
    int n = 0;

    if (myinfile.is_open())
    {
        while (myinfile >> user_name[n] >> user_accnum[n] >> user_pin[n] >> acc_type[n] >> phone_no[n] >> initialBalance[n])
        {
            if (search_accnum == user_accnum[n])
            {
                found = true;
                cout << "Account found:" << endl;
                cout << "Name: " << user_name[n] << endl;
                cout << "Account number: " << user_accnum[n] << endl;
                cout << "Account Type: " << acc_type[n] << endl;
                cout << "Initial Balance: " << initialBalance[n] << endl;
                cout << "User Pin: " << user_pin[n] << endl;
                break; // Stop searching after finding the account
            }
        }
    }
    else
    {
        cout << "File not opened." << endl;
    }

    if (!found)
    {
        cout << "Account not found." << endl;
    }

    myinfile.close();
}

void manager::delete_account()
{
    string delete_accnum;
    cout << "Enter account number to delete: ";
    cin >> delete_accnum;

    ifstream inputfile("user-info.txt");
    ofstream temp("temp.txt");

    if (!inputfile || !temp)
    {
        cout << "Error opening file." << endl;
        return;
    }

    int n = 0;
    bool found = false;
    while (inputfile >> user_name[n] >> user_accnum[n] >> user_pin[n] >> acc_type[n] >> phone_no[n] >> initialBalance[n])
    {
        if (delete_accnum == user_accnum[n])
        {
            found = true;
            cout << "Account deleted successfully." << endl;
        }
        else
        {
            temp << user_name[n] << " " << user_accnum[n] << " " << user_pin[n] << " " << acc_type[n] << " " << phone_no[n] << " " << initialBalance[n] << endl;
            n++;
        }
    }

    if (!found)
    {
        cout << "Account not found." << endl;
    }

    inputfile.close();
    temp.close();

    // Remove the original file and rename the temporary file
    remove("user-info.txt");
    rename("temp.txt", "user-info.txt");
}

void manager::display_data()
{
    ifstream myinfile1("user-info.txt");
    int n = 0;

    if (myinfile1.is_open())
    {
        while (myinfile1 >> user_name[n] >> user_accnum[n] >> user_pin[n] >> acc_type[n] >> phone_no[n] >> initialBalance[n])
        {
            cout << "Name: " << user_name[n] << endl;
            cout << "Account number: " << user_accnum[n] << endl;
            cout << "Account Type: " << acc_type[n] << endl;
            cout << "Initial Balance: " << initialBalance[n] << endl;
            cout << "User Pin: " << user_pin[n] << endl;
        }
    }
    else
    {
        cout << "File not opened." << endl;
    }

    myinfile1.close();
}

void manager::modify_data()
{
    int n = 0;
    ifstream inputfile("user-info.txt");
    if (!inputfile)
    {
        cout << "Error opening file." << endl;
        return;
    }
    else
    {
        while (inputfile >> user_name[n] >> user_accnum[n] >> user_pin[n] >> acc_type[n] >> phone_no[n] >> initialBalance[n])
        {
            n++;
        }
        inputfile.close();

        string acc_n;
        int index = -1;

        cout << "Enter account number to be edited: ";
        cin >> acc_n;

        for (int m = 0; m < n; m++)
        {
            if (acc_n == user_accnum[m])
            {
                index = m;
                break;
            }
        }

        if (index != -1)
        {
            cout << "Enter new Account Details :" << endl;
            cout << "Enter new Account type: ";
            cin >> acc_type[index];
            cout << "Enter New Balance: ";
            cin >> initialBalance[index];
            cout << "Enter The New User pin  ";
            cin >> user_pin[index];

            ofstream myoutfile("user-info.txt");
            if (!myoutfile)
            {
                cout << "Error opening file." << endl;
                return;
            }

            int i = 0;
            while (i < n)
            {
                myoutfile << user_name[i] << " " << user_accnum[i] << " " << user_pin[i] << " " << acc_type[i] << " " << phone_no[i] << " " << initialBalance[i] << endl;
                i++;
            }

            myoutfile.close();
            cout << "Data modified successfully." << endl;
        }
        else
        {
            cout << "Account not found." << endl;
        }
    }
}
