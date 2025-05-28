#pragma once
#include <iostream>
#include <numeric>
#include <cstdlib>

class Rational {
public:
    Rational() : numerator_(0), denominator_(1) {}
    Rational(int numerator) : numerator_(numerator), denominator_(1) {}
    Rational(int numerator, int denominator) : numerator_(numerator), denominator_(denominator) {
        if (denominator_ == 0) {
            std::abort();
        }
        Reduction();
    }
    Rational(const Rational& other) = default;
    Rational& operator=(const Rational&) = default;

    Rational operator+(const Rational& other) const {
        return Rational(
            numerator_ * other.denominator_ + other.numerator_ * denominator_,
            denominator_ * other.denominator_
            );
    }

    Rational operator-(const Rational& other) const {
        return Rational(
            numerator_ * other.denominator_ - other.numerator_ * denominator_,
            denominator_ * other.denominator_
            );
    }

    Rational operator*(const Rational& other) const {
        return Rational(
            numerator_ * other.numerator_,
            denominator_ * other.denominator_
            );
    }

    Rational operator/(const Rational& other) const {
        if (other.numerator_ == 0) {
            std::abort();
        }
        return Rational(
            numerator_ * other.denominator_,
            denominator_ * other.numerator_
            );
    }

    Rational& operator+=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ + denominator_ * other.numerator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator-=(const Rational& other) {
        numerator_ = numerator_ * other.denominator_ - denominator_ * other.numerator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator*=(const Rational& other) {
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        Reduction();
        return *this;
    }

    Rational& operator/=(const Rational& other) {
        if (other.numerator_ == 0) {
            std::abort();
        }
        numerator_ *= other.denominator_;
        denominator_ *= other.numerator_;
        Reduction();
        return *this;
    }

    Rational operator+() const { return *this; }
    Rational operator-() const { return Rational(-numerator_, denominator_); }

    bool operator==(const Rational& other) const = default;
    auto operator<=>(const Rational& other) const {
        return numerator_ * other.denominator_ <=> other.numerator_ * denominator_;
    }

    Rational Inv() const {
        if (numerator_ == 0) {
            std::abort();
        }
        return Rational(denominator_, numerator_);
    }

    int GetNumerator() const { return numerator_; }
    int GetDenominator() const { return denominator_; }

    std::string ToString() const {
        if (denominator_ == 1) return std::to_string(numerator_);
        return std::to_string(numerator_) + "/" + std::to_string(denominator_);
    }

private:
    void Reduction() {
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
        const int divisor = std::gcd(numerator_, denominator_);
        numerator_ /= divisor;
        denominator_ /= divisor;
    }

    int numerator_;
    int denominator_;

    friend std::ostream& operator<<(std::ostream& os, const Rational& r);
    friend std::istream& operator>>(std::istream& is, Rational& r);
};

inline std::ostream& operator<<(std::ostream& os, const Rational& r) {
    os << r.numerator_;
    if (r.denominator_ != 1) {
        os << " / " << r.denominator_;
    }
    return os;
}

inline std::istream& operator>>(std::istream& is, Rational& r) {
    int num = 0, denom = 1;
    char sep = '\0';

    if (!(is >> num)) {
        return is;
    }

    if (is >> sep && sep == '/') {
        if (!(is >> denom)) {
            is.setstate(std::ios::failbit);
            return is;
        }
        if (denom == 0) {
            is.setstate(std::ios::failbit);
            return is;
        }
    } else {
        if (sep != '\0') {
            is.unget();
        }
    }

    r = Rational(num, denom);
    return is;
}
