

#include <iostream>
#include<string>
#include<vector>
#include<iomanip>
#include<fstream>
using namespace std;
const string bankFileName = "client.txt";
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
stclient CurrentClient;
void ShowQuickWithdrawScreen();
void ShowMainMenue();
void ShowNormalWithDrawScreen();
void Login();


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

bool FindClientByAccountNumber(string AccountNumber, vector <stclient> vstring, stclient& client)
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
        if (c.acountNumber == AccountNumber)
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


bool DeleteClientByAccountNumber(string AccountNumber, vector <stclient>& vstring) {

    stclient client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vstring, client))
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
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        return false;
    }
}

bool UpdateClientByAccountNumber(string AccountNumber, vector <stclient>& vstring)
{
    stclient client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vstring, client))
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
bool DepositBalanceToClientByAccountNumber(string AccountNumber, double Amount, vector <stclient>& vstring)
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
enum enMainMenueOptions {
    eQucikWithdraw = 1, eNormalWithDraw = 2, eDeposit = 3,
    eCheckBalance = 4, eExit = 5
};
void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}
double ReadDepositAmount()
{
    double Amount;
    cout << "\nEnter a positive Deposit Amount? ";
    cin >> Amount;
    while (Amount <= 0)
    {
        cout << "\nEnter a positive Deposit Amount? ";
        cin >> Amount;
    }
    return Amount;
}
void PerfromDepositOption()
{
    double DepositAmount = ReadDepositAmount();
    vector <stclient> vClients =
        load(bankFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.acountNumber,
        DepositAmount, vClients);
    CurrentClient.balance += DepositAmount;
}
void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";
    PerfromDepositOption();



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
bool FindClientByAccountNumberAndPinCode(string AccountNumber, string PinCode, stclient& Client)
{
    vector <stclient> vClients = load(bankFileName);
    for (stclient C : vClients)
    {
        if (C.acountNumber == AccountNumber && C.pincode ==
            PinCode)
        {
            Client = C;
            return true;
        }
    }
    return false;
}
bool LoadClientInfo(string AccountNumber, string PinCode)
{
    if (FindClientByAccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
        return true;
    else
        return false;
}
short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;
    return Choice;
}
short ReadQuickWithdrawOption()
{
    short Choice = 0;
    while (Choice < 1 || Choice>9)
    {
        cout << "\nChoose what to do from [1] to [9] ? ";
        cin >> Choice;
    }
    return Choice;
}
short getQuickWithDrawAmount(short QuickWithDrawOption)
{
    switch (QuickWithDrawOption)
    {
    case 1:
        return 20;
    case 2:
        return 50;
    case 3:
        return 100;
    case 4:
        return 200;
    case 5:
        return 400;
    case 6:
        return 600;
    case 7:
        return 800;
    case 8:
        return 1000;
    default:
        return 0;
    }
}
void PerfromQuickWithdrawOption(short QuickWithDrawOption)
{
    if (QuickWithDrawOption == 9)//exit
        return;
    short WithDrawBalance =
        getQuickWithDrawAmount(QuickWithDrawOption);
    if (WithDrawBalance > CurrentClient.balance)
    {
        cout << "\nThe amount exceeds your balance, make another choice.\n";
        cout << "Press Anykey to continue...";
        system("pause>0");
        ShowQuickWithdrawScreen();
        return;
    }
    vector <stclient> vClients =
        load(bankFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.acountNumber, WithDrawBalance * -1, vClients);
    CurrentClient.balance -= WithDrawBalance;
}
void ShowCheckBalanceScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tCheck Balance Screen\n";
    cout << "===========================================\n";
    cout << "Your Balance is " << CurrentClient.balance <<
        "\n";
}
void ShowQuickWithdrawScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tQucik Withdraw\n";
    cout << "===========================================\n";
    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "===========================================\n";
    cout << "Your Balance is " << CurrentClient.balance;
    PerfromQuickWithdrawOption(ReadQuickWithdrawOption());
}
int ReadWithDrawAmont()
{
    int Amount;
    cout << "\nEnter an amount multiple of 5's ? ";
    cin >> Amount;
    while (Amount % 5 != 0)
    {
        cout << "\nEnter an amount multiple of 5's ? ";
        cin >> Amount;
    }
    return Amount;
}
void PerfromNormalWithdrawOption()
{
    int WithDrawBalance = ReadWithDrawAmont();
    if (WithDrawBalance > CurrentClient.balance)
    {
        cout << "\nThe amount exceeds your balance, make another choice.\n";
            cout << "Press Anykey to continue...";
        system("pause>0");
        ShowNormalWithDrawScreen();
        return;
    }
    vector <stclient> vClients =
        load(bankFileName);
    DepositBalanceToClientByAccountNumber(CurrentClient.acountNumber,
        WithDrawBalance * -1, vClients);
    CurrentClient.balance -= WithDrawBalance;
}
void ShowNormalWithDrawScreen()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tNormal Withdraw Screen\n";
    cout << "===========================================\n";
    PerfromNormalWithdrawOption();
}
void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption) {
    case enMainMenueOptions::eQucikWithdraw:
        system("cls");
        ShowQuickWithdrawScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eNormalWithDraw:
        system("cls");
        ShowNormalWithDrawScreen();
        GoBackToMainMenue();
        break;

    case enMainMenueOptions::eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eCheckBalance:
        system("cls");
        ShowCheckBalanceScreen();
        GoBackToMainMenue();
        break;
    case enMainMenueOptions::eExit:
   
        system("cls");
        Login();
        break;
        
    }
}
void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tATM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}
void Login() {
    bool LoginFaild = false;
    string AccountNumber, PinCode;
    do
    {
        system("cls");
        cout << "\n---------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n---------------------------------\n";
        if (LoginFaild)
        {
            cout << "Invlaid Account Number/PinCode!\n";
        }
        cout << "Enter Account Number? ";
        cin >> AccountNumber;
        cout << "Enter Pin? ";
        cin >> PinCode;
        LoginFaild = !LoadClientInfo(AccountNumber, PinCode);
    } while (LoginFaild);
    ShowMainMenue();
}
int main()
{
    
    Login();
}
