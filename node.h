#pragma once
//
// Created by Gusiatnikova Natalya on 05.08.2020.
//

#include "date.h"
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

protected:

};

class EmptyNode : public Node {
    bool Evaluate(const Date &date, const std::string &event) const override;
};

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison &cmp, Date date);

    bool Evaluate(const Date &date, const std::string &event) const override;

    Date GetDate();

private:
    const Date date_;
    const Comparison cmp_;
};

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison &cmp, const std::string &event);

    bool Evaluate(const Date &date, const std::string &event) const override;

private:
    const std::string event_;
    const Comparison cmp_;
};

class LogicalOperationNode : public Node {
public:
    LogicalOperationNode(const LogicalOperation logic_op,
                         std::shared_ptr<Node> sptr_lhs,
                         std::shared_ptr<Node> sptr_rhs);

    bool Evaluate(const Date &date, const std::string &event) const override;

private:
    const LogicalOperation logic_op_;
    const std::shared_ptr<Node> lhs_;
    const std::shared_ptr<Node> rhs_;
};
