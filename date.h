#pragma once
//
// Created by Gusiatnikova Natalya on 05.08.2020.
//

#include <iostream>

using uint = unsigned int;

class Date {
private:
    uint year_;
public:
    Date(uint year, uint month, uint day);

    Date();

    uint getYear() const;

    uint getMonth() const;

    uint getDay() const;

    bool operator<(const Date &rhs) const;

    bool operator>(const Date &rhs) const;

    bool operator==(const Date &rhs) const;

    bool operator!=(const Date &rhs) const;

    bool operator<=(const Date &rhs) const;

    bool operator>=(const Date &rhs) const;

    std::string ToString() const;

private:
    //0 to 9999
    uint month_; //1 to 12
    uint day_; //1 to 31
};

Date ParseDate(std::istream &is);

std::ostream &operator<<(std::ostream &os, const Date &date);



