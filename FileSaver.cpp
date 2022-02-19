#include "FileSaver.h"

bool CFileSaver::readAccounts(std::map<std::string, std::string>& accounts)
{
    FILE* fd = fopen("Accounts.txt", "r");

    if ( !fd )
        return false;

    char line[1024];
    char *pLine;
    while (!feof(fd)) 
    {
        pLine = fgets(line, 1024, fd);
        std::string id;
        std::string pw;

        char* ptr = strtok(pLine, ",");
        if ( ptr )
            id = ptr;

        ptr = strtok(NULL, ",");
        if ( ptr )
        {
            ptr[strlen(ptr)-1] = '\0';
            pw = ptr;
        }

        if ( !id.empty() && !pw.empty() )
            accounts[id] = pw;
    }

    fclose(fd);

    return !accounts.empty();
}

bool CFileSaver::readMailList(std::map<std::string, std::vector<Mail>>& list)
{
    FILE* fd = fopen("MailList.txt", "r");

    if ( !fd )
        return false;

    char line[1024];
    char *pLine;
    while (!feof(fd)) 
    {
        pLine = fgets(line, 1024, fd);
        if ( !pLine )
            continue;

        std::string account;
        std::string id;
        std::string from;
        std::string to;
        std::string title;
        std::string contents;
        std::string attached;

        char* ptr = strtok(pLine, ",");
        account = ptr;

        ptr = strtok(NULL, ",");
        if (!ptr)  continue;
        else id = ptr;

        ptr = strtok(NULL, ",");
        if (!ptr)  continue;
        else from = ptr;

        ptr = strtok(NULL, ",");
        if (!ptr)  continue;
        else to = ptr;

        ptr = strtok(NULL, ",");
        if (!ptr)  continue;
        else title = ptr;

        ptr = strtok(NULL, ",");
        if (!ptr)  continue;
        else contents = ptr;

        ptr = strtok(NULL, ",");
        if (!ptr)  continue;
        else
        {
            ptr[strlen(ptr)-1] = '\0';
            attached = ptr;
        }

        if ( !account.empty() && !id.empty() && !from.empty() && !to.empty() && !title.empty() && !contents.empty() )
            list[account].push_back(Mail(std::stoi(id), from, to, title, contents, attached == "y"));
    }

    fclose(fd);

    return !list.empty();
}

bool CFileSaver::saveAccounts(const std::map<std::string, std::string>& accounts)
{
    FILE* fd = fopen("Accounts.txt", "w");

    if ( !fd )
        return false;

    for ( const auto& a : accounts )
    {
        fputs((a.first + "," + a.second + "\n").c_str(), fd);
    }

    fclose(fd);
    return true;
}

bool CFileSaver::saveMailList(const std::map<std::string, std::vector<Mail>>& list)
{
    FILE* fd = fopen("MailList.txt", "w");
    
    if ( !fd )
        return false;

    for ( const auto& a : list )
    {
        for ( const auto& m : a.second )
        {
            std::string tmp = a.first + "," + std::to_string(m.id) + "," + m.from + "," + m.to + "," + 
                              m.title + "," + m.contents + "," + std::to_string(m.attached) + "\n";

            fputs(tmp.c_str(), fd);
        }
    }
    
    fclose(fd);
    return true;
}
