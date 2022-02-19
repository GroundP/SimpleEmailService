#pragma once
#include "DataTypeDef.h"
class CFileSaver
{

public:
    static bool readAccounts(std::map<std::string, std::string>& accounts);
    static bool readMailList(std::map<std::string, std::vector<Mail>>& list);
    static bool saveAccounts(const std::map<std::string, std::string>& accounts);
    static bool saveMailList(const std::map<std::string, std::vector<Mail>>& list);
};

