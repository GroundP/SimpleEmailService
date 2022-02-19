#pragma once
#include "DataTypeDef.h"

class CAccountHandler
{

public:
    CAccountHandler();
    ~CAccountHandler();
    bool processSignUp();
    bool processSignIn(std::pair<std::string, std::string>& info);
    std::set<std::string> getAllId();
    void showAccounts();

private:
    bool chooseAuthInfo(std::pair<std::string, std::string>& info);
    //enSignupRes validateSignup(std::pair<std::string, std::string>& info);
    bool validateSignup(const std::pair<std::string, std::string>& info);
    bool validateSignin(const std::pair<std::string, std::string>& info);

private:
    std::map<std::string, std::string> accounts; 
};

