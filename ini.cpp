#include "ini.hpp"
#include <fstream>
#include <vector>

using namespace std;

INI::INI(string filepath)
{
    ifstream inFile;
    inFile.open(filepath);

    vector<char> varBuf;
    vector<char> valBuf;

    if (!inFile)
        throw "Unable to open INI-file '" + filepath + "'";

    char inChar;
    int mode = 0;
    size_t linesRead;

    while (inFile.get(inChar))
    {
        if (inChar == ' ' || inChar == '\t')
            continue;

        if (inChar == '\n')
        {
            if (varBuf.empty())
                throw "Unexpected end of line at line " + (linesRead+1);

            if (INI::typeOf(valBuf) == T_INT)
                _valuesInt.insert(pair<string, int>(
                    INI::buildString(varBuf),
                    INI::buildInt(valBuf)
                ));
            else if (INI::typeOf(valBuf) == T_DOUBLE)
                _valuesDouble.insert(pair<string, double>(
                    INI::buildString(varBuf),
                    INI::buildDouble(valBuf)
                ));
            
            varBuf.clear();
            valBuf.clear();
            linesRead++;
            mode = 0;
            continue;
        }

        if (inChar == '=')
        {
            if (varBuf.empty())
                throw "Unexpected '=' symbol at line " + (linesRead+1);
            
            mode = 1;
            continue;
        }

        switch (mode)
        {
            case 0:
                varBuf.push_back(inChar);
                break;
            case 1:
                valBuf.push_back(inChar);
                break;
        }
    }

    if (INI::typeOf(valBuf) == T_INT)
        _valuesInt.insert(pair<string, int>(
            INI::buildString(varBuf),
            INI::buildInt(valBuf)
        ));
    else if (INI::typeOf(valBuf) == T_DOUBLE)
        _valuesDouble.insert(pair<string, double>(
            INI::buildString(varBuf),
            INI::buildDouble(valBuf)
        ));
    
    varBuf.clear();
    valBuf.clear();
    linesRead++;
}

INI::~INI() {}

string INI::typeOf(vector<char> in)
{   
    vector<char>::iterator it;
    
    bool hasPoint = false;
    bool hasDigits = false;

    for (it = in.begin(); it != in.end(); it++)
    {
        if (*it == '.') hasPoint = true;
        if (isdigit(*it)) hasDigits = true;
    }

    if (hasDigits && hasPoint) return T_DOUBLE;
    else if (hasDigits) return T_INT;
    return T_STRING;
}

string INI::buildString(vector<char> in)
{
    string buf;
    
    vector<char>::iterator it;

    for (it = in.begin(); it != in.end(); it++)
        buf += *it;

    return buf;
}

int INI::buildInt(vector<char> in)
{
    string buf;

    vector<char>::iterator it;

    for (it = in.begin(); it != in.end(); it++)
        buf += *it;

    return atoi(buf.c_str());
}

double INI::buildDouble(vector<char> in)
{
    string buf;

    vector<char>::iterator it;

    for (it = in.begin(); it != in.end(); it++)
        buf += *it;

    return atof(buf.c_str());
}

double INI::getDouble(string key)
{
    map<string, double>::iterator it;

    for (it = _valuesDouble.begin(); it != _valuesDouble.end(); it++)
        if (it->first == key)
            return it->second;

    return 0;
}

int INI::getInt(string key)
{
    map<string, int>::iterator it;

    for (it = _valuesInt.begin(); it != _valuesInt.end(); it++)
        if (it->first == key)
            return it->second;

    return 0;
}