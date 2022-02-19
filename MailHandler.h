#pragma once

#include "DataTypeDef.h"
class CMailHandler
{

public:
    CMailHandler();
    ~CMailHandler();

    void setAccount(const std::string& acc) { curAccount = acc; }
    bool run(const std::set<std::string>& accounts);
    
private:
    enMailChoice chooseMailFunc();
    void showProcess();
    void sendMailProcess(const std::set<std::string>& accounts);
    unsigned int getMaxId();

private:
    std::map<std::string, std::vector<Mail>> mailList;
    std::string curAccount;
};


