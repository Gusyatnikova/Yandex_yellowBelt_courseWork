#pragma once

#include "../Date/date.h"
#include <memory>

enum class Comparison {
    Less,
    LessOrEqual,
    Greater,
    GreaterOrEqual,
    Equal,
    NotEqual
};

enum class LogicalOperation {
    Or,
    And
};

class Node {
public:
    Node() = default;
    virtual bool Evaluate(const Date &date, const std::string &event) const = 0;
};