#ifndef BANKHEADER_H_INCLUDED
#define BANKHEADER_H_INCLUDED


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

const string BankClient = "myCBank.txt";    const string BankUser = "myUser.txt";

fstream myFile; string FindRecord;  string AccntNmbr;   string FindUser;

struct stRecord{

    string AccuntNmbr;  string ClientName;
    string AccPinCode;  string ClientPhon;
    double AccBalance;  bool MarkForDelete =false;
};  stRecord cRecord;   vector<stRecord>showRecord;

struct stUser{

    string UsertName;
    string PassWords;
    int Permision;  bool MarkForDelete =false;
};  stUser cUser;   vector<stUser>showUsers;    stUser CurrentUser;

enum enMainMenuPermissions {

    eAll=-1, eShowClient=1, eAddClients=2, eDeletClients=4, eUpdateClients=8,
    eFindClients=16, eTransactions=32, eManageUsers=64  };

int ReadPermissionsToSet()
{
    int permissions=0;  char Answer='n';

    cout << "\nWould You like to give Full Access ? y/n "; cin>>Answer;

    if(tolower(Answer)=='y'){

        return -1;  }

    cout << "\nWould You like to give Access For : \n";

    cout << "\nShow Clients List ? y/n.. "; cin>>Answer;

    if(tolower(Answer)=='y'){

        permissions+=enMainMenuPermissions::eShowClient;    }

    cout << "\nAdd New Clients ? y/n.. "; cin>>Answer;

    if(tolower(Answer)=='y'){

        permissions+=enMainMenuPermissions::eAddClients;    }

    cout << "\nDelete Clients ? y/n.. "; cin>>Answer;

    if(tolower(Answer)=='y'){

        permissions+=enMainMenuPermissions::eDeletClients;    }

    cout << "\nUpdate Clients ? y/n.. "; cin>>Answer;

    if(tolower(Answer)=='y'){

        permissions+=enMainMenuPermissions::eUpdateClients;    }

    cout << "\nFind Clients ? y/n.. "; cin>>Answer;

    if(tolower(Answer)=='y'){

        permissions+=enMainMenuPermissions::eFindClients;    }

    cout << "\nTransactions ? y/n.. "; cin>>Answer;

    if(tolower(Answer)=='y'){

        permissions+=enMainMenuPermissions::eTransactions;    }

    cout << "\nManage Users ? y/n.. "; cin>>Answer;

    if(tolower(Answer)=='y'){

        permissions+=enMainMenuPermissions::eManageUsers;    }

    return permissions;
}

bool CheckAccessPermissions(int Permission)
{
    if(CurrentUser.Permision == enMainMenuPermissions::eAll){

        return true;    }

    if((Permission & CurrentUser.Permision) == Permission){

        return true;    }

    return false;
}

bool addMore()
{
    char add='n';

    cout << "\nDone Successfuly, Do it more ? y/n "; cin>>add;

    return (tolower(add)=='y')? true : false;
}

vector <string> SplitString(string TheString, string delim)
{

    vector <string> vString;  size_t pos = 0;    string sWord;

    while((pos=TheString.find(delim))!=std::string::npos)
    {
        ///Create First and followed Word
        sWord=TheString.substr(0,pos);

        if(sWord != "")
        {
            vString.push_back(sWord);
        }

        TheString.erase(0, pos+delim.length());
    }

    /// Create Last Word
    if(TheString != "")
        vString.push_back(TheString);

    return vString;
}

string RecordPrnting(stRecord Record, string Seprator = "#//#")
{
    string rString = "";

    rString += Record.AccuntNmbr + Seprator;
    rString += Record.AccPinCode + Seprator;
    rString += Record.ClientName + Seprator;
    rString += Record.ClientPhon + Seprator;
    rString += to_string(Record.AccBalance);

    return rString;
}

string UserPrnting(stUser Record, string Seprator = "#//#")
{
    string rString = "";

    rString += Record.UsertName + Seprator;
    rString += Record.PassWords + Seprator;
    rString += to_string(Record.Permision) + Seprator;

    return rString;
}

string RecordToLine(stRecord Record, string Seprator = "#//#")
{
    string rString = "";

    rString += Record.AccuntNmbr + Seprator;
    rString += Record.AccPinCode + Seprator;
    rString += Record.ClientName + Seprator;
    rString += Record.ClientPhon + Seprator;
    rString += to_string(Record.AccBalance);

    return rString;
}

string UserToLine(stUser User, string Seprator = "#//#")
{
    string rString = "";

    rString += User.UsertName + Seprator;
    rString += User.PassWords + Seprator;
    rString += to_string(User.Permision) + Seprator;

    return rString;
}

stRecord LineToRecordPrinting(string Line, string Seprator = "#//#")
{
    stRecord Record; vector<string>vRecord;

    vRecord = SplitString(Line, Seprator);

    Record.AccuntNmbr = vRecord[0];
    Record.AccPinCode = vRecord[1];
    Record.ClientName = vRecord[2];
    Record.ClientPhon = vRecord[3];
    Record.AccBalance = stod(vRecord[4]);

    return Record;
}

stUser LineToUserPrinting(string Line, string Seprator = "#//#")
{
    stUser user; vector<string>vUserdata;

    vUserdata = SplitString(Line, Seprator);

    user.UsertName = vUserdata[0];
    user.PassWords = vUserdata[1];
    user.Permision = stoi(vUserdata[2]);

    return user;
}


void SaveRecordToFile(string FileName, string sRecord)
{
    myFile.open(FileName, ios::out | ios::app);

    if(myFile.is_open())
    {
        myFile << sRecord << endl; myFile.close();
    }
}

void SaveUserToFile(string FileName, string sUser)
{
    myFile.open(FileName, ios::out | ios::app);

    if(myFile.is_open())
    {
        myFile << sUser << endl; myFile.close();
    }
}


vector<stRecord> SaveRecordToFile(string FileName, vector <stRecord> vRecord)
{
    myFile.open(FileName, ios::out);

    string DataLine;

    if(myFile.is_open())
    {
        for (stRecord rec : vRecord)
        {
            if(rec.MarkForDelete == false)
            {
                DataLine = RecordPrnting(rec);

                myFile << DataLine << endl;
            }
        }
        myFile.close();
    }
    return vRecord;
}

vector<stUser> SaveUserToFile(string FileName, vector <stUser> vUser)
{
    myFile.open(FileName, ios::out);

    string DataLine;

    if(myFile.is_open())
    {
        for (stUser rec : vUser)
        {
            if(rec.MarkForDelete == false)
            {
                DataLine = UserPrnting(rec);

                myFile << DataLine << endl;
            }
        }
        myFile.close();
    }
    return vUser;
}


string ReadString(string Message)
{
    string aString;
    cout << Message ; cin >> aString;
    return aString;
}

short ReadRangedNumber(string message, short From, short To)
{
    short Nmbr;

    do{

        cout << message ; cin >> Nmbr;

    }while (Nmbr < From || Nmbr > To);

    return Nmbr;
}

stRecord RecordReading(string AccntNmbr)
{
    stRecord Record;

    cout << "\nNew Client of Account No. : " << AccntNmbr << endl;
    /// Using getlin cin >> ws = white space
    Record.AccuntNmbr = AccntNmbr;
    ///cout << "\nAccount Number  : " ; getline(cin>>ws, Record.AccuntNmbr);
    cout << "\nAccount PinCode : " ; getline(cin>>ws, Record.AccPinCode);
    cout << "\nClient Full Name: " ; getline(cin, Record.ClientName);
    cout << "\nClient Phone No.: " ; getline(cin, Record.ClientPhon);
    cout << "\nAccount Balance : " ; cin >> Record.AccBalance;

    return Record;
}

stUser UserReading(string UserName)
{
    stUser user;

    cout << "\nNew info of User No. : " << UserName << endl;
    /// Using getlin cin >> ws = white space
    user.UsertName = UserName;
    cout << "\nUser Password   : " ; getline(cin>>ws, user.PassWords);
    cout << "\nUser Permission : " ; user.Permision = ReadPermissionsToSet();
    return user;
}

void Pr2ntEachRecrod(stRecord Rec)
{
    cout << "AccountNo.       : "  << setw(20) << left << Rec.AccuntNmbr << endl;
    cout << "Pin Code         : "  << setw(15) << left << Rec.AccPinCode << endl;
    cout << "Client Full Name : "  << setw(60) << left << Rec.ClientName << endl;
    cout << "Client Phone     : "  << setw(15) << left << Rec.ClientPhon << endl;
    cout << "Accout Balance   : "  << setw(15) << left << Rec.AccBalance << endl;

}

void Pr2ntEachUser(stUser Rec)
{
    cout << "\tUser-Name        : "  << setw(30) << left << Rec.UsertName << endl;
    cout << "\tPass-Word        : "  << setw(30) << left << Rec.PassWords << endl;
    cout << "\tPermissions      : "  << setw(30) << left << Rec.Permision << endl;

}


stRecord UpdateOneRecrod(string rAccountNmbr)
{
    stRecord Record;
    Record.AccuntNmbr = rAccountNmbr;

    cout << "\nUpdate Records No. " << rAccountNmbr << endl;
    cout << "\nUpdate Account PinCode : " ; getline(cin>>ws, Record.AccPinCode);
    cout << "\nUpdate Client Full Name: " ; getline(cin, Record.ClientName);
    cout << "\nUpdate Client Phone No.: " ; getline(cin, Record.ClientPhon);
    cout << "\nUpdate Account Balance : " ; cin >> Record.AccBalance;

    return Record;
}

stUser UpdateOneUser(string rUserName)
{
    stUser Record;  Record.UsertName = rUserName;

    cout << "\nUpdate User Name " << rUserName << endl;
    cout << "\nUpdate User Pass Word  : " ; getline(cin>>ws, Record.PassWords);
    cout << "\nUpdate User Permission : \n" ; Record.Permision = ReadPermissionsToSet();

    return Record;
}


bool WithdrawFromRecrod(string rAccountNmbr, vector<stRecord> &vRecord)
{
    double NewWithdraw = 0.0; char usure = 'n';

    cout << "\nUpdate Account Balance : " ; cin >> NewWithdraw;

    for(stRecord & recrd : vRecord)
    {
        if(recrd.AccuntNmbr == rAccountNmbr)
        {
            if(recrd.AccBalance < NewWithdraw)
            {
                cout << "\n\nYour Balance is not allowed !!";
                cout << " your allowed up to = " << recrd.AccBalance << endl;
                return false;
            }
            else
            {
                cout << "\n\nAre You Sure ? y/n "; cin>>usure;

                if(tolower(usure)=='y')
                {
                    recrd.AccBalance += NewWithdraw * -1;    return true;
                }
                return false;
            }

        }
    }
    return false;
}

bool DepositIntoRecrod(string rAccountNmbr, vector<stRecord> &vRecord)
{

    double NewDeposit = 0.0;

    cout << "\nUpdate Account Balance : " ; cin >> NewDeposit;

    for(stRecord & recrd : vRecord)
    {
        if(recrd.AccuntNmbr == rAccountNmbr)
        {
            recrd.AccBalance += NewDeposit;
            return true;

        }
    }
    return false;

}

vector <stRecord> PrintFileContentOnScreen(string FileName)
{
    vector <stRecord> vRecord;

    ///To read file content we use ios::int
    myFile.open(FileName, ios::in);

    if(myFile.is_open())
    {
        string line ; stRecord Record;

        while(getline(myFile, line))
        {
            Record = LineToRecordPrinting(line);
            vRecord.push_back(Record);
        }

        myFile.close();
    }
    return vRecord;
}

vector<stUser> PrintUserFileContentOnScreen(string FileName)
{
    vector<stUser> vUser;   fstream myFile;

    myFile.open(FileName, ios::in);

    if(myFile.is_open())
    {
        string line;   stUser user;

        while(getline(myFile, line))
        {
            user = LineToUserPrinting(line);

            vUser.push_back(user);
        }

        myFile.close();
    }
    return vUser;
}

vector <stRecord> Pr2ntFileContentToFile(string FileName)
{
    vector <stRecord> vRecord;

    ///To write on file content we use ios::int
    myFile.open(FileName, ios::in);

    if(myFile.is_open())
    {
        string line ; stRecord Record;

        while(getline(myFile, line))
        {
            Record = LineToRecordPrinting(line);
            vRecord.push_back(Record);
        }

        myFile.close();
    }
    return vRecord;
}

vector <stUser> Pr2ntUserFileContentToFile(string FileName)
{
    vector <stUser> vRecord;

    ///To write on file content we use ios::int
    myFile.open(FileName, ios::in);

    if(myFile.is_open())
    {
        string line ; stUser Record;

        while(getline(myFile, line))
        {
            Record = LineToUserPrinting(line);
            vRecord.push_back(Record);
        }

        myFile.close();
    }
    return vRecord;
}


bool CheckAccountNumber(stRecord &fRecord, string rAccountNmbr)
{
    showRecord = PrintFileContentOnScreen(BankClient);

    for(stRecord rec : showRecord)
    {
        if(rec.AccuntNmbr == rAccountNmbr)
        {
            cout << "Account Number is exist" << endl;
            return true;
        }
    }
    return false;
}

bool FindRecordbyAccountNumber(vector<stRecord> vRecord, stRecord &sRecord, string rAccNmbr)
{

    for(stRecord rec : vRecord)
    {
        if(rec.AccuntNmbr == rAccNmbr)
        {
            sRecord = rec;  return true;
        }
    }
    return false;
}

bool FindRecordbyAccountNumber(stRecord &fRecord, string rAccountNmbr)
{
    showRecord = PrintFileContentOnScreen(BankClient);

    for(stRecord rec : showRecord)
    {
        if(rec.AccuntNmbr == rAccountNmbr){

            fRecord = rec;  return true;    }
    }
    return false;
}

bool FindUserbyUserNameAndPassword(string UserName, string Password, stUser &User)
{

    showUsers=PrintUserFileContentOnScreen(BankUser);

    for(stUser use : showUsers)
    {
        if(use.UsertName==UserName && use.PassWords==Password){

            User=use;    return true; }
    }

    return false;
}

bool FindUserbyUserName(string UserName, vector<stUser>vUsers, stUser &User)
{

    for(stUser use : vUsers)
    {
        if(use.UsertName==UserName){

            User = use;    return true; }
    }

    return false;
}

void PrintNewClientScreen()
{
    cout << "\n\n--------------------------------------------------\n";
    cout << "\n\n\t\tAdd New Clients Screen\n\n\n";
    cout << "--------------------------------------------------\n\n";
    cout << " Adding New Client : \n" << endl;
}

void PrintNewUserScreen()
{
    cout << "\n\n--------------------------------------------------\n";
    cout << "\n\n\t\tAdd New Users Screen\n\n\n";
    cout << "--------------------------------------------------\n\n";
    cout << " Adding New User : \n" << endl;
}

void AddNewRecord(string AccntNmbr)
{

    stRecord record;    system("clear");   PrintNewClientScreen();

    record =  RecordReading(AccntNmbr);

    SaveRecordToFile(BankClient,RecordToLine(record));
}

void AddNewUser(string UserName)
{

    stUser users;    system("clear");   PrintNewUserScreen();

    users =  UserReading(UserName);

    SaveUserToFile(BankUser,UserToLine(users));
}

void PrintNotFound(string FRecord)
{
    cout << "\nRecord with Account Number (" << FRecord << ") Not Found \n" << endl;
}

bool MarkRecordForDeleteByAccountNmbr(string rAccountNmbr, vector<stRecord> &vRecord)
{
    for(stRecord & recrd : vRecord)
    {
        if(recrd.AccuntNmbr == rAccountNmbr)
        {
            recrd.MarkForDelete = true;
            return true;

        }
    }
    return false;
}

bool MarkUserForDeleteByUserName(string rUserName, vector<stUser> &vUser)
{
    for(stUser & recrd : vUser)
    {
        if(recrd.UsertName == rUserName)
        {
            recrd.MarkForDelete = true;
            return true;

        }
    }
    return false;
}

bool DeleteRecordbyAccountNumber(vector<stRecord> &vRecord, string rAccountNmbr)
{
    stRecord cRecord; char Answer = 'n';

    if(FindRecordbyAccountNumber(vRecord,cRecord,rAccountNmbr))
    {
        cout << endl;

        Pr2ntEachRecrod(cRecord); cout << endl ;

        cout << "\n\nYou Are About Delete ! R U Sure? y/n "; cin >> Answer;

        if(tolower(Answer) == 'y')
        {
            MarkRecordForDeleteByAccountNmbr(rAccountNmbr, vRecord);

            SaveRecordToFile(BankClient,vRecord);

            ///refresh Records
            vRecord = Pr2ntFileContentToFile(BankClient);

            cout << "\n\nRecord Deleted Successfully. " << endl << endl ;

            return true;
        }
    }

    PrintNotFound(rAccountNmbr);    return false;
}

void PrintUserNotFound(string FUser);


bool DeleteUserbyUserName(vector<stUser> &vUser, string rUserName)
{
    stUser cUser; char Answer = 'n';

    if(FindUserbyUserName(rUserName, showUsers ,CurrentUser))
    {

        if(rUserName == "Admin"){

            cout << "\nIt's Not allowed to delete the Admin \n\n" << endl;  return false;   }

        Pr2ntEachUser(cUser); cout << endl ;


        cout << "\n\nYou Are About Delete ! R U Sure? y/n "; cin >> Answer;

        if(tolower(Answer) == 'y')
        {
            MarkUserForDeleteByUserName(rUserName, vUser);

            SaveUserToFile(BankUser,vUser);

            ///refresh Records
            vUser = Pr2ntUserFileContentToFile(BankUser);

            cout << "\n\nUser Deleted Successfully. " << endl << endl ;
        }   return true;
    }

    PrintUserNotFound(rUserName);   return false;
}

bool WithdrawbyAccountNumber(vector<stRecord> &vRecord, string rAccountNmbr)
{
            stRecord cRecord; char Answer = 'n';

    if(FindRecordbyAccountNumber(showRecord,cRecord,rAccountNmbr))
    {
        cout << endl;

        Pr2ntEachRecrod(cRecord); cout << endl ;

        cout << "\n\nYou Are About Update this Record ! R U Sure? y/n "; cin >> Answer;

        if(tolower(Answer) == 'y')
        {

            if(WithdrawFromRecrod(rAccountNmbr, vRecord))
            {

                SaveRecordToFile(BankClient,vRecord);

                ///refresh Records
                vRecord = Pr2ntFileContentToFile(BankClient);

                cout << "\n\nWithdrawal done Successfully. " << endl << endl ;

                return true;
            }
            else
            {
                cout << "\n\nWithdrawal Failed . \n\n"; return false;
            }
        }
    }

    PrintNotFound(rAccountNmbr);

    return false;
}

bool DepositbyAccountNumber(vector<stRecord> &vRecord, string rAccountNmbr)
{
        stRecord cRecord; char Answer = 'n';

    if(FindRecordbyAccountNumber(showRecord,cRecord,rAccountNmbr))
    {
        cout << endl;

        Pr2ntEachRecrod(cRecord); cout << endl ;

        cout << "\n\nYou Are About Update this Record ! R U Sure? y/n "; cin >> Answer;

        if(tolower(Answer) == 'y')
        {

            DepositIntoRecrod(rAccountNmbr, vRecord);

            SaveRecordToFile(BankClient,vRecord);

            ///refresh Records
            vRecord = Pr2ntFileContentToFile(BankClient);

            cout << "\n\nDeposit Added Successfully. " << endl << endl ;

            return true;
        }
    }
    PrintNotFound(rAccountNmbr);

    return false;
}

double UpdateBalances(vector<stRecord> &vRecord)
{
    stRecord cRecord; double BalanceSum = 0.0;

    for(stRecord &recc : vRecord)
    {
        BalanceSum += recc.AccBalance;
    }
    return BalanceSum;
}

bool UpdateRecordbyAccountNumber(vector<stRecord> &vRecord, string rAccountNmbr)
{

    stRecord cRecord; char Answer = 'n';

    if(FindRecordbyAccountNumber(showRecord,cRecord,rAccountNmbr))
    {
        cout << endl;


        Pr2ntEachRecrod(cRecord); cout << endl ;

        cout << "\n\nYou Are About Update this Record ! R U Sure? y/n "; cin >> Answer;

        if(tolower(Answer) == 'y')
        {

            for(stRecord &recc : vRecord)
            {
                if(recc.AccuntNmbr == rAccountNmbr)
                {
                    recc = UpdateOneRecrod(rAccountNmbr); break;
                }
            }
            SaveRecordToFile(BankClient,vRecord);

           cout << "\n\nRecord Update Successfully. " << endl << endl ;

            return true;
        }
    }

    PrintNotFound(rAccountNmbr);

    return false;
}

void UpdateUserbyUserName(vector<stUser> &vUser, string rUserName)
{
    stUser cUser; char Answer = 'n';

    if(FindUserbyUserName(rUserName, showUsers ,CurrentUser))
    {
        cout << endl;

        if(rUserName =="Admin"){

        cout << "\n\tIt's Not Allowed To Update the Admin \n\n" << endl; return;    }

        Pr2ntEachUser(cUser); cout << endl ;

        cout << "\n\nYou Are About Update this User ! R U Sure? y/n "; cin >> Answer;

        if(tolower(Answer) == 'y')
        {

            for(stUser &recc : vUser)
            {
                if(recc.UsertName == rUserName)
                {
                    recc = UpdateOneUser(rUserName); break;
                }
            }
            SaveUserToFile(BankUser,vUser);

           cout << "\n\nUser Update Successfully. " << endl << endl ;
        }   return;
    }
    PrintUserNotFound(rUserName);
}


void PrintBalanceRecrod(stRecord Rec)
{
    cout << "\t| " << setw(20) << left << Rec.AccuntNmbr;
    cout << "| " << setw(60) << left << Rec.ClientName;
    cout << "| " << setw(15) << left << Rec.AccBalance << "|";

}

void PrintFindClientScreen()
{
    cout << "\n\n----------------------------------------\n";
    cout << "\t\tFind Clients Screen\n";
    cout << "----------------------------------------\n\n";
    cout << " Find Client : \n" << endl;
}

void PrintFindUserScreen()
{
    cout << "\n\n----------------------------------------\n";
    cout << "\t\tFind Users Screen\n";
    cout << "----------------------------------------\n\n";
    cout << " Find User : \n" << endl;
}

void PrintTrnsactionScreen()
{
    cout << "\n\n--------------------------------------------------------------------------------\n\n";
    cout << "\t\tTransactions Screen\n\n";
    cout << "--------------------------------------------------------------------------------\n\n";
    cout << " Transactions : \n" << endl;
    cout << "\t[1]  Deposits   . \n\n";
    cout << "\t[2]  Withdrawal . \n\n";
    cout << "\t[3]  Balances   . \n\n";
    cout << "\t[4]  Main Menue . \n\n";
    cout << "--------------------------------------------------------------------------------\n\n";

}

void PrintManageUserScreen()
{
    cout << "\n\n--------------------------------------------------------------------------------\n\n";
    cout << "\t\tManager Users Screen\n\n";
    cout << "--------------------------------------------------------------------------------\n\n";
    cout << " Manager Users : \n\n" << endl;
    cout << "\t [1]  Users List  . \n\n";
    cout << "\t [2]  Add    User . \n\n";
    cout << "\t [3]  Delete User . \n\n";
    cout << "\t [4]  Update User . \n\n";
    cout << "\t [5]  Find   User . \n\n";
    cout << "\t [6]  Main Screen . \n\n";
    cout << "\t [0]  to Exit-----.\n\n";
    cout << "--------------------------------------------------------------------------------\n\n";

}

void PrintUpdateClientScreen()
{
    cout << "\n\n----------------------------------------\n";
    cout << "\t\tUpdate Clients Screen\n";
    cout << "----------------------------------------\n\n";
    cout << " Updating Client : \n" << endl;
}

void PrintUpdateUserScreen()
{
    cout << "\n\n----------------------------------------\n";
    cout << "\t\tUpdate Users Screen\n";
    cout << "----------------------------------------\n\n";
    cout << " Updating User : \n" << endl;

}

void PrintDeleteClientScreen()
{
    cout << "\n\n----------------------------------------\n";
    cout << "\t\tDelete Clients Screen\n";
    cout << "----------------------------------------\n\n";
    cout << " Delete Client : \n" << endl;
}

void PrintDeleteUserScreen()
{
    cout << "\n\n----------------------------------------\n";
    cout << "\t\tDelete Users Screen\n";
    cout << "----------------------------------------\n\n";
    cout << " Deleting User : \n" << endl;
}

void PrintDepositsScreen()
{
    cout << "\n\n----------------------------------------\n";
    cout << "\t\tDeposits Screen\n";
    cout << "----------------------------------------\n\n";
    cout << " New Deposit : \n" << endl;
}

void PrintWithdrawScreen()
{
    cout << "\n\n----------------------------------------\n";
    cout << "\tWithdrawal Screen\n";
    cout << "----------------------------------------\n\n";
    cout << " New Withdrawal : \n" << endl;
}

void PrintBalancesScreen(vector<stRecord>myRecord, double BalanceSum )
{
    cout << "\n--------------------------------------------------\n\n";
    cout << "\tBalances Screen\n\n";
    cout << "--------------------------------------------------\n\n\n";

    cout << "\n\tBalancese Of ( " << myRecord.size() << " ) Record(s) " << setw(60) << endl;

    cout << "\t| --------------------| ------------------------------------------------------------| ---------------|" << endl;
    cout << "\t|                     |                                                             |                |" << endl;

    cout << "\t| " << left << setw(20) << "AccountNo.";
    cout << "| " << left << setw(60) << "Client Full Name";
    cout << "| " << left << setw(15) << "Balance " << "|" << endl;

    cout << "\t|                     |                                                             |                |" << endl;
    cout << "\t| --------------------| ------------------------------------------------------------| ---------------|" << endl;
    cout << "\t|                     |                                                             |                |" << endl;

    for(stRecord rec : myRecord)
    {
        PrintBalanceRecrod(rec);

        cout << endl;
    }
    cout << "\t|                     |                                                             |                |" << endl;
    cout << "\t| --------------------| ------------------------------------------------------------| ---------------|" << endl;

    cout << "\tTotal Balancese = [ " << BalanceSum << " ] " << endl;
    cout << endl << endl << endl;
}

void PrintGodBye()
{
    cout << "\n\n--------------------------------------------------------------------------------\n";
    cout << "\n\n\t\t\tExit my C Bank :)  \n\n\t\t\tPress ENTER key to Exit" << endl;
    cout << "\n\n--------------------------------------------------------------------------------\n";

    cin.ignore(); cin.get();
}

bool LoadUserInfo(string Username, string Password)
{
    return(FindUserbyUserNameAndPassword(Username, Password, CurrentUser))? true : false;
}

void PrintLoginScreen()
{
    string userName="", passWord="";  bool LoginFaild=false;

    do {
        system("clear");
        cout << "======================================================================================================================================================\n\n";
        cout << "\n\t\t\t\t\t\t\t      Welcome To my C Bank  \n\n";
        cout << "\t\t\t\t\t\t\t    ***   Login Screen   ***  \n\n\n";
        cout << "======================================================================================================================================================\n\n";

        if(LoginFaild){

            cout << "\t Invalid User Name / Pass Word ... ";    }

        cout << "\tPlease enter your login informations : \n\n";
        cout << "\tUser Name : ";   cin>>userName;
        cout << "\tPass Word : ";   cin>>passWord;

        LoginFaild = !LoadUserInfo(userName, passWord);

    } while (LoginFaild);
}

void PrintAccessDeniedScreen()
{
    system("clear");
    cout << "\n\n--------------------------------------------------------------------------------\n";
    cout << "\n\n\tYour Access Denied, \nPlease Contact Admin for Access Rights!! " << endl;
    cout << "\n\n--------------------------------------------------------------------------------\n";
    cin.ignore(); cin.get();
}

void PrintMainScreenChoise()
{
    cout << endl;
    cout << "======================================================================================================================================================\n\n";
    cout << "\t\t\t\t\t\t\t    ***   Main Menu Screen   ***  \n\n";
    cout << "======================================================================================================================================================\n\n";
    cout << "\n\t [1]  Show   Client List. \n\n";
    cout << "\t [2]  New    Client Add . \n\n";
    cout << "\t [3]  Delete Client. \n\n";
    cout << "\t [4]  Update Client. \n\n";
    cout << "\t [5]  Find   Client. \n\n";
    cout << "\t [6]  Transactions . \n\n";
    cout << "\t [7]  Manage Users . \n\n";
    cout << "\t [8]  Logout .       \n\n";
    cout << "\t [0]  to Exit-------.\n\n";
    cout << "======================================================================================================================================================\n\n";
}

void PrintPressENTER()
{
    cout << "\n\nPress ENTER Key to back the Main Screen " << endl;
    cin.ignore(); cin.get();

}

void PressENTERBackUser()
{
    cout << "\n\nPress ENTER Key to back Manager User Screen " << endl;
    cin.ignore(); cin.get();

}


void PrintEachRecrod(stRecord Rec)
{
    cout << "| " << setw(20) << left << Rec.AccuntNmbr;
    cout << "| " << setw(15) << left << Rec.AccPinCode;
    cout << "| " << setw(60) << left << Rec.ClientName;
    cout << "| " << setw(15) << left << Rec.ClientPhon;
    cout << "| " << setw(15) << left << Rec.AccBalance << "|";

}

void PrintEachUser(stUser Rec)
{
    cout << "| " << setw(30) << left << Rec.UsertName;
    cout << "| " << setw(30) << left << Rec.PassWords;
    cout << "| " << setw(30) << left << Rec.Permision;
    cout << "| " ;
}


void PrinMyRecordsData(vector<stRecord> myRecord)
{
    if(myRecord.size()==0){

        cout << "\n\n\n\t\tNo Data To Show \n\n\n\t\tAdd new client first\n\n\n";   }

    else{


        cout << "\n\n\n\t\t\t\t\t\t\tRecord List ( " << myRecord.size() << " ) Record(s) " << setw(60) << endl << endl << endl;
        cout << "| --------------------| ---------------| ------------------------------------------------------------| ---------------| ---------------|" << endl;
        cout << "|                     |                |                                                             |                |                |" << endl;

        cout << "| " << left << setw(20) << "AccountNo.";
        cout << "| " << left << setw(15) << "Pin Code";
        cout << "| " << left << setw(60) << "Client Full Name";
        cout << "| " << left << setw(15) << "Client Phone";
        cout << "| " << left << setw(15) << "Balance " << "|" << endl;

        cout << "|                     |                |                                                             |                |                |" << endl;
        cout << "| --------------------| ---------------| ------------------------------------------------------------| ---------------| ---------------|" << endl;
        cout << "|                     |                |                                                             |                |                |" << endl;

        for(stRecord rec : myRecord)
        {
            PrintEachRecrod(rec);

            cout << endl;
        }
        cout << "|                     |                |                                                             |                |                |" << endl;
        cout << "| --------------------| ---------------| ------------------------------------------------------------|----------------| ---------------|" << endl;
        cout << "\n\n\n" << endl;
    }
}

void PrinMyUsersData(vector<stUser> myRecord)
{

    cout << "\n\n\n\t\t\t\t      User List ( " << myRecord.size() << " ) User(s) " << setw(60) << endl << endl << endl;
    cout << "| ------------------------------| ------------------------------| ------------------------------|" << endl;
    cout << "|                               |                               |                               |" << endl;

    cout << "| " << left << setw(25) << "\tUser-Name  ";
    cout << "| " << left << setw(25) << "\tPass-Word  ";
    cout << "| " << left << setw(30) << "\tPermissions             |";
    cout << "\n|                               |                               |                               |" << endl;
    cout << "| ------------------------------| ------------------------------| ------------------------------|" << endl;
    cout << "|                               |                               |                               |" << endl;

        for(stUser use : myRecord)
        {
            PrintEachUser(use);

            cout << endl;
        }
    cout << "|                               |                               |                               |" << endl;
    cout << "| ------------------------------| ------------------------------| ------------------------------|" << endl;
    cout << "\n\n\n" << endl;
}


void PrintUserNotFound(string FUser)
{
    cout << "\nUser with User Name (" << FUser << ") Not Found \n" << endl;
}

void PrintUserFound(string FUser)
{
    cout << "\nUser with User Name (" << FUser << ") is Found \n" << endl;
}

void PrintAccNmbrFound(string FRecord)
{
    cout << "\nRecord with Account Number (" << FRecord << ") is Exist \n" << endl;
}


void toAdd(string AccntNmbr)
{
    char addMore = 'y';

    do    {

        AddNewRecord(AccntNmbr);

        cout << endl << "Record Added, Wanna Add more ? "; cin >> addMore;

        if(tolower(addMore)!='y') break;

        do {

            FindRecord = ReadString("\nPlease enter Account Number?  ");

            if(!FindRecordbyAccountNumber(cRecord,FindRecord))
            {
                AddNewRecord(FindRecord);

            }
            else
            {
                PrintAccNmbrFound(FindRecord); break;
            }
            cout << endl << "Record Added, Wanna Add more ? "; cin >> addMore;

            if(tolower(addMore)!='y') break;

        }while(!FindRecordbyAccountNumber(cRecord,FindRecord) || tolower(addMore)=='y' );

        break;

    }while (tolower(addMore)=='y');
}

void toAddUser(string UserName)
{
    //char addMore='y';



        AddNewUser(UserName);

    /**    toAddAgain:

        if(addMore()==false)
            break;

        FindUser = ReadString("\nPlease enter new User Name ?  ");

        if(!FindUserbyUserName(FindUser, showUsers ,CurrentUser)){

            AddNewUser(FindUser);

            goto toAddAgain; } else {

            PrintUserFound(FindUser);   return; }

    }while(addMore());*/

}


#endif // BANKHEADER_H_INCLUDED
