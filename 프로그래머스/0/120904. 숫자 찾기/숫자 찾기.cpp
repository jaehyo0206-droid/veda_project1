#include <string>
#include <vector>
using namespace std;

int solution(int num, int k) {
    int answer = 0;
    string ntos =to_string(num);
    char ktoc =k+'0';
    int inx=0;
    for(char c : ntos){
        inx++;
        if(c==ktoc){
            return inx;
        }
    }
    return -1;
}