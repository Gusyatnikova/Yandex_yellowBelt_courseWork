#pragma once

#include "../Node/node.h"
#include "../Node/Empty/empty_node.h"
#include "../Node/Date Comparison/date_comparasion_node.h"
#include "../Node/Event Comparison/event_comparison_node.h"
#include "../Node/Logical Operation/logical_operaion_node.h"

#include <memory>
#include <iostream>

using namespace std;

shared_ptr<Node> ParseCondition(istream &is);

void TestParseCondition();

