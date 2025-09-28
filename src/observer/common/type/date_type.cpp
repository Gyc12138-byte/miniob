#include "common/type/date_type.h"
#include "common/value.h"
#include <sstream>
#include <iomanip>

bool DateType::is_leap_year(int year) {
    if (year % 4 != 0) return false;
    if (year % 100 != 0) return true;
    return (year % 400 == 0);
}

bool DateType::check_date(int year, int month, int day) {
    if (year < 0 || year > 9999) return false;
    if (month < 1 || month > 12) return false;
    
    int days_in_month[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    
    if (is_leap_year(year)) {
        days_in_month[1] = 29;
    }
    
    return (day >= 1 && day <= days_in_month[month - 1]);
}

int DateType::compare(const Value &left, const Value &right) const {
    return common::compare_int((void*)&left.value_.int_value_, (void*)&right.value_.int_value_);
}

RC DateType::to_string(const Value &val, std::string &result) const {
    std::stringstream ss;
    int date_value = val.value_.int_value_;
    
    int year = date_value / 10000;
    int month = (date_value % 10000) / 100;
    int day = date_value % 100;
    
    ss << std::setw(4) << std::setfill('0') << year << "-"
       << std::setw(2) << std::setfill('0') << month << "-"
       << std::setw(2) << std::setfill('0') << day;
    
    result = ss.str();
    return RC::SUCCESS;
}

RC DateType::cast_to(const Value &val, AttrType type, Value &result) const {
    switch (type) {
        case AttrType::CHARS: {
            std::string date_str;
            to_string(val, date_str);
            result.set_string(date_str.c_str());
            return RC::SUCCESS;
        }
        default:
            return RC::UNIMPLEMENTED;
    }
}