#pragma once

#include "../node.h"

class EventComparisonNode : public Node {
public:
    EventComparisonNode(const Comparison &cmp, const std::string &event);

    bool Evaluate(const Date &date, const std::string &event) const override;

private:
    const std::string event_;
    const Comparison cmp_;
};