//
//  Rational Sums (Ad Infinitum 18).cpp
//  Hackerrank
//
//  Created by Mikael Arakelian on 6/11/17.
//  Copyright © 2017 Mikael Arakelian. All rights reserved.
//

#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <vector>

template<long long n>
struct Ring {
    Ring(long long value=0) {
        if (value < 0) {
            value %= n;
            value += n;
        }
        this->value = value % n;
    }
    Ring operator + (const Ring& b) const {
        return Ring(this->value + b.value);
    }
    Ring operator * (const Ring& b) const {
        return Ring(this->value * b.value);
    }
    Ring operator - () const {
        return Ring(n - this->value);
    }
    Ring operator - (const Ring& b) const {
        return *this + (-b);
    }
    Ring& operator *= (const Ring& b) {
        *this = *this * b;
        return *this;
    }
    Ring& operator += (const Ring& b) {
        *this = *this + b;
        return *this;
    }
    Ring& operator -= (const Ring& b) {
        *this = *this - b;
        return *this;
    }
    Ring& operator = (const Ring& b) {
        this->value = b.value;
        return *this;
    }
    long long value;
};

template<long long n>
std::istream& operator >> (std::istream& in, Ring<n>& r) {
    long long x;
    in >> x;
    r = Ring<n>(x);
    return in;
}

template<long long n>
std::ostream& operator << (std::ostream& out, const Ring<n>& r) {
    out << r.value;
    return out;
}

template<long long n>
Ring<n> power(Ring<n> a, int p) {
    Ring<n> result(1);
    while (p) {
        if (p & 1) {
            result *= a;
        }
        p >>= 1;
        a *= a;
    }
    return result;
}

const long long mod = 1000 * 1000 * 1000 + 7;
typedef Ring<mod> Field;
const long long cache_size = 10000;
std::vector<Field> field_inverses;

Field field_inverse_slow(const Field& a) {
    return power(a, mod - 2);
}

void precalc() {
    field_inverses.resize(cache_size);
    field_inverses[0] = 0;
    for (int i = 1; i < cache_size; ++i) {
        field_inverses[i] = field_inverse_slow(i);
    }
}

Field field_inverse(const Field& a) {
    if (a.value < cache_size) {
        return field_inverses[a.value];
    }
    return field_inverse_slow(a);
}


Field operator / (const Field& a, const Field& b) {
    return a * field_inverse(b);
}

typedef std::vector<Field> FieldPolynomial;

Field evaluate(const FieldPolynomial& polynomial, const Field& value) {
    Field result = 0;
    for (int i = 0; i < polynomial.size(); ++i) {
        result = result * value + polynomial[i];
    }
    return result;
}

int main() {
    precalc();
    int n;
    std::cin >> n;
    std::vector<int> roots(n);
    FieldPolynomial P(n - 1);
    
    for (int i = 0; i < n; ++i) {
        std::cin >> roots[i];
    }
    std::sort(roots.begin(), roots.end());
    for (int i = 0; i < n - 1; ++i) {
        std::cin >> P[i];
    }
    std::reverse(P.begin(), P.end());
    
    std::vector<Field> A(n);
    for (int i = 0; i < n; ++i) {
        Field numerator = evaluate(P, -roots[i]);
        Field denum = 1;
        for (int j = 0; j < n; ++j) {
            if (j == i) {
                continue;
            }
            denum *= Field(roots[j] - roots[i]);
        }
        A[i] = numerator * field_inverse(denum);
    }
    
    int biggest_root = roots.back();
    Field sum = 0;
    
    for (int i = 0; i < n; ++i) {
        Field numerator = A[i];
        for (int j = roots[i] + 1; j <= biggest_root + 1; ++j) {
            sum += numerator * field_inverse(j);
        }
    }
    
    std::cout << sum;
}
