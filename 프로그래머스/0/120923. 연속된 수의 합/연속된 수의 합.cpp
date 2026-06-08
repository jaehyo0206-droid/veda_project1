#include <vector>
using namespace std;

vector<int> solution(int num, int total) {
    // 충분히 넓은 후보 범위 만들기 (음수도 답이 될 수 있으므로)
    vector<int> range;
    for (int i = -1000; i <= 1000; i++) range.push_back(i);

    // 시작 위치를 1칸씩 밀면서 길이 num짜리 구간을 모두 검사
    for (int s = 0; s + num <= (int)range.size(); s++) {
        int sum = 0;
        for (int j = s; j < s + num; j++) sum += range[j];

        if (sum == total) {
            vector<int> answer;
            for (int j = s; j < s + num; j++) answer.push_back(range[j]);
            return answer;
        }
    }
    return {}; // 제약상 도달하지 않음
}