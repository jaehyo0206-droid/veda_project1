#include <string>
#include <vector>

using namespace std;

string solution(vector<string> id_pw, vector<vector<string>> db) {
    for (auto user : db) {
        if (user[0] == id_pw[0]) {
            if (user[1] == id_pw[1])
                return "login";
            else
                return "wrong pw";
        }
    }

    return "fail";
}