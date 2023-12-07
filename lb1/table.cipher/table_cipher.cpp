#include "table_cipher.h"
void table_cipher::write_str_to_v(std::string st, std::vector<std::vector<std::string>> &v) {
    int l = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (l < st.length()) { 
                v[i][j] = st[l];
                l++;
            }
            else {
                break;
            }
        }
    }
}
void table_cipher::write_str_to_v(std::vector<std::vector<std::string>> &v) {
    int l = 0;
    for (int i = 0; i < v.size(); i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (l < t.length()) { 
                v[i][j] = t[l];
                l++;
            }
            else {
                break;
            }
        }
    }
    l = 0;
    for (int j = key - 1; j >= 0; j--) {
        for (int i = 0; i < rows; i++) {
            if (l < t.length()) {
                if(v[i][j]==" "){
                    continue;
                }
                v[i][j] = t[l];
                l++;
            } else {
                break;
            }
        }
    }
}
table_cipher::table_cipher(std::string text,double k,std::string& initial_value){
    t=text;
    t.erase(std::remove(t.begin(), t.end(), ' '), t.end());
    double length=t.length();
    rows=std::ceil(length/k);
    st_to_vec=std::vector<std::vector<std::string>>(rows, std::vector<std::string>(k, initial_value));
    key=k;
    i_value=initial_value;
}
std::string table_cipher::encrypt(){
    std::vector<std::vector<std::string>> en_v=std::vector<std::vector<std::string>>(rows, std::vector<std::string>(key, i_value));
    write_str_to_v(t,st_to_vec);
    std::string res="";
   
    for(int j =key-1;j>=0;j--){
        for(int i=0;i<rows;i++){
            res=res+st_to_vec[i][j];
        }
    }
    res.erase(std::remove(res.begin(), res.end(), ' '), res.end());
    return res;
}
std::string table_cipher::decrypt() {
    std::vector<std::vector<std::string>> en_v = std::vector<std::vector<std::string>>(rows, std::vector<std::string>(key, i_value));
    write_str_to_v(st_to_vec);
    std::string res = "";
    for (int i = 0; i <rows; i++) {
        for (int j = 0; j < key; j++) {
            res = res + st_to_vec[i][j];
        }
    }
    return res;
}
