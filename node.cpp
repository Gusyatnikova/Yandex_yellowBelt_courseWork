#include "node.h"

bool EmptyNode::Evaluate(const Date &date, const std::string &event) const {
    return true;
}

DateComparisonNode::DateComparisonNode(const Comparison &cmp, Date date)
        : cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    // date_ cmp_ date
    switch (cmp_) {
        case Comparison::Equal :
            return date == date_;
        case Comparison::Less :
            return date < date_;
        case Comparison::Greater :
            if (date == date_) return false;
            return date > date_;
        case Comparison::NotEqual :
            return date != date_;
        case Comparison::GreaterOrEqual :
            return date >= date_;
        case Comparison::LessOrEqual :
            return date <= date_;
    }
}

EventComparisonNode::EventComparisonNode(const Comparison &cmp, const std::string &event) :
        cmp_(cmp), event_(event) {}

bool EventComparisonNode::Evaluate(const Date &date, const std::string &event) const {
    switch (cmp_) {
        case Comparison::Equal :
            return event == event_;
        case Comparison::Less :
            return event < event_;
        case Comparison::Greater :
            return event > event_;
        case Comparison::NotEqual :
            return event != event_;
        case Comparison::GreaterOrEqual :
            return event >= event_;
        case Comparison::LessOrEqual :
            return event <= event_;
    }
}

LogicalOperationNode::LogicalOperationNode(const LogicalOperation logic_op,
                                           std::shared_ptr<Node> lhs,
                                           std::shared_ptr<Node> rhs) :
        logic_op_(logic_op), lhs_(lhs), rhs_(rhs) {}

bool LogicalOperationNode::Evaluate(const Date &date, const std::string &event) const {
    switch (logic_op_) {
        case LogicalOperation::And : {
            return (lhs_->Evaluate(date, event) && rhs_->Evaluate(date, event));
        }
        case LogicalOperation::Or : {
            return (lhs_->Evaluate(date, event) || rhs_->Evaluate(date, event));
        }
    }
}
