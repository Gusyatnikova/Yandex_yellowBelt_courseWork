#pragma once

#include "../node.h"

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
