#ifndef __COMMON_TYPE_DATE_TYPE_H__
#define __COMMON_TYPE_DATE_TYPE_H__

#include "common/type/data_type.h"
#include "common/lang/comparator.h"

class DateType : public DataType {
public:
    DateType() = default;
    virtual ~DateType() = default;

    int compare(const Value &left, const Value &right) const override;
    RC to_string(const Value &val, std::string &result) const override;
    RC cast_to(const Value &val, AttrType type, Value &result) const override;
    
    // 日期合法性检查函数
    static bool check_date(int year, int month, int day);
    static bool is_leap_year(int year);
};

#endif // __COMMON_TYPE_DATE_TYPE_H__