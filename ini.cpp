/*
Copyright (c) 2019, Ildar Karymov
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
   list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.

3. Neither the name of the copyright holder nor the names of its
   contributors may be used to endorse or promote products derived from
   this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

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