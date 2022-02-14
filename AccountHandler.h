#pragma once
#include "DataTypeDef.h"

class CAccountHandler
{
    enum enSignupRes
    {
        enSuccess_up,
        enExistID,
        enWrongInput,
    };

    enum enSigninRes
    {
        enSuccess_in,
        enNoID,
        enWrongPW,
    };

public:
    bool processSignUp();
    bool processSignIn(std::pair<std::string, std::string>& info);
    std::set<std::string> getAllId();

private:
    bool chooseAuthInfo(std::pair<std::string, std::string>& info);
    enSignupRes validateSingup(std::pair<std::string, std::string>& info);
    enSigninRes validateSingin(std::pair<std::string, std::string>& info);

private:
    std::map<std::string, std::string> accounts; 
};

