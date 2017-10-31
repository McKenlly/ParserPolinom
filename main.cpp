#include <map>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
using namespace std;
int GetNum(string &s, int &pos) {
    int value = 0;
    int shift = 10;
    int j = pos;
    while (j < s.size() && s[j] <= '9' && s[j] >= '0') {
        value = value*shift + (int)(s[j]-'0');
        j++;
    }
    pos = j;
    return value;
}
int Parse(string &s, int &pos, int& degree) {
    int ans = 1;
    int i;
    for (i = pos; i < s.size() && s[i] != '+' && s[i] != '-';) {
        if (s[i] >= '0' && s[i] <= '9') {
            int value = GetNum(s, i);
            ans *= value;
            continue;
        }
        if (s[i] == '*') {
            i++;
            continue;
        }
        if (s[i] == 'x' && i+1 < s.size()) {
            if (s[i+1] == '^') {
                i += 2;
                int value = GetNum(s, i);
                degree += value;
                continue;
            }
        }
        if (s[i] == 'x')
            degree++;
        i++;
    }
    pos = i-1;
    return ans;
}
int main(int argc, char **argv)
{
    string str, outStr = "";
    cin >> str;
    map<int, int> result;
    int t;
    for(int i = 0; i < str.size(); i++) {
        int degree = 0;
        if (str[i] == '+')  {
            i++;
            t = Parse(str, i, degree);
            if (degree > 0 && t != 0) {result[degree] += t;}
        }
        else {
            i++;
            t  = Parse(str, i, degree);
            t = -t;
            if (degree > 0 && t != 0) {result[degree] += t;}
        }
    }
    /*for (auto i:result) {
        cout << i.first << " " << i.second << endl;
    }*/
    map<int, int>::iterator it = result.end();
    int i = -1;
    if (result.empty()) {outStr = "0";}
    else
       do {
            if (it == result.begin()) {
                 break;
            }
            it--;
            it->second = it->second*it->first;
            i++;
            if (i != 0) {
                if (it->second > 0) outStr +=  "+"; 
            }
            outStr += to_string(it->second);
            if (it->first == 1) {
                continue;
            }
            if (it->first - 1 == 1) {
                outStr += "*x";
                continue;
            }
        if (it->first - 1 > 1) {
            outStr += "*x^" + to_string(it->first-1);
        }
    } while (it != result.begin());
    cout << outStr;
    return 0;
}