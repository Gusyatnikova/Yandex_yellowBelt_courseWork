//
// Created by Gusiatnikova Natalya on 05.08.2020.
//

#include "date.h"
#include <tuple>
#include <iomanip>

Date::Date(uint year, uint month, uint day) :
        year_(year), month_(month), day_(day) {
    //the correctness of the arguments is guaranteed
}

uint Date::getYear() const {
    return year_;
}

uint Date::getMonth() const {
    return month_;
}

uint Date::getDay() const {
    return day_;
}


Date::Date() = default;

Date ParseDate(std::istream &is) {
    uint year, month, day;
    char delim;
    is >> year >> delim >> month >> delim >> day;
    return Date(year, month, day);
}

std::ostream &operator<<(std::ostream &os, const Date &date) {
    os << std::setw(4) << std::setfill('0') << date.getYear() << "-"
       << std::setw(2) << std::setfill('0') << date.getMonth() << "-"
       << std::setw(2) << std::setfill('0') << date.getDay();
    return os;
}

std::string Date::ToString() const {
    std::ostringstream ss;
    ss << *this;
    return ss.str();
}

bool Date::operator==(const Date &rhs) const {
    return (year_ == rhs.getYear() &&
            month_ == rhs.getMonth() &&
            day_ == rhs.getDay());
}

bool Date::operator!=(const Date &rhs) const {
    return !operator==(rhs);
}

bool Date::operator<(const Date &rhs) const {
    return std::make_tuple(year_, month_, day_)
           < std::make_tuple(rhs.getYear(), rhs.getMonth(), rhs.getDay());
}

bool Date::operator>(const Date &rhs) const {
    return !operator<(rhs);
}

bool Date::operator<=(const Date &rhs) const {
    return operator==(rhs) || operator<(rhs);
}

bool Date::operator>=(const Date &rhs) const {
    return operator==(rhs) || operator>(rhs);
}
