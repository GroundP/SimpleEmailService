#include <iostream>
#include "MailHandler.h"

using namespace std;

CMailHandler::CMailHandler()
{
}

CMailHandler::~CMailHandler()
{
}

bool CMailHandler::run(const set<string>& accounts)
{
    while ( true )
    {
        system("cls");
        cout << "<< " << curAccount << " >>" << endl;
        const enMailChoice& category = chooseMailFunc();
        switch ( category )
        {
        case enMailChoice::enShow:
            showProcess();
            break;
        case enMailChoice::enSend:
            sendMailProcess();
            break;
        case enMailChoice::enLogout:
        case enMailChoice::enExit:
            return true;
        default:
            break;
        }
    }
    
}

enMailChoice CMailHandler::chooseMailFunc()
{
    while ( true )
    {
        cout << (int)enMailChoice::enShow << ". Show Mail List" << endl;
        cout << (int)enMailChoice::enSend << ". Send Mail" << endl;
        cout << (int)enMailChoice::enLogout << ". Logout" << endl;
        cout << (int)enMailChoice::enExit << ". Exit" << endl;

        int input;
        cin >> input;

        if ( input < 1 || input > 5 )
        {
            cout << "wrong input" << endl;
            continue;
        }

        return static_cast<enMailChoice>(input);
    }
}

void CMailHandler::showProcess()
{
    cout << "Show mail list!" << endl;
       
    if ( mailList[curAccount].empty() )
        cout << "There's no mail(" << curAccount << ")" << endl;

    for ( const auto& a : mailList[curAccount] )
    {
        cout << "Id: " << a.id << endl;
        cout << "From: " << a.from << endl;
        cout << "To: " << a.to << endl;
        cout << "Title: " << a.title << endl;
        cout << "Contents: " << a.contents << endl;
        cout << "Attached: " << (a.attached ? "y" : "n") << endl;
    }
}

void CMailHandler::sendMailProcess()
{
    cout << "send mail!" << endl;
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

    if ( mailList.count(to) == 0 )
    {
        vector<Mail> v;
        mailList.insert(make_pair(to, v));
    }

    mailList[to].push_back(Mail(0, curAccount, to, title, contents, attached == "y" ? true : false));
}