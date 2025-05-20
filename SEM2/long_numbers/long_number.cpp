#include "long_number.hpp"

using biv::LongNumber;

#define POSITIVE 1
#define NEGATIVE -1

// !!!!!!!!!!!
// LongNumber is stored in numbers array as little endian
// so number 178 will be stored as [8, 7, 1]
// !!!!!!!!!!!
		
LongNumber::LongNumber() : sign(POSITIVE), numbers(new int[1]), length(1) {
    numbers[0] = 0;
}

LongNumber::LongNumber(const char* const str) {
    *this = str;
}

LongNumber::LongNumber(const LongNumber& x) {
    *this = x;
}

LongNumber::LongNumber(LongNumber&& x) {
    *this = std::move(x);
}

LongNumber::~LongNumber() {
    if (numbers != nullptr)
        delete [] numbers;
}

LongNumber& LongNumber::operator = (const char* const str) {
    // we will get 0 if some error occured
    sign = POSITIVE;
    numbers = new int[1];
    length = 1;
    
    int len = get_length(str);
    if (len == 0)
        return *this; // we got error in input
    
    int start = 0;
    if (str[0] == '-') {
        ++start;
    }
    
    for (int i = start; i < len; ++i) {
        if (str[i] < '0' || str[i] > '9')
            return *this; // we got error in input
    }
    
    if (str[start] == '0' && len > start + 1)
        return *this; // we got error in input
    
    // everything is good here
    sign = (start == 0) ? POSITIVE : NEGATIVE;
    length = (start == 0) ? len : len-1;
    delete [] numbers;
    numbers = new int[length];
    
    for (int i = 0; i < length; ++i) {
        numbers[i] = int(str[length + start - 1 - i] - '0');
    }
    
    return *this;
}

LongNumber& LongNumber::operator = (const LongNumber& x) {
    sign = x.sign;
    length = x.length;
    numbers = new int[length];
    for (int i = 0; i < length; ++i) {
        numbers[i] = x.numbers[i];
    }
    return *this;
}

LongNumber& LongNumber::operator = (LongNumber&& x) {
    sign = x.sign;
    length = x.length;
    numbers = x.numbers;
    x.numbers = nullptr;
    return *this;
}

bool LongNumber::operator == (const LongNumber& x) const {
    if (sign != x.sign)
        return false;
    return compare_abs_values(*this, x) == AbsValuesCompare::EQUAL;
}

bool LongNumber::operator != (const LongNumber& x) const {
    return !(*this == x);
}

bool LongNumber::operator > (const LongNumber& x) const {
    if (sign == POSITIVE && x.sign == NEGATIVE)
        return true;
    if (sign == NEGATIVE && x.sign == POSITIVE)
        return false;
    
    AbsValuesCompare res = compare_abs_values(*this, x);
    
    if (res == AbsValuesCompare::EQUAL)
        return false;
    
    if (res == AbsValuesCompare::GREATER)
        return (sign == POSITIVE) ? true : false;
    else
        return (sign == POSITIVE) ? false : true;
}

bool LongNumber::operator < (const LongNumber& x) const {
    return !(*this > x) && (*this != x);
}

LongNumber LongNumber::operator + (const LongNumber& x) const {
    // + +
    if (sign == POSITIVE && x.sign == POSITIVE) {
        LongNumber result = add_abs_values(*this, x);
        result.sign = POSITIVE;
        return result;
    }
    
    // - -
    if (sign == NEGATIVE && x.sign == NEGATIVE) {
        LongNumber result = add_abs_values(*this, x);
        result.sign = NEGATIVE;
        return result;
    }
    
    AbsValuesCompare comp_res = compare_abs_values(*this, x);
    
    // + -
    if (sign == POSITIVE && x.sign == NEGATIVE) {
        if (comp_res == AbsValuesCompare::EQUAL || comp_res == AbsValuesCompare::GREATER) {
            LongNumber result = subtract_abs_values(*this, x);
            result.sign = POSITIVE;
            return result;
        } else {
            LongNumber result = subtract_abs_values(x, *this);
            result.sign = NEGATIVE;
            return result;
        }
    }
    
    // - +
    if (comp_res == AbsValuesCompare::EQUAL || comp_res == AbsValuesCompare::LESS) {
        LongNumber result = subtract_abs_values(x, *this);
        result.sign = POSITIVE;
        return result;
    } else {
        LongNumber result = subtract_abs_values(*this, x);
        result.sign = NEGATIVE;
        return result;
    }
}

LongNumber LongNumber::operator - (const LongNumber& x) const {
    LongNumber neg = x;
    neg.sign = neg.sign * (-1);
    return *this + neg;
}

LongNumber LongNumber::operator * (const LongNumber& x) const {
    if(*this == LongNumber() || x == LongNumber())
        return LongNumber();
    
    LongNumber result;
    
    for (int i = 0; i < length; i++) {
        if (numbers[i] == 0)
            continue;
        LongNumber temp = x;
        temp.sign = POSITIVE;
        temp.multiply_by_digit(numbers[i]);
        for (int j = 0; j < i; j++)
            temp.multiply_by_ten();
        result = result + temp;
    }
    
    result.sign = sign * x.sign;
    return result;
}

LongNumber LongNumber::operator / (const LongNumber& x) const {
    std::pair<LongNumber, LongNumber> res = divide_abs_values(*this, x);
    if (res.first == LongNumber())
        return LongNumber();
    
    res.first.sign = sign * x.sign;
    return res.first;
}

LongNumber LongNumber::operator % (const LongNumber& x) const {
    std::pair<LongNumber, LongNumber> res = divide_abs_values(*this, x);
    if (res.second == LongNumber())
        return LongNumber();
    
    if (sign * x.sign == POSITIVE) {
        res.second.sign = sign;
        return res.second;
    } else {
        res.second.sign = x.sign;
        res.second = x - res.second;
        return res.second;
    }
    
    return res.second;
}

int LongNumber::get_digits_number() const noexcept {
    return length;
}

int LongNumber::get_rank_number(int rank) const {
    if (rank < 0 || rank >= length)
        return -1; // we got error in input
    return numbers[length - 1 - rank];
}

bool LongNumber::is_negative() const noexcept {
    return sign == NEGATIVE;
}

// ----------------------------------------------------------
// PRIVATE
// ----------------------------------------------------------
int LongNumber::get_length(const char* const str) const noexcept {
    int len = 0;
    const char* current = str;
    while (*current != '\0') {
        ++len;
        ++current;
    }
    return len;
}

LongNumber::AbsValuesCompare LongNumber::compare_abs_values(const LongNumber& x, const LongNumber& y) const {
    if (x.length > y.length)
        return AbsValuesCompare::GREATER;
    if (x.length < y.length)
        return AbsValuesCompare::LESS;
    
    for (int i = x.length-1; i >= 0; i--) {
        if (x.numbers[i] > y.numbers[i])
            return AbsValuesCompare::GREATER;
        if (x.numbers[i] < y.numbers[i])
            return AbsValuesCompare::LESS;
    }
    
    return AbsValuesCompare::EQUAL;
}

LongNumber LongNumber::add_abs_values(const LongNumber& x, const LongNumber& y) const {
    const LongNumber& longest = (x.length > y.length) ? x : y;
    const LongNumber& shortest = (x.length > y.length) ? y : x;
    
    LongNumber result(longest);
    int carry = 0;
    
    for (int i = 0; i < shortest.length; i++) {
        result.numbers[i] += shortest.numbers[i] + carry;
        carry = result.numbers[i] / 10;
        result.numbers[i] %= 10;
    }
    
    for (int i = shortest.length; i < longest.length && carry != 0; i++) {
        result.numbers[i] += carry;
        carry = result.numbers[i] / 10;
        result.numbers[i] %= 10;
    }
    
    if (carry != 0) {
        LongNumber copy = result;
        delete [] result.numbers;
        result.length = copy.length + 1;
        result.numbers = new int[result.length];
        for (int i = 0; i < copy.length; i++)
            result.numbers[i] = copy.numbers[i];
        result.numbers[result.length - 1] = 1;
    }
    
    return result;
}

// x must be >= y !!!!
LongNumber LongNumber::subtract_abs_values(const LongNumber& big, const LongNumber& small) const {
    if (compare_abs_values(big, small) == AbsValuesCompare::LESS)
        return LongNumber(); // error case
    if (compare_abs_values(big, small) == AbsValuesCompare::EQUAL)
        return LongNumber();
    
    LongNumber result(big);
    int borrow = 0;
    
    for (int i = 0; i < small.length; i++) {
        result.numbers[i] = big.numbers[i] - small.numbers[i] - borrow;
        borrow = result.numbers[i] < 0;
        result.numbers[i] = (result.numbers[i] < 0) ? result.numbers[i] + 10 : result.numbers[i];
    }
    
    for (int i = small.length; i < big.length; i++) {
        result.numbers[i] = big.numbers[i] - borrow;
        borrow = result.numbers[i] < 0;
        result.numbers[i] = (result.numbers[i] < 0) ? result.numbers[i] + 10 : result.numbers[i];
    }
    
    // we need to remove trailing zeroes
    
    int trailingZeroes = 0;
    for (int i = result.length - 1; i >= 0; i--)
        if (result.numbers[i] == 0)
            ++trailingZeroes;
        else
            break;
    
    if (trailingZeroes != 0) {
        LongNumber copy = result;
        delete [] result.numbers;
        result.length = copy.length - trailingZeroes;
        result.numbers = new int [result.length];
        for (int i = 0; i < result.length; i++)
            result.numbers[i] = copy.numbers[i];
    }
    
    return result;
}

void LongNumber::multiply_by_digit(int digit) {
    if (digit < 0 || digit > 9)
        return;
    
    if (digit == 0) {
        delete [] numbers;
        length = 1;
        numbers = new int[1];
        numbers[0] = 0;
        return;
    }
    
    int carry = 0;
    for (int i = 0; i < length; i++ ) {
        int result = numbers[i] * digit + carry;
        carry = result / 10;
        result %= 10;
        numbers[i] = result;
    }
    if (carry != 0) {
        LongNumber copy = *this;
        delete [] numbers;
        length = copy.length + 1;
        numbers = new int[length];
        for (int i = 0; i < copy.length; i++)
            numbers[i] = copy.numbers[i];
        numbers[length - 1] = carry;
    }
}

void LongNumber::multiply_by_ten() {
    if (*this == LongNumber())
        return;
    
    LongNumber copy = *this;
    delete [] numbers;
    length = copy.length + 1;
    numbers = new int[length];
    for (int i = 0; i < copy.length; i++)
        numbers[i + 1] = copy.numbers[i];
    numbers[0] = 0;
}

std::pair<LongNumber, LongNumber> LongNumber::divide_abs_values(const LongNumber& x, const LongNumber& y) const {
    if (y == LongNumber())
        return {LongNumber(), LongNumber()}; // error: division ZERO
    
    LongNumber numerator = x;
    numerator.sign = POSITIVE;
    LongNumber denominator = y;
    denominator.sign = POSITIVE;
    
    LongNumber current = LongNumber();
    LongNumber result = LongNumber();
    
    char* digit = new char[2];
    digit[1] = '\0';
    
    for (int i = numerator.length - 1; i >= 0; i--) {
        current.multiply_by_ten();
        digit[0] = '0' + numerator.numbers[i];
        current = current + LongNumber(digit);
        
        int div = 0;
        while (current > denominator || current == denominator) {
            ++div;
            current = current - denominator;
        }
        
        result.multiply_by_ten();
        digit[0] = '0' + div;
        result = result + LongNumber(digit);
    }
    
    delete [] digit;
    
    return {result, current};
}

// ----------------------------------------------------------
// FRIENDLY
// ----------------------------------------------------------
namespace biv {
	std::ostream& operator << (std::ostream &os, const LongNumber& x) {
        if (x.is_negative())
            os << '-';
        
        int len = x.get_digits_number();
        for (int i = 0; i < len; ++i)
            os << x.get_rank_number(i);
        
        return os;
	}
}
