#pragma once

#include <string>
#include <vector>

using namespace std;

class Path
{
private:
    string SEP = "/";
    vector<string> VecPath;

public:
    Path() {};

    Path(string StrPath)
    {
        if (StrPath.substr(0, 1) == SEP)
        {
            StrPath = StrPath.substr(1);
        }

        while (StrPath.size() > 1)
        {
            string CurrentSection = StrPath.substr(0, StrPath.find(SEP));

            VecPath.push_back(CurrentSection);

            if (CurrentSection.size() + 1 < StrPath.size())
                StrPath = StrPath.substr(CurrentSection.size() + 1);
            else
                StrPath = "";
        }
    }

    void AddToEnd(string Addition)
    {
        VecPath.push_back(Addition);
    }

    void RemoveFromEnd()
    {
        VecPath.pop_back();
    }

    void AddToStart(string Addition)
    {
        VecPath.insert(VecPath.begin(), Addition);
    }

    void RemoveFromStart()
    {
        VecPath.erase(VecPath.begin());
    }

    string operator[](int Pos)
    {
        return VecPath[Pos];
    }

    size_t size()
    {
        return VecPath.size();
    }

    string GetLast()
    {
        return VecPath.back();
    }

    string GetStrPath()
    {
        string StrPath = "";

        for (string Section: VecPath)
        {
            StrPath += SEP + Section;
        }

        if (StrPath.length() > 0)
        {
            StrPath = StrPath.substr(1);
        }
        
        return StrPath;
    }
};