#include <string>
#include <algorithm>
using namespace std;

string solution(string bin1, string bin2) {
    string answer = "";
    
    int bin1_inx = bin1.size() - 1;
    int bin2_inx = bin2.size() - 1;
    int up = 0;

    while (bin1_inx >= 0 || bin2_inx >= 0 || up) {
        int sum = up;

        if (bin1_inx >= 0) sum += bin1[bin1_inx--] - '0';
        if (bin2_inx >= 0) sum += bin2[bin2_inx--] - '0';

        answer.push_back((sum % 2) + '0');
        up = sum / 2;
    }

    reverse(answer.begin(), answer.end());
    return answer;
}