#pragma once

#include "../node.h"

class EmptyNode : public Node {
    bool Evaluate(const Date &date, const std::string &event) const override;
};