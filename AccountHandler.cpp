#include <iostream>
#include <Windows.h>
#include <conio.h>
#include "FileSaver.h"
#include "AccountHandler.h"

using namespace std;

CAccountHandler::CAccountHandler()
{
    map<string,string> data;
    if ( CFileSaver::readAccounts(data) )
        accounts = data;
}
CAccountHandler::~CAccountHandler()
{

}

bool CAccountHandler::processSignUp()
{
    while ( true )
    {
        system( "cls" );
        cout << "<< SIGN UP >>" << endl;
        pair<string, string> info;
        if ( !chooseAuthInfo(info) )
        {
            cout << "[Error] wrong input!" << endl;
            continue;
        }

        if (validateSignup(info))
            return true;
        else
        {
            cout << "Retry?(y/n) ";
            string tmp;
            cin >> tmp;
            if ( tmp != "y" )
                return false;
        }
    }
    
}

bool CAccountHandler::processSignIn(pair<string, string>& info)
{
    while ( true )
    {
        system( "cls" );
        cout << "<< SIGN IN >>" << endl;
        if ( !chooseAuthInfo(info) )
        {
            cout << "[Error] wrong input!" << endl;
            Sleep(1000);
            continue;
        }

        if (validateSignin(info))
            return true;
        else
        {
            cout << "Retry?(y/n) ";
            string tmp;
            cin >> tmp;
            if ( tmp != "y" )
                return false;
        }
    }
}

set<string> CAccountHandler::getAllId()
{
    set<string> tmp;
    for ( const auto& a : accounts )
        tmp.insert(a.first);

    return tmp;
}

void CAccountHandler::showAccounts()
{
    int idx = 1;
    for ( const auto& a : getAllId() )
    {
        cout << idx << ") " << a << endl;
        idx++;
    }

    cout << endl << "press any key...";
    while ( true )
    {
        if ( _kbhit() )
            return;
    }
}

bool CAccountHandler::chooseAuthInfo(pair<string, string>& info)
{
    cout << "ID: ";
    string id;
    cin >> id;

    cout << "PW: ";
    string pw;
    cin >> pw;
    cout << endl;

    if ( id.empty() || pw.empty() )
        return false;

    info.first = id;
    info.second = pw;
    return true;
}

//CAccountHandler::enSignupRes CAccountHandler::validateSignup(pair<string, string>& info)
//{
//    if ( accounts.count(info.first) > 0 )
//    {
//        return enExistID;
//    }
//
//    for ( const auto& s : info.first )
//    {
//        if ( s < 33 || (s > 58 && s < 65) || (s > 90 && s < 97) || s > 122 ) 
//            return enWrongInput;
//    }
//
//    for ( const auto& s : info.second )
//    {
//        if ( s < 33 || (s > 58 && s < 65) || (s > 90 && s < 97) || s > 122 ) 
//            return enWrongInput;
//    }
//
//    return enSuccess_up;
//}
//

bool CAccountHandler::validateSignup(const std::pair<std::string, std::string>& info)
{
    if ( accounts.count(info.first) > 0 )
    {
        cout << "[Error] This id(" << info.first << ") is already exist!"<< endl;
        return false;
    }

    for ( const auto& s : info.first )
    {
        if ( s < 33 || (s > 58 && s < 65) || (s > 90 && s < 97) || s > 122 ) 
        {
            cout << "[Error] Both Id and password allow only characters(special) and numbers." << endl;
            return false;
        }
    }

    for ( const auto& s : info.second )
    {
        if ( s < 33 || (s > 58 && s < 65) || (s > 90 && s < 97) || s > 122 ) 
        {
            cout << "[Error] Both Id and password allow only characters(special) and numbers." << endl;
            return false;
        }
    }

    accounts.insert(info);
    CFileSaver::saveAccounts(accounts);
    cout << "[Execute] Success to sign up! (" << info.first << ")"<< endl;
    Sleep(1000);

    return true;
}

bool CAccountHandler::validateSignin(const pair<string, string>& info)
{
    const auto& itr = accounts.find(info.first);
    if ( itr == accounts.end() )
    {
        cout << "[Error] Invalid Account(" << info.first << ")" << endl;
        return false;
    }
    
    if ( itr->second != info.second )
    {
        cout << "[Error] Check Password!" << endl;
        return false;
    }

    cout << "[Execute] Success to logon!"<< endl;
    Sleep(500);
    return true;
}

