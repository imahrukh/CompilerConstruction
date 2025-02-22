#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <cctype>

using namespace std;

string getKeywordToken(const string &lexeme);
void tokenize(const string &input, ofstream &outFile);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        cerr << "Usage: " << argv[0] << " <input_file> <output_file>" << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile) {
        cerr << "Error opening input file." << endl;
        return 1;
    }

    ofstream outFile(argv[2]);
    if (!outFile) {
        cerr << "Error opening output file." << endl;
        return 1;
    }

    string input((istreambuf_iterator<char>(inFile)), istreambuf_iterator<char>());
    inFile.close();

    tokenize(input, outFile);

    outFile.close();
    return 0;
}

string getKeywordToken(const string &lexeme) {
    static const unordered_map<string, string> keywordToken = {
        {"char", "CHAR"},
        {"int", "INT"},
        {"if", "IF"},
        {"else", "ELSE"},
        {"while", "WHILE"}
    };
    auto it = keywordToken.find(lexeme);
    return (it != keywordToken.end()) ? it->second : "";
}

void tokenize(const string &input, ofstream &outFile) {
    int index = 0;
    int len = input.length();

    while (index < len) {
        if (isspace(input[index])) {
            index++;
            continue;
        }

        char current = input[index];

        // Identifier or keyword
        if (isalpha(current) || current == '_') {
            int start = index;
            index++;
            while (index < len && (isalnum(input[index]) || input[index] == '_')) {
                index++;
            }
            string lexeme = input.substr(start, index - start);
            string tokenType = getKeywordToken(lexeme);
            if (!tokenType.empty()) {
                outFile << "(" << tokenType << ", ^) ";
            } else {
                outFile << "(ID, \"" << lexeme << "\") ";
            }
        }
        // Integer literal
        else if (isdigit(current)) {
            int start = index;
            index++;
            while (index < len && isdigit(input[index])) {
                index++;
            }
            string num = input.substr(start, index - start);
            outFile << "(INT_LIT, " << num << ") ";
        }
        // Character literal
        else if (current == '\'') {
            index++; // Consume opening '
            if (index >= len) break;
            char value = input[index];
            index++; // Consume character
            if (index < len && input[index] == '\'') {
                index++; // Consume closing '
                outFile << "(CL, '" << value << "') ";
            } else {
                // Unterminated, handle error if needed
                outFile << "(CL, '" << value << "') ";
            }
        }
        // Operators and punctuation
        else {
            switch (current) {
                case '=':
                    if (index + 1 < len && input[index+1] == '=') {
                        outFile << "('==', ^) ";
                        index += 2;
                    } else {
                        outFile << "('=', ^) ";
                        index++;
                    }
                    break;
                case '!':
                    if (index +1 < len && input[index+1] == '=') {
                        outFile << "('!=', ^) ";
                        index +=2;
                    } else {
                        outFile << "('!', ^) ";
                        index++;
                    }
                    break;
                case '<':
                    if (index +1 < len && input[index+1] == '=') {
                        outFile << "('<=', ^) ";
                        index +=2;
                    } else {
                        outFile << "('<', ^) ";
                        index++;
                    }
                    break;
                case '>':
                    if (index +1 < len && input[index+1] == '=') {
                        outFile << "('>=', ^) ";
                        index +=2;
                    } else {
                        outFile << "('>', ^) ";
                        index++;
                    }
                    break;
                case '+':
                    outFile << "('+', ^) ";
                    index++;
                    break;
                case '-':
                    outFile << "('-', ^) ";
                    index++;
                    break;
                case '*':
                    outFile << "('*', ^) ";
                    index++;
                    break;
                case '/':
                    outFile << "('/', ^) ";
                    index++;
                    break;
                case '%':
                    outFile << "('%', ^) ";
                    index++;
                    break;
                case ';':
                    outFile << "(';', ^) ";
                    index++;
                    break;
                case '(':
                    outFile << "('(', ^) ";
                    index++;
                    break;
                case ')':
                    outFile << "(')', ^) ";
                    index++;
                    break;
                case '{':
                    outFile << "('{', ^) ";
                    index++;
                    break;
                case '}':
                    outFile << "('}', ^) ";
                    index++;
                    break;
                default:
                    index++;
                    break;
            }
        }
    }
}