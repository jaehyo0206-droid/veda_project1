#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int solution(vector<vector<int>> dots) {

    int x_min = dots[0][0];
    int x_max = dots[0][0];
    int y_min = dots[0][1];
    int y_max = dots[0][1];

    for(int i=1; i<dots.size(); i++){
        x_min = min(x_min, dots[i][0]);
        x_max = max(x_max, dots[i][0]);
        y_min = min(y_min, dots[i][1]);
        y_max = max(y_max, dots[i][1]);
    }
    return (x_max - x_min)*(y_max - y_min);
}