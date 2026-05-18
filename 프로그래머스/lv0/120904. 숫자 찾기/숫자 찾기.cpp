#include <string>
using namespace std;
int solution(int num, int k) {
    int found = to_string(num).find('0'+k)+1;
    return found ? found : -1;
}
