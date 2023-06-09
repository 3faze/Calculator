#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

bool has_error = false;

struct Token{
    char value;
    std::string type;
};

class Lexer {
public:
    int line_num;
    std::string curr_char;
    std::vector<char> literals = {'+', '-', '/', '*', ' ', ';'};
    std::vector<Token> tokenize(const std::vector<std::string>& lines) {
        bool at_end_of_line = false;
        std::string curr_err_showoff;
        std::vector<Token> ret_tokens;

        int line_num = 0;
        for (const std::string& line : lines) {
            line_num++;
            if (at_end_of_line == true) {
                curr_err_showoff = "";
                at_end_of_line = false;
            }
            for (char curr_char : line) {
                curr_err_showoff += curr_char;
                std::string token(1, curr_char);
                if (curr_char != ' '){
                    if (std::find(literals.begin(), literals.end(), curr_char) != literals.end()) {
                        if (curr_char == ';'){
                            Token semicolon;
                            semicolon.type = "LITERAL";
                            semicolon.value = ';';
                            ret_tokens.push_back(semicolon);
                            at_end_of_line = true;
                        } else {
                            Token literal;
                            literal.type = "LITERAL";
                            literal.value = curr_char;
                            ret_tokens.push_back(literal);
                        }
                    } else {
                        if (std::isdigit(curr_char)){
                            Token number;
                            number.type = "NUMBER";
                            number.value = curr_char;
                            ret_tokens.push_back(number);
                        } else {
                            std::cout << "\033[1;31mError: Invalid Input\033[0m\nThe character 'curr_char' is not a valid member of 'literals'" << std::endl;
                            std::cout << "Error at -> '" << curr_err_showoff << "', at line " << line_num << std::endl;
                            has_error = true;
                        }
                    }
                }
            }
        }
        return ret_tokens;
    }
};
int main(int argc, char* argv[]) {
    Lexer lexer;
    std::vector<std::string> lines;
    std::string name;
    if (argc < 2) {
        std::cout << "Usage: " << "./main.exe" << " <filename>" << std::endl;
        return 1;
    }
    name = argv[1];
    std::cout << "Name -> " << name << std::endl;
    std::cout << "----OUTPUT----" << std::endl;
    std::ifstream rfile(name);
    if (rfile.is_open()) {
        std::string line;
        while (std::getline(rfile, line)) {
            lines.push_back(line);
        }
        rfile.close();
        Lexer lexer;
        std::vector<Token> tokens = lexer.tokenize(lines);
        for (const Token& token : tokens) {
            if (has_error == false) {
                std::cout << token.value << " : " << token.type << std::endl;
            } else {
                return 1;
            }
        }
    } else {
        std::cout << "Failed to open " << name << std::endl;
        return 1;
    }
    return 0;
}
