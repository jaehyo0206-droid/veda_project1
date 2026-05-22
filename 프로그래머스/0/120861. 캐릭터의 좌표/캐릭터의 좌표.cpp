#include <string>
#include <vector>
#include <map>

using namespace std;

struct Info{
    int x=0;
    int y=0;
};

vector<int> solution(vector<string> keyinput, vector<int> board) {
    vector<int> answer(2,0);
    map<string,Info> m;
    m["left"]={-1,0};
    m["right"]={1,0};
    m["down"]={0,-1};
    m["up"]={0,1};

    int maxX = board[0]/2;
    int maxY = board[1]/2;

    for(string s : keyinput){

        int nx = answer[0] + m[s].x;
        int ny = answer[1] + m[s].y;

        if(nx >= -maxX && nx <= maxX &&
           ny >= -maxY && ny <= maxY)
        {
            answer[0] = nx;
            answer[1] = ny;
        }
    }

    return answer;
}