#pragma once
#include <map>
#include <set>
#include <vector>
#include <string>

enum class enMainChoice
{
    enSignUp=1,
    enSignIn,
    enExit
};

enum class enMailChoice : int
{
    enShow=1,
    enSend,
    enLogout,
    enExit
};

struct Mail
{
    unsigned int id;
    std::string from;
    std::string to;
    std::string title;
    std::string contents;
    bool attached;

    Mail(const unsigned int _id, const std::string& _f, const std::string& _t, 
         const std::string& _tt, const std::string& _c, const bool _a) 
        : id(_id), from(_f), to(_t), title(_tt), contents(_c), attached(_a) {}
};