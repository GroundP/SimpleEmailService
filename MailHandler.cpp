#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "FileSaver.h"
#include "MailHandler.h"

using namespace std;

CMailHandler::CMailHandler()
{
    std::map<std::string, std::vector<Mail>> savedList;
    if ( CFileSaver::readMailList(savedList) )
        mailList = savedList;
}

CMailHandler::~CMailHandler()
{
}

bool CMailHandler::run(const set<string>& accounts)
{
    while ( true )
    {
        system("cls");
        cout << "<< HOME(" << curAccount << ") >>" << endl;
        const enMailChoice& category = chooseMailFunc();
        switch ( category )
        {
        case enMailChoice::enShow:
            showProcess();
            break;
        case enMailChoice::enSend:
            sendMailProcess(accounts);
            break;
        case enMailChoice::enLogout:
            return true;
        case enMailChoice::enExit:
            cout << "[Execute] The program will be exited."<< endl;
            Sleep(500);
            exit(0);
        default:
            break;
        }
    }
    
}

enMailChoice CMailHandler::chooseMailFunc()
{
    while ( true )
    {
        cout << (int)enMailChoice::enShow   << ". Show Mail List" << endl;
        cout << (int)enMailChoice::enSend   << ". Send Mail" << endl;
        cout << (int)enMailChoice::enLogout << ". Logout" << endl;
        cout << (int)enMailChoice::enExit   << ". Exit" << endl;

        cout << endl << "[Input] ";
        int input;
        cin >> input;

        if ( input < 1 || input > 5 )
        {
            cout << "wrong input" << endl;
            Sleep(1000);
            if ( cin.fail() )
            {
                cin.clear();
                cin.ignore(1024, '\n');
            }
            return static_cast<enMailChoice>(0);
        }
        

        return static_cast<enMailChoice>(input);
    }
}

void CMailHandler::showProcess()
{
    cout << "<< MAIL LIST >>" << endl;
       
    if ( mailList[curAccount].empty() )
    {
        cout << "There's no mail(" << curAccount << ")" << endl;
        Sleep(1000);
        return;
    }

    for ( const auto& a : mailList[curAccount] )
    {
        cout << "-------------------" << endl;
        cout << "Id: " << a.id << endl;
        cout << "From: " << a.from << endl;
        cout << "To: " << a.to << endl;
        cout << "Title: " << a.title << endl;
        cout << "Contents: " << a.contents << endl;
        cout << "Attached: " << (a.attached ? "y" : "n") << endl;
    }

    cout << endl << "Press any key...";

    while ( true )
    {
        if ( _kbhit() )
            return;
    }
}

void CMailHandler::sendMailProcess(const set<string>& accounts)
{
    while ( true )
    {
        system("cls");
        cout << "<< SEND MAIL >>" << endl;
        cout << "To: ";
        string to;
        cin >> to;

        cout << "Title: ";
        string title;
        cin >> title;

        cout << "Contents: ";
        string contents;
        cin >> contents;

        cout << "Attached?(y/n)";
        string attached;
        cin >> attached;

        if ( accounts.count(to) == 0 )
        {
            cout << endl << "[Error] Email address(" << to <<") is not registered. Check again" << endl;
            cout << "Retry?(y/n) ";
            string tmp;
            cin >> tmp;
            if ( tmp == "y" )
                continue;
            else
                return;
        }

        if ( mailList.count(to) == 0 )
        {
            vector<Mail> v;
            mailList.insert(make_pair(to, v));
        }

        mailList[to].push_back(Mail(getMaxId()+1, curAccount, to, title, contents, attached == "y" ? true : false));

        cout << endl<< "[Execute] Success to send mail!" << endl;
        CFileSaver::saveMailList(mailList);
        Sleep(1000);
        return;
    }
    
}

unsigned int CMailHandler::getMaxId()
{
    unsigned int maxId = 0;
    for ( const auto& a : mailList )
    {
        for ( const auto& b : a.second )
        {
            if ( b.id > maxId )
                maxId = b.id;            
        }
    }
    return maxId;
}