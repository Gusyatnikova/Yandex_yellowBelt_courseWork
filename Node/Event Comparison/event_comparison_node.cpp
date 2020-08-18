#include "event_comparison_node.h"

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