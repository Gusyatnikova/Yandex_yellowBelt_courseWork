#include "logical_operaion_node.h"

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
