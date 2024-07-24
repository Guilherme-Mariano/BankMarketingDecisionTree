
#ifndef HELPER_H
#define HELPER_H
#include <string>
#include <vector>
using namespace std;

class Helper {
public:
    static bool check_string_is_numeric(string str);
    static bool check_string_in_vector(vector<string> vec,string str);
    static double str_to_double(string object);
};



#endif //HELPER_H
