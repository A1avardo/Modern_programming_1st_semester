#pragma once

#include <iostream>

namespace biv {

    class LongNumber {
    private:
        int* numbers;
        int length;
        int sign;
		
    public:
        LongNumber();
        LongNumber(const char* const str);
        LongNumber(const LongNumber& x);
        LongNumber(LongNumber&& x);
        
        ~LongNumber();
        
        LongNumber& operator = (const char* const str);
        LongNumber& operator = (const LongNumber& x);
        LongNumber& operator = (LongNumber&& x);
        
        bool operator == (const LongNumber& x) const;
        bool operator != (const LongNumber& x) const;
        bool operator > (const LongNumber& x) const;
        bool operator < (const LongNumber& x) const;
        
        LongNumber operator + (const LongNumber& x) const;
        LongNumber operator - (const LongNumber& x) const;
        LongNumber operator * (const LongNumber& x) const;
        LongNumber operator / (const LongNumber& x) const;
        LongNumber operator % (const LongNumber& x) const;
        
        int get_digits_number() const noexcept;
        int get_rank_number(const int rank) const;
        bool is_negative() const noexcept;
        
        friend std::ostream& operator << (std::ostream &os, const LongNumber& x);
        
        private:
        int get_length(const char* const str) const noexcept;
        
        enum class AbsValuesCompare {
            LESS,
            GREATER,
            EQUAL
        };
        AbsValuesCompare compare_abs_values(const LongNumber& x, const LongNumber& y) const;
        
        LongNumber add_abs_values(const LongNumber& x, const LongNumber& y) const;
        LongNumber subtract_abs_values(const LongNumber& big, const LongNumber& small) const;
        
        void multiply_by_digit(int digit);
        void multiply_by_ten();
        
        std::pair<LongNumber, LongNumber> divide_abs_values(const LongNumber& x, const LongNumber& y) const;
	};
}
