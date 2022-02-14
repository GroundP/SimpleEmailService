#include <iostream>
#include <Windows.h>
#include "AccountHandler.h"

using namespace std;
bool CAccountHandler::processSignUp()
{
    system( "cls" );
    cout << "<< SIGN UP >>" << endl;
    pair<string, string> info;
    if ( !chooseAuthInfo(info) )
    {
        cout << "[Error] wrong input!" << endl;
        return false;
    }

    const auto& res = validateSingup(info);
    if ( res == enExistID )
    {
        cout << "[Error] This id(" << info.first << ") is already exist!"<< endl;
        Sleep(2000);
        return false;
    }

    if ( res == enWrongInput )
    {
        cout << "[Error] Both Id and password allow only characters(special) and numbers." << endl;
        Sleep(2000);
        return false;
    }

    if ( res == enSuccess_up )
    {
        accounts.insert(info);
        cout << "[Execute] Success to sign up! (" << info.first << ")"<< endl;
        Sleep(2000);
    }
    

    return true;
}

bool CAccountHandler::processSignIn(pair<string, string>& info)
{
    system( "cls" );
    cout << "<< SIGN IN >>" << endl;
    if ( !chooseAuthInfo(info) )
    {
        cout << "[Error] wrong input!" << endl;
        return false;
    }

    const auto& res = validateSingin(info);
    if ( res == enNoID )
    {
        cout << "[Error] This id(" << info.first << ") is not exist!" << endl;
        Sleep(2000);
        return false;
    }

    if ( res == enWrongPW )
    {
        cout << "[Error] Check Password!" << endl;
        Sleep(2000);
        return false;
    }

    cout << "[Execute] Success to logon!"<< endl;
    Sleep(2000);
    return true;
}

set<string> CAccountHandler::getAllId()
{
    set<string> tmp;
    for ( const auto& a : accounts )
        tmp.insert(a.first);

    return tmp;
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

CAccountHandler::enSignupRes CAccountHandler::validateSingup(pair<string, string>& info)
{
    if ( accounts.count(info.first) > 0 )
    {
        cout << "[Error] This id(" << info.first << ") is already exist!"<< endl;
        return enExistID;
    }

    for ( const auto& s : info.first )
    {
        if ( s < 33 || (s > 58 && s < 65) || (s > 90 && s < 97) || s > 122 ) 
            return enWrongInput;
    }

    for ( const auto& s : info.second )
    {
        if ( s < 33 || (s > 58 && s < 65) || (s > 90 && s < 97) || s > 122 ) 
            return enWrongInput;
    }

    return enSuccess_up;
}

CAccountHandler::enSigninRes CAccountHandler::validateSingin(pair<string, string>& info)
{
    const auto& itr = accounts.find(info.first);
    if ( itr == accounts.end() )
        return enNoID;
    
    if ( itr->second != info.second )
        return enWrongPW;

    return enSuccess_in;
}

