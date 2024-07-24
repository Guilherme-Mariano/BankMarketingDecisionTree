
#include "Helper.h"

bool Helper::check_string_is_numeric(string str) {
    for(int i = 0; i < str.length(); i++) {
        if(str[i] != '.' && !isdigit(str[i]) && str[i] != '-') {
            return false;
        }
    }
    return true;
}

bool Helper::check_string_in_vector(vector<string> vec, string str) {
    if(vec.empty()) return false;
    for(int i = 0; i < vec.size(); i++) {
        if(vec.at(i) == str) return true;
    }
    return false;
}


double Helper::str_to_double(string object) {
    if(object.empty() || object == " ") {
        return 0;
    }
    return stod(object);
}
