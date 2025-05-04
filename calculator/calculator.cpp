#include "calculator.h"
#include <cmath>

void Calculator::Set(Number value) {
    result = value;
}

void Calculator::Add(Number value) {
    result += value;
}

void Calculator::Sub(Number value) {
    result -= value;
}

void Calculator::Mul(Number value) {
    result *= value;
}

void Calculator::Div(Number value) {
    result /= value;
}

void Calculator::Pow(Number value) {
    result = pow(result, value);
}

void Calculator::Save() {
    memory = result;
    memory_save = true;
}

void Calculator::Load() {
    result = memory;
}

bool Calculator::HasMem() const {
    return memory_save;
}

Number Calculator::GetNumber() const {
    return result;
}

std::string Calculator::GetNumberRepr() const {
    return std::to_string(result);
}
