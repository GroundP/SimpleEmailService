#include "AccountHandler.h"
#include "MailHandler.h"
#include "MainController.h"
#include <iostream>
#include <Windows.h>

using namespace std;

void CMainController::run()
{
    CAccountHandler accountHandler;
    CMailHandler mailHandler;
    while ( true )
    {
        system( "cls" );
        enMainChoice choise = chooseMain();

        bool bExit = false;
        switch ( choise )
        {
        case enMainChoice::enSignUp:
            accountHandler.processSignUp();
            break;
        case enMainChoice::enSignIn:
        {
            pair<string, string> info;
            if ( accountHandler.processSignIn(info) )
            {
                mailHandler.setAccount(info.first);
                mailHandler.run(accountHandler.getAllId());
            }
        }
        break;
        case enMainChoice::enExit:
            cout << "[Execute] The program will be exited."<< endl;
            Sleep(1000);
            bExit = true;
            break;
        default:
            cout << "[Error] Wrong input."<< endl;
            Sleep(500);
            break;
        }

        if ( bExit )
            break;
    }
}

enMainChoice CMainController::chooseMain()
{
    cout << "<< EMAIL SERVEICE >>" << endl;
    cout << "1. SIGN UP" << endl;
    cout << "2. SIGN IN" << endl;
    cout << "3. EXIT" << endl;

    cout << "\n[Input] ";

    int input;
    cin >> input;

    return static_cast<enMainChoice>(input);
}
