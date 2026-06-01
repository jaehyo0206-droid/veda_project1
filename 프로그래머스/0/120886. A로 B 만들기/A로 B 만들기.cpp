#include <string>
using namespace std;

int solution(string before, string after) {
    for (char c : before) {
        size_t pos = after.find(c);

        if (pos == string::npos) {
            return 0;
        }

        after.erase(pos, 1);
    }

    return 1;
}