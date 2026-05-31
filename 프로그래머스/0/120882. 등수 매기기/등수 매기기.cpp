#include <string>
#include <vector>
#include <set>
using namespace std;
vector<int> solution(vector<vector<int>> score) {
    vector<int> total;
    vector<int> answer(score.size());

    for (auto s : score) {
        total.push_back(s[0] + s[1]);
    }

    int n = total.size();

    for (int i = 0; i < n; i++) {
        int rank = 1;

        for (int j = 0; j < n; j++) {
            if (total[i] < total[j]) {
                rank++;
            }
        }

        answer[i] = rank;
    }

    return answer;
}