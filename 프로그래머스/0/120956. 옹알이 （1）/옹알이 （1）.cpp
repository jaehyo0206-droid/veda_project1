#include <string>
#include <vector>
using namespace std;

int solution(vector<string> babbling) {
    int answer = 0;

    for (string s : babbling) {
        int idx = 0;

        while (idx < s.size()) {
            if (s.substr(idx, 3) == "aya")
                idx += 3;
            else if (s.substr(idx, 2) == "ye")
                idx += 2;
            else if (s.substr(idx, 3) == "woo")
                idx += 3;
            else if (s.substr(idx, 2) == "ma")
                idx += 2;
            else
                break;
        }

        if (idx == s.size())
            answer++;
    }

    return answer;
}