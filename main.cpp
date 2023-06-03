#include <iostream>
#include <string>
#include <cstring>

std::string get_line(std::string var){
    std::getline(std::cin, var);
    return var;
}

char* tokenize(std::string op){
    int lenght = op.size() + 1;
    char arr[lenght];
    strcpy(arr, op.c_str());

    return arr;
}

int main(){
    std::string text_op;
    while (text_op != "quit()"){
        std::cout << "OP > ";
        text_op = get_line(text_op);
        for (int i = 0; i > sizeof(tokenize(text_op)) / sizeof(char); i++){
            std::cout << tokenize(text_op)[i] << std::endl;
        }

    }
}
