#include <string>

#pragma once

using Number = double;

class Calculator {
public:
    void Set(Number value);
    void Add(Number value);
    void Sub(Number value);
    void Mul(Number value);
    void Div(Number value);
    void Pow(Number value);
    void Save();
    void Load();
    bool HasMem() const;
    Number GetNumber() const;
    std::string GetNumberRepr() const;
private:
    Number result = 0;
    Number memory;
    bool memory_save = false;
};
