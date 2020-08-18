#pragma once

#include "../node.h"

class DateComparisonNode : public Node {
public:
    DateComparisonNode(const Comparison &cmp, Date date);

    bool Evaluate(const Date &date, const std::string &event) const override;

    Date GetDate();

private:
    const Date date_;
    const Comparison cmp_;
};