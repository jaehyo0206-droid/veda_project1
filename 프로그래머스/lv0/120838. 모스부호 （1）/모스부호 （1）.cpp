#include <string>
#include <vector>
#include <sstream>
using namespace std;
string solution(string letter) {
    string answer;
    string alph[26]={".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.."};
    stringstream ss(letter);
    string temp;
    while (ss >> temp) {
       
        for(int i=0;i<26;i++){if(temp==alph[i]){ string s(1, 'a' + i);answer+=s;}}
    }
    return answer;
}