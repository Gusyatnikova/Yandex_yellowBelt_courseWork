#include "date_comparasion_node.h"

DateComparisonNode::DateComparisonNode(const Comparison &cmp, Date date)
        : cmp_(cmp), date_(date) {}

bool DateComparisonNode::Evaluate(const Date &date, const std::string &event) const {
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
