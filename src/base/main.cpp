#include <iostream>
#include <string>
#include "./../lexer/main.hpp"
using namespace std;
int main(const char* args[]){
    while (true){
        string input = "";
        getline(cin, input);
        Lexer lexer_ = Lexer(string("<shell>"));
        cout << input << endl;
    }
    return 0;
}