#include <string>
#include <vector>

using namespace std;

int solution(int M, int N) {
    int answer = (N-1)*M+(M-1);
    return answer;
}