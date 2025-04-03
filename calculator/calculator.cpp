#include <iostream>
#include <string>
#include <cmath>
#include <vector>
#include <algorithm>
#include "calculator.h"

const std::vector<std::string> ALLOW_TOKENS = {"+", "-", "*", "/", "**", "=", "q", ":", "c", "s", "l"};

bool ReadNumber(Number& result) {
    if (!(std::cin >> result)) {
        std::cerr << "Error: Numeric operand expected" << std::endl;
        return false;
    }

    return true;
}

bool ReadToken(std::string& token) {
    std::cin >> token;

    if (std::find(ALLOW_TOKENS.begin(), ALLOW_TOKENS.end(), token) == ALLOW_TOKENS.end()) {
        std::cerr << "Error: Unknown token " << token << std::endl;
        return false;
    }

    return true;
}

bool RunCalculatorCycle() {
    Number number = 0;
    Number result = 0;
    Number memory = 0;
    bool memory_save = false;

    std::string token = "";
    
    if (!ReadNumber(number)) {
        return false;
    } else {
        // Основной цикл.
        result = number;
        while (true) {
            if (!ReadToken(token)) {
                break;
            } else {
                if (token == "+") {
                    if (!ReadNumber(number)) {
                        break;
                    }
                    result += number;
                } else if (token == "-") {
                    if (!ReadNumber(number)) {
                        break;
                    }
                    result -= number;
                } else if (token == "*") {
                    if (!ReadNumber(number)) {
                        break;
                    }
                    result *= number;
                } else if (token == "/") {
                    if (!ReadNumber(number)) {
                        break;
                    }
                    result /= number;
                } else if (token == "**") {
                    if (!ReadNumber(number)) {
                        break;
                    }
                    result = pow(result, number);
                } else if (token == "=") {
                    std::cout << result << std::endl;
                } else if (token == ":") {
                    if (!ReadNumber(number)) {
                        break;
                    }
                    result = number;
                } else if (token == "c") {
                    result = 0;
                } else if (token == "q") {
                    break;
                } else if (token == "s") {
                    memory = result;
                    memory_save = true;
                } else if (token == "l") {
                    if (!memory_save) {
                        std::cerr << "Error: Memory is empty" << std::endl;
                        break;
                    } else {
                        result = memory;
                    }
                }
            }
        }
    }

    return false;
}
