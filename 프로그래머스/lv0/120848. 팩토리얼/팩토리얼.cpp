#include <string>
#include <vector>

using namespace std;

int solution(int n) {
    int answer = 1;
    int cnt=0;
    for(int i=2;answer<=n;i++){cnt++; answer*=i;}
    return cnt;
}