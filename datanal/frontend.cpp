#include <vector>
#include <string>
#include <dirent.h>
//#include <stdio.h>
#include <algorithm>
#include <fstream>
#include <sstream>
//#include <iterator>
#include <iostream>
#include <iomanip>
#include "frontend.h"

using namespace std;

vector<string> GetFileNames(const string dirname)
{
    DIR *dir;
    struct dirent *ent;
    vector<string> FileNames;
    string temp;

    if ((dir = opendir (dirname.c_str())) != NULL) {
    /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
        //printf ("%s\n", ent->d_name);
            temp = ent->d_name;
            if (temp.size()>3 && temp.substr(temp.size()-4)==".log")
                FileNames.push_back(ent->d_name);
        }
        closedir (dir);
    } else {
    /* could not open directory */
        perror ("");
    }

    sort(FileNames.begin(), FileNames.end());
    return FileNames;
}

vector<string> GetColNames(const vector<string> filenames)
{
    vector<string> colnames;
    string s;

    ifstream testFile(filenames[0]);

    for (;;)
    {
        getline(testFile, s);
        istringstream ss(s);
        while (!ss.eof())
        {
            string x;
            ss >> x;
            colnames.push_back(x);
        }
        if (colnames[0] == "TIME") break;

        colnames.clear();
    }

    testFile.close();
    return colnames;
}

int GetColIndex(const vector<string> colnames, const string column)
{

    if (column == "?")
    {
        for (auto x:colnames)
        cout << left << setw(20) << x;
        cout << endl;
        return -1;
    }
    for (unsigned i=0; i!=colnames.size(); ++i)
        if (colnames[i] == column) return static_cast<int>(i);
    cerr << "No such parameter exists\nEnter ? for parameter list\n";
    return -1;
}

vector<string> GetColData(const string filename, const int colindex)
{
    vector<string> column;
    string s, tmp;
    ifstream testFile(filename);

    if (!testFile)
    {
        cout << "file not exist : " << testFile << endl;
        return column;
    }

    while (getline(testFile, s))
    {
        istringstream ss(s);
        char c = ss.peek();
        if (!isdigit(c)) continue;
        for (auto i=0; i<colindex+1; ++i) ss >> tmp;
        column.push_back(tmp);
    }
    return column;
}

vector<double> GetColDData(const string filename, const int colindex)
{
    vector<double> column;
    string s, tmp;
    double dtmp;
    ifstream testFile(filename);

    if (!testFile)
    {
        cout << "file not exist : " << testFile << endl;
        return column;
    }

    while (getline(testFile, s))
    {
        istringstream ss(s);
        char c = ss.peek();
        if (!isdigit(c)) continue;
        for (auto i=0; i<colindex; ++i) ss >> tmp;
        ss >> dtmp;
        column.push_back(dtmp);
    }
    return column;
}

unsigned GetMaxStep(const vector<string> fnlist)
{
    vector<string> tmp = GetColData(fnlist[0], GetColIndex(GetColNames(fnlist), "STEP_Counter"));
    return atoi(tmp.back().c_str());
}
