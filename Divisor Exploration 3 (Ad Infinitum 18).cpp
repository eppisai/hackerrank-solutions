//
//  Divisor Exploration 3 (Ad Infinitum 18).cpp
//  Hackerrank
//
//  Created by Mikael Arakelian on 6/11/17.
//  Copyright © 2017 Mikael Arakelian. All rights reserved.
//

#include <cassert>
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

template<long long n>
struct Ring {
    Ring(long long value=0) {
        if (value < 0) {
            value %= n;
            value += n;
        }
        this->value = value % n;
    }
    Ring operator + (const Ring& b) {
        return Ring(this->value + b.value);
    }
    Ring operator * (const Ring& b) {
        return Ring(this->value * b.value);
    }
    Ring operator - () {
        return Ring(n - this->value);
    }
    Ring operator - (const Ring& b) {
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

Field field_inverse(const Field& a) {
    return power(a, mod - 2);
}

std::vector<int> primes;
std::vector<Field> primes_inverse;
std::vector<Field> field_inverses_precalc;
const int primes_needed = 1000;

void precalculate() {
    const int sieve_size = primes_needed * 32 + 1;
    bool sieve[sieve_size];
    std::fill(std::begin(sieve), std::end(sieve), true);
    sieve[0] = sieve[1] = false;
    primes.reserve(primes_needed);
    for (int i = 2; i < sieve_size && primes.size() < primes_needed; ++i) {
        if (sieve[i]) {
            primes.push_back(i);
            if (i * 1ll * i < sieve_size) {
                for (int j = i * i; j < sieve_size; j += i) {
                    sieve[j] = false;
                }
            }
        }
    }
    
    primes_inverse.resize(primes_needed);
    for (int i = 0; i < primes_needed; ++i) {
        primes_inverse[i] = field_inverse(primes[i]);
    }
    field_inverses_precalc.resize(2001);
    field_inverses_precalc[0] = 0;
    for (int i = 1; i <= 2000; ++i) {
        field_inverses_precalc[i] = field_inverse(i);
    }
}

Field solve_for_prime(int prime_index, int n, int depth) {
    Field sum = 0;
    
    Field prime_power = power(Field(primes[prime_index]), n);
    Field prime_inverse = primes_inverse[prime_index];
    Field choose = 1;
    
    for (int i = 0; i <= n; ++i) {
        sum += prime_power * choose;
        prime_power *= prime_inverse;
        choose = choose * (depth + i) * field_inverses_precalc[i + 1];
    }

    return sum;
}

Field solve() {
    int primes, shift, depth;
    std::cin >> primes >> shift >> depth;
    Field answer = 1;
    
    for (int i = 0; i < primes; ++i) {
        answer *= solve_for_prime(i, shift + i + 1, depth - 1);
    }
    
    return answer;
}

int main() {
    precalculate();
    
    int queries;
    std::cin >> queries;
    for (int i = 0; i < queries; ++i) {
        std::cout << solve() << "\n";
    }
    return 0;
}


