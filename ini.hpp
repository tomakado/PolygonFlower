#ifndef INI_CLASS
#define INI_CLASS

#define T_STRING "type:string"
#define T_INT "type:int"
#define T_DOUBLE "type:double"

#include <map>
#include <vector>

using namespace std;

class INI {
    private:
        map<string, int> _valuesInt;
        map<string, double> _valuesDouble;

        static string buildString(vector<char> in);
        static int buildInt(vector<char> in);
        static double buildDouble(vector<char> in);
        static string typeOf(vector<char> in);
    public:
        INI(string filepath);
        ~INI();
        
        int getInt(string key);
        double getDouble(string key);
};

#endif