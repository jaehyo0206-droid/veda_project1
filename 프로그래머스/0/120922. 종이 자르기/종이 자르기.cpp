#include <string>
#include <vector>

using namespace std;

int solution(int M, int N) {
    int answer = (N-1)*M+(M-1);//MN-M+M-1 => MN-1
    //N-1 N의 길이를 만들기 위해 필요한 가위질 수
    //M을 만드는 길이 만큼 N-1의 가위질의 횟수가 늘어난다
    //M-1 길이 M을 만드는데 필요한 가위질 횟수
    return M*N-1;
}