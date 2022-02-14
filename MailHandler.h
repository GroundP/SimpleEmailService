#pragma once

#include "DataTypeDef.h"

class CMailHandler
{
    enum enMail
    {

    };

public:
    CMailHandler();
    ~CMailHandler();

    void setAccount(const std::string& acc) { curAccount = acc; }
    bool run(const std::set<std::string>& accounts);
    
private:
    enMailChoice chooseMailFunc();
    void showProcess();
    void sendMailProcess();
private:
    std::map<std::string, std::vector<Mail>> mailList;
    std::string curAccount;
};


