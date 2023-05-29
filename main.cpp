#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include "BankHeader.h"

using namespace std;

void theMainMenuScreen();   void TrnsactionScreen();    void ManageUserScreen();

void BalancesScreen()
{
    system("clear");    double BalanceSum = 0.0;

    showRecord = PrintFileContentOnScreen(BankClient);

    BalanceSum = UpdateBalances(showRecord);

    PrintBalancesScreen(showRecord, BalanceSum);



    PrintPressENTER();
    TrnsactionScreen();
}

void WithdrawScreen()
{
    system("clear");
    PrintWithdrawScreen();

    FindRecord = ReadString("\nPlease enter Account Number?  ");
    WithdrawbyAccountNumber(showRecord,FindRecord);

    PrintPressENTER();
    TrnsactionScreen();
}

void DepositsScreen()
{
    system("clear");
    PrintDepositsScreen();

    FindRecord = ReadString("\nPlease enter Account Number?  ");
    DepositbyAccountNumber(showRecord,FindRecord);

    PrintPressENTER();
    TrnsactionScreen();
}

void ShowClientScreen()
{
    system("clear");

    if(!CheckAccessPermissions(enMainMenuPermissions::eShowClient)){

        PrintAccessDeniedScreen();  PrintPressENTER();  theMainMenuScreen();  }

    showRecord = PrintFileContentOnScreen(BankClient);
    PrinMyRecordsData(showRecord);

    PrintPressENTER();
    theMainMenuScreen();
}

void ShowUserScreen()
{
    system("clear");

    showUsers = PrintUserFileContentOnScreen(BankUser);
    PrinMyUsersData(showUsers);

    PressENTERBackUser();
    ManageUserScreen();
}

void AaddClientScreen()
{
    system("clear");

    if(!CheckAccessPermissions(enMainMenuPermissions::eAddClients)){

        PrintAccessDeniedScreen();  PrintPressENTER();  theMainMenuScreen();    return; }

    PrintNewClientScreen();


    do {

        FindRecord = ReadString("\nPlease enter Account Number?  ");

        if(FindRecordbyAccountNumber(cRecord,FindRecord)){

                PrintAccNmbrFound(FindRecord);  }

    }while(FindRecordbyAccountNumber(cRecord,FindRecord));

    toAdd(FindRecord);

    PrintPressENTER();
    theMainMenuScreen();
}

void AaddUserScreen()
{
    system("clear");
    PrintNewUserScreen();

    do {

        FindUser = ReadString("\nPlease enter User Name ? ");

        if(!FindUserbyUserName(FindUser, showUsers ,CurrentUser))
            toAddUser(FindUser);

    }while(addMore());

    PressENTERBackUser();
    ManageUserScreen();
}


void DletClientScreen()
{
    system("clear");

    if(!CheckAccessPermissions(enMainMenuPermissions::eDeletClients)){

        PrintAccessDeniedScreen();      PrintPressENTER();  theMainMenuScreen();    return;  }

    PrintDeleteClientScreen();

    showRecord = PrintFileContentOnScreen(BankClient);
    //PrinMyRecordsData(showRecord);

    FindRecord = ReadString("\nPlease enter Account Number?  ");
    DeleteRecordbyAccountNumber(showRecord,FindRecord);

    PrintPressENTER();
    theMainMenuScreen();
}

void DletUserScreen()
{
    system("clear");
    PrintDeleteUserScreen();


    showUsers = PrintUserFileContentOnScreen(BankUser);
    //PrinMyUsersData(showUsers);

    FindUser = ReadString("\nPlease enter User Name ?  ");
    if(DeleteUserbyUserName(showUsers,FindUser))
    {
        PressENTERBackUser();
        ManageUserScreen();
        theMainMenuScreen();
    }
}

void UpdtClientScreen()
{
    system("clear");

    if(!CheckAccessPermissions(enMainMenuPermissions::eUpdateClients)){

        PrintAccessDeniedScreen();      PrintPressENTER();  theMainMenuScreen();    return;  }

    PrintUpdateClientScreen();

    showRecord = PrintFileContentOnScreen(BankClient);
    //PrinMyRecordsData(showRecord);

    FindRecord = ReadString("\nPlease enter Account Number?  ");
    UpdateRecordbyAccountNumber(showRecord,FindRecord);

    PrintPressENTER();
    theMainMenuScreen();
}

void UpdtUserScreen()
{
    system("clear");
    PrintUpdateUserScreen();

    showUsers = PrintUserFileContentOnScreen(BankUser);
    //PrinMyUsersData(showUsers);

    FindUser = ReadString("\nPlease enter User Name ?  ");
    UpdateUserbyUserName(showUsers, FindUser);


    PressENTERBackUser();
    ManageUserScreen();
    theMainMenuScreen();
}

void FindClientScreen()
{
    system("clear");

    if(!CheckAccessPermissions(enMainMenuPermissions::eFindClients)){

        PrintAccessDeniedScreen();  PrintPressENTER();  theMainMenuScreen();    return;  }

    PrintFindClientScreen();

    showRecord = PrintFileContentOnScreen(BankClient);
    //PrinMyRecordsData(showRecord);

    FindRecord = ReadString("\nPlease enter Account Number?  ");

    if(FindRecordbyAccountNumber(cRecord,FindRecord)){

        cout << endl << endl;
        PrintEachRecrod(cRecord);
        cout << endl << endl;
    }
    else
        PrintNotFound(FindRecord);


    PrintPressENTER();
    theMainMenuScreen();
}

void FindUserScreen()
{
    system("clear");
    PrintFindUserScreen();

    showUsers = PrintUserFileContentOnScreen(BankUser);
    //PrinMyUsersData(showUsers);

    FindUser = ReadString("\nPlease enter User Name ?  ");

    if(FindUserbyUserName(FindUser, showUsers ,CurrentUser)){

        cout << endl << endl;   PrintEachUser(cUser);
        cout << endl << endl;   }

    else {

        PrintUserNotFound(FindUser);  }


    PressENTERBackUser();
    ManageUserScreen();
}

void TrnsactionScreen()
{
    system("clear");

    if(!CheckAccessPermissions(enMainMenuPermissions::eTransactions)){

        PrintAccessDeniedScreen();  PrintPressENTER();  theMainMenuScreen();    return;  }

    unsigned short chose = 0;
    PrintTrnsactionScreen();

    chose = ReadRangedNumber("\t     Chose what do you want to de? [ 1 to 4 ] ? ", 1,4);

    switch (chose){

    case (1): DepositsScreen(); break;
    case (2): WithdrawScreen(); break;
    case (3): BalancesScreen(); break;
    case (4): theMainMenuScreen(); break;
    }
}

void ExitScreen()
{
    system("clear");
    PrintGodBye();
}

void ManageUserScreen()
{

    if(!CheckAccessPermissions(enMainMenuPermissions::eManageUsers)){

        PrintAccessDeniedScreen();  PrintPressENTER();  theMainMenuScreen();    return;  }

    system("clear");    unsigned short chose = 0;

    PrintManageUserScreen();

    chose = ReadRangedNumber("\t     Chose what do you want to de? [ 1 to 6 - or 0 to Exit ] ? ", 0, 6);

    switch (chose){

    case (0): ExitScreen(); break;
    case (1): ShowUserScreen(); break;
    case (2): AaddUserScreen(); break;
    case (3): DletUserScreen(); break;
    case (4): UpdtUserScreen(); break;
    case (5): FindUserScreen(); break;
    case (6): theMainMenuScreen();  break;  }
}

void MainLoginScreen()
{
    system("clear");

    PrintLoginScreen();

    theMainMenuScreen();
}


void theMainMenuScreen()
{
    system("clear"); unsigned short chose = 0;

    PrintMainScreenChoise();

    chose = ReadRangedNumber("\t     Chose what do you want to de? [ 1 to 8 or 0 to Exit ] ? ", 0,8);

    switch (chose){

    case (0): ExitScreen(); break;
    case (1): ShowClientScreen(); break;
    case (2): AaddClientScreen(); break;
    case (3): DletClientScreen(); break;
    case (4): UpdtClientScreen(); break;
    case (5): FindClientScreen(); break;
    case (6): TrnsactionScreen(); break;
    case (7): ManageUserScreen(); break;
    case (8): MainLoginScreen(); break; }

}

int main()
{

    MainLoginScreen();

    return 0;
}
