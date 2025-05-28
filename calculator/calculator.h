#pragma once

#include <string>
#include <optional>
#include <cmath>

#include "rational.h"
#include "pow.h"

using Error = std::string;

template <typename Number>
class Calculator {
public:
    Calculator() : current_(0), memory_(std::nullopt) {}

    void Set(Number n) { current_ = n; }
    Number GetNumber() const { return current_; }

    std::optional<Error> Add(Number n) { current_ += n; return std::nullopt; }
    std::optional<Error> Sub(Number n) { current_ -= n; return std::nullopt; }
    std::optional<Error> Mul(Number n) { current_ *= n; return std::nullopt; }

    std::optional<Error> Div(Number n) {
        if constexpr (std::is_integral_v<Number> || std::is_same_v<Number, Rational>) {
            if (n == Number(0)) return "Division by zero";
        }
        current_ /= n;
        return std::nullopt;
    }

    std::optional<Error> Pow(Number n) {
        if constexpr (std::is_integral_v<Number>) {
            if (current_ == 0 &&
                n == 0) {
                return "Zero power to zero";
            }
            if (n < 0) return "Integer negative power";
            current_ = ::IntegerPow(current_, n);
        }
        else if constexpr (std::is_same_v<Number, Rational>) {
            if (current_ == 0 &&
                n == 0) {
                return "Zero power to zero";
            }
            if (n.GetDenominator() != 1) return "Fractional power is not supported";
            current_ = ::Pow(current_, n);
        }
        else {
            current_ = std::pow(current_, n);
        }
        return std::nullopt;
    }

    void Save() { memory_ = current_; }
    void Load() { if (memory_) current_ = *memory_; }
    bool GetHasMem() const { return memory_.has_value(); }

    std::string GetNumberRepr() const {
        if constexpr (std::is_same_v<Number, Rational>) {
            return current_.ToString();
        } else {
            return std::to_string(current_);
        }
    }

private:
    Number current_;
    std::optional<Number> memory_;
};
