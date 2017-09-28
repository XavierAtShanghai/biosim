#include "stringManage.h"


int stringManage::findPosition_inTable(const vector<string> & str_vect,const string& str){

int pos=-1;
    for(uint i=0; i<str_vect.size(); i++){
        if (str_vect[i].find(str)!=std::string::npos){
        pos=i;
        break;
        }
    }
    if (pos==-1) cerr<<"warning findPosition_inTable: "<<" not found "<<str<<endl;
return pos;
}

vector<string> stringManage::split(const string& s, const string& delim, const bool keep_empty) {
    vector<string> result;
    if (delim.empty()) {
        result.push_back(s);
        return result;
    }
    string::const_iterator substart = s.begin(), subend;
    while (true) {
        subend = search(substart, s.end(), delim.begin(), delim.end());
        string temp(substart, subend);
        if (keep_empty || !temp.empty()) {
            result.push_back(temp);
        }
        if (subend == s.end()) {
            break;
        }
        substart = subend + delim.size();
    }
    return result;
}
