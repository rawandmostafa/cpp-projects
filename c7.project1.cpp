
#include <iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
using namespace std;
const string bankFileName = "client.txt";
void printAll();
void ShowTransactionsMenue();
struct stclient {
    string acountNumber;
    string pincode;
    string name;
    string phone;
    double balance;
    bool MarkForDelete = false;
};
stclient read() {
    stclient client;
    cout << "enter acountNumber?\n";
    getline(cin >> ws, client.acountNumber);
    cout << "enter pincode?\n";
    getline(cin, client.pincode);
    cout << "enter name?\n";
    getline(cin, client.name);
    cout << "enter phone?\n";
    getline(cin, client.phone);
    cout << "enter balalnce?\n";
    cin >> client.balance;
    return client;
}
string convertToline(stclient client, string seperat = "#//#") {
    string sbank = "";
    sbank += client.acountNumber + seperat;
    sbank += client.pincode + seperat;
    sbank += client.name + seperat;
    sbank += client.phone + seperat;
    sbank += to_string(client.balance);
    return sbank;
}
vector<string>splite(string s, string delim) {
    vector<string>vstring;
    int count = 0;
    int pos = 0;
    string sword;
    while ((pos = s.find(delim)) != std::string::npos) {
        sword = s.substr(0, pos);
        if (sword != "") {
            vstring.push_back(sword);

        }
        s.erase(0, pos + delim.length());
    }
    if (s != " ") {
        vstring.push_back(s);
    }
    return vstring;
}
string acountread() {
    string acount;
    cout << "enter acount?\n";
    cin >> acount;
    return acount;
}
void write(string fileName, string stdata) {
    fstream myFile; myFile.open(fileName, ios::out | ios::app);
    if (myFile.is_open()) {
        myFile << stdata << endl;
    }
    myFile.close();
}
void addDatabank() {



    stclient client;
    client = read();


    write(bankFileName, convertToline(client));

}
void addNewClient() {
    char add = 'y';
    do {

        system("cls");

        addDatabank();
        cout << "\nClient Added Successfully, do you want to addmore clients ? Y / N ? ";
        cin >> add;

    } while (add == 'y');
}
stclient convert2(string line, string seperat = "#//#") {
    stclient client;
    vector<string>vstring;
    vstring = splite(line, seperat);
    client.acountNumber = vstring[0];
    client.pincode = vstring[1];
    client.name = vstring[2];
    client.phone = vstring[3];
    client.balance = stod(vstring[4]);
    return client;

}
vector<stclient>load(string fileName) {
    vector<stclient>vstring;
    fstream myFile;
    myFile.open(fileName, ios::in);

    if (myFile.is_open()) {
        string line;
        stclient client;
        while (getline(myFile, line)) {
            client = convert2(line);
            vstring.push_back(client);
        }

        myFile.close();
    }
    return vstring;
}
void PrintClientRecord(stclient client)
{
    
    cout << "| " << setw(15) << left << client.acountNumber;
    cout << "| " << setw(10) << left << client.pincode;
    cout << "| " << setw(40) << left << client.name;
    cout << "| " << setw(12) << left << client.phone;
    cout << "| " << setw(12) << left << client.balance;
}
void PrintAllClientsData()
{
    vector<stclient>vstring = load(bankFileName);
    cout << "\n\t\t\t\t\tdata List (" << vstring.size() << ").";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
    for (stclient client : vstring)
    {
        PrintClientRecord(client);
        cout << endl;
    }
    cout <<
        "\n_______________________________________________________";
    cout << "_________________________________________\n" << endl;
}

int readnum() {
    int x;
    cout << "choose what do you want to do?[1to7]?\n";
    cin >> x;
    return x;
}

bool FindClientByAccountNumber(string AccountNumber, vector <stclient> vstring, stclient &client)
{
    for (stclient c : vstring)
    {
        if (c.acountNumber == AccountNumber)
        {
            client = c;
            return true;
        }
    }
    return false;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector <stclient>& vstring)
{
    for (stclient& c : vstring)
    {
        if (c.acountNumber== AccountNumber)
        {
            c.MarkForDelete = true;
            return true;
        }
    }
    return false;
}
stclient ChangeClientRecord(string AccountNumber)
{
    stclient client;
    client.acountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, client.pincode);
    cout << "Enter Name? ";
    getline(cin, client.name);
    cout << "Enter Phone? ";
    getline(cin, client.phone);
    cout << "Enter AccountBalance? ";
    cin >> client.balance;
    return client;
}
vector <stclient> SaveCleintsDataToFile(string fileName, vector<stclient> vstring)
{
    fstream myFile;
    myFile.open(fileName, ios::out);
    string DataLine;
    if (myFile.is_open())
    {
        for (stclient c : vstring)
        {
            if (c.MarkForDelete == false)
            {

                DataLine = convertToline(c);
                myFile << DataLine << endl;
            }
        }
        myFile.close();
    }
    return vstring;
}

void PrintClientCard(stclient client) 
    {
        cout << "\nThe following are the client details:\n";
        cout << "-----------------------------------";
        cout << "\nAccout Number: " << client.acountNumber;
        cout << "\nPin Code : " << client.pincode;
        cout << "\nName : " << client.name;
        cout << "\nPhone : " << client.phone;
        cout << "\nAccount Balance: " << client.balance;
        cout << "\n-----------------------------------\n";
    }

    
    bool DeleteClientByAccountNumber(string AccountNumber, vector <stclient>&vstring) {
    
        stclient client;
        char Answer = 'n';
        if (FindClientByAccountNumber(AccountNumber, vstring,client))
        {
            PrintClientCard(client);
            cout << "\n\nAre you sure you want delete this client? y/n? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                MarkClientForDeleteByAccountNumber(AccountNumber, vstring);
                SaveCleintsDataToFile(bankFileName, vstring);

                vstring = load(bankFileName);
                cout << "\n\nClient Deleted Successfully.";
                return true;
            }
        }
        else
        {
            cout << "\nClient with Account Number (" << AccountNumber<< ") is Not Found!";
            return false;
        }
    }

    bool UpdateClientByAccountNumber(string AccountNumber, vector <stclient>& vstring)
    {
        stclient client;
        char Answer = 'n';
        if (FindClientByAccountNumber(AccountNumber, vstring,client))
        {
            PrintClientCard(client);
            cout << "\n\nAre you sure you want update this client? y/n? ";
                cin >> Answer;
            if (Answer == 'y' || Answer == 'Y')
            {
                for (stclient& c : vstring)
                {
                    if (c.acountNumber == AccountNumber)
                    {
                        c = ChangeClientRecord(AccountNumber);
                        break;
                    }
                }
                SaveCleintsDataToFile(bankFileName, vstring);
                cout << "\n\nClient Updated Successfully.";
                return true;
            }
        }
        else
        {
            cout << "\nClient with Account Number (" << AccountNumber
                << ") is Not Found!";
            return false;
        }
    }
    void ShowAddNewClientsScreen()
    {
        cout << "\n-----------------------------------\n";
        cout << "\tAdd New Clients Screen";
        cout << "\n-----------------------------------\n";
        addNewClient();
    }
    bool DepositBalanceToClientByAccountNumber(string AccountNumber,double Amount, vector <stclient>& vstring)
    {
        char Answer = 'n';
        cout << "\n\nAre you sure you want perfrom this transaction? y / n ? ";
            cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (stclient& C : vstring)
            {
                if (C.acountNumber == AccountNumber)
                {
                    C.balance += Amount;
                    SaveCleintsDataToFile(bankFileName, vstring);
                    cout << "\n\nDone Successfully. New balance is: " << C.balance;
                    return true;
                }
            }
            return false;
        }
    }

    string ReadClientAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }
    void showDelete() {
        cout << "\n-----------------------------------\n";
        cout << "\tDelete Client Screen";
        cout << "\n-----------------------------------\n";
        vector<stclient>vstring = load(bankFileName);
        string AccountNumber = ReadClientAccountNumber();
        DeleteClientByAccountNumber(AccountNumber, vstring);
    }

    void showupdate() {
        cout << "\n-----------------------------------\n";
        cout << "\tUpdate Client Info Screen";
        cout << "\n-----------------------------------\n";
        vector<stclient>vstring = load(bankFileName);
        string AccountNumber = ReadClientAccountNumber();
        UpdateClientByAccountNumber(AccountNumber, vstring);
    }
    void showFind() {
        cout << "\n-----------------------------------\n";
        cout << "\tFind Client Screen";
        cout << "\n-----------------------------------\n";
        vector<stclient>vstring = load(bankFileName);
        stclient client;
        string AccountNumber = ReadClientAccountNumber();
        if (FindClientByAccountNumber(AccountNumber, vstring, client)) {
            PrintClientCard(client);
        }
        else {
            cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
        }
    }
    void ShowEndScreen()
    {
        cout << "\n-----------------------------------\n";
        cout << "\tProgram Ends :-)";
        cout << "\n-----------------------------------\n";
    }
   
   
    enum enMainMenueOptions
    {
        eListClients = 1, eAddNewClient = 2,
        eDeleteClient = 3, eUpdateClient = 4,
        eFindClient = 5,transaction=6, eExit = 7
    };
    void GoBackToMainMenue()
    {
        cout << "\n\nPress any key to go back to Main Menue...";
        system("pause>0");
        printAll();

    }
    int readTransaction() {
        int num;
        cout << "Choose what do you want to do? [1 to 4]? \n";
        cin >> num;
        return num;
    }
    void GoBackToTransactionsMenue()
    {
        cout << "\n\nPress any key to go back to Transactions Menue...";
        system("pause>0");
        ShowTransactionsMenue();
    }
    void ShowDepositScreen()
    {
        cout << "\n-----------------------------------\n";
        cout << "\tDeposit Screen";
        cout << "\n-----------------------------------\n";
        vector<stclient>vstring = load(bankFileName);
        stclient client;
        string AccountNumber = ReadClientAccountNumber();
        while (!FindClientByAccountNumber(AccountNumber, vstring, client)) {
            cout << "\nClient with [" << AccountNumber << "] does notexist.\n";
            AccountNumber = ReadClientAccountNumber();

        }
       
        PrintClientCard(client);
        double Amount = 0;
        cout << "\nPlease enter deposit amount? ";
        cin >> Amount;
        DepositBalanceToClientByAccountNumber(AccountNumber, Amount,  vstring);


    }
    void ShowWithDrawScreen()
    {
        cout << "\n-----------------------------------\n";
        cout << "\tWithdraw Screen";
        cout << "\n-----------------------------------\n";
        vector<stclient>vstring = load(bankFileName);
        stclient client;
        string AccountNumber = ReadClientAccountNumber();
        while (!FindClientByAccountNumber(AccountNumber, vstring, client)) {
            cout << "\nClient with [" << AccountNumber << "] does notexist.\n";
            AccountNumber = ReadClientAccountNumber();

        }

        PrintClientCard(client);
        double Amount = 0;
        cout << "\nPlease enter deposit amount? ";
        cin >> Amount;
        while (Amount > client.balance) {
            cout << "\nAmount Exceeds the balance, you can withdraw up to : " << client.balance << endl;
                cout << "Please enter another amount? ";
            cin >> Amount;
        }
        DepositBalanceToClientByAccountNumber(AccountNumber, Amount * -1, vstring);
    }
    void PrintClientRecordBalanceLine(stclient Client)
    {
        cout << "| " << setw(15) << left << Client.acountNumber;
        cout << "| " << setw(40) << left << Client.name;
        cout << "| " << setw(12) << left << Client.balance;
    }
    void ShowTotalBalances()
    {
        vector<stclient>vstring = load(bankFileName);
        cout << "\n\t\t\t\t\tBalances List (" << vstring.size() << ") Client(s).";
            cout <<
            "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "Accout Number";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Balance";
        cout <<
            "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;

        double TotalBalances = 0;
        if (vstring.size() == 0)
            cout << "\t\t\t\tNo Clients Available In the System!";
        else
            for (stclient Client : vstring)
            {
                PrintClientRecordBalanceLine(Client);
                TotalBalances += Client.balance;
                cout << endl;
            }
        cout <<
            "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "\t\t\t\t\t Total Balances = " << TotalBalances;
    }

    
    void ShowTotalBalancesScreen()
    {
        ShowTotalBalances();
    }
    enum enTransactionsMenueOptions {
        eDeposit = 1, eWithdraw = 2,
        eShowTotalBalance = 3, eShowMainMenue = 4
    };
    void performanceTransaction(enTransactionsMenueOptions transaction) {
        switch (transaction) {
        case enTransactionsMenueOptions::eDeposit:
            system("cls");
            ShowDepositScreen();
            GoBackToTransactionsMenue();
            break;
        case enTransactionsMenueOptions::eWithdraw:
            system("cls");
            ShowWithDrawScreen();
            GoBackToTransactionsMenue();
            break;
        case enTransactionsMenueOptions::eShowTotalBalance:
            system("cls");
            ShowTotalBalancesScreen();
            GoBackToTransactionsMenue();
            break;
        case enTransactionsMenueOptions::eShowMainMenue:
        
            printAll();
        

        }
    }
    void ShowTransactionsMenue()
    {
        system("cls");
        cout << "===========================================\n";
        cout << "\t\tTransactions Menue Screen\n";
        cout << "===========================================\n";
        cout << "\t[1] Deposit.\n";
        cout << "\t[2] Withdraw.\n";
        cout << "\t[3] Total Balances.\n";
        cout << "\t[4] Main Menue.\n";
        cout << "===========================================\n";
        performanceTransaction((enTransactionsMenueOptions)readTransaction());

    }
    void performance(enMainMenueOptions option) {
        switch (option) {
        case enMainMenueOptions::eListClients:
            system("cls");
            PrintAllClientsData();
            GoBackToMainMenue();
            break;
        case enMainMenueOptions::eAddNewClient:
            system("cls");
            ShowAddNewClientsScreen();
            GoBackToMainMenue();
            break;
            
        case enMainMenueOptions::eDeleteClient:
            system("cls");
            showDelete();
            GoBackToMainMenue();
            break;
            case enMainMenueOptions::eUpdateClient:
                system("cls");
                showupdate();
                GoBackToMainMenue();
                break;

            case enMainMenueOptions::eFindClient:
                system("cls");
                showFind();
                GoBackToMainMenue();
                break;
            case enMainMenueOptions::transaction:
                system("cls"); 
                ShowTransactionsMenue();
                GoBackToMainMenue();
                break;
            case enMainMenueOptions::eExit:
                system("cls");
                ShowEndScreen();
                GoBackToMainMenue();
                break;



        }
    }
   
    
    void printAll() {

        cout << "=============================================\n";
        cout << "          main menue screen                  \n";
        cout << "=============================================\n";
        cout << "[1]show client list\n";
        cout << "[2]add new client\n";
        cout << "[3]delet client\n";
        cout << "[4]update client info\n";
        cout << "[5]find client\n";
        cout << "[6]transaction\n";
        cout << "[7]exist\n";
        performance((enMainMenueOptions)readnum());
        
    }
int main()
{
    printAll();
}
