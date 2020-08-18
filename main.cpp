#include "Condition Parser/condition_parser.h"
#include "Database/database.h"
#include "Unit Test/test_runner.h"

#include <stdexcept>

using namespace std;

string ParseEvent(istream &is) {
    string event;
    getline(is, event);
    auto new_end = find_if(event.begin(), event.end(), [] (char c) {return c != ' ';});
    event.erase(event.begin(), new_end);
    return event;
}

void TestParseEvent() {
    {
        istringstream is("event");
        AssertEqual(ParseEvent(is), "event", "Parse event without leading spaces");
    }
    {
        istringstream is("   sport event ");
        AssertEqual(ParseEvent(is), "sport event ", "Parse event with leading spaces");
    }
    {
        istringstream is("  first event  \n  second event");
        vector<string> events;
        events.push_back(ParseEvent(is));
        events.push_back(ParseEvent(is));
        AssertEqual(events, vector<string>{"first event  ", "second event"}, "Parse multiple events");
    }
}

void TestAll() {
    TestRunner tr;
    tr.RunTest(TestParseEvent, "TestParseEvent");
    tr.RunTest(TestParseCondition, "TestParseCondition");
    tr.RunTest(TestDbAdd, "TestDbAdd");
    tr.RunTest(TestDbPrint, "TestDbPrint");
    tr.RunTest(TestDbRemoveIf, "TestDbRemoveIf");
    tr.RunTest(TestDbFindIf, "TestDbFindIf");
    tr.RunTest(TestDbLast, "TestDbLast");
}

int main() {
    TestAll();

    Database db;

    for (string line; getline(cin, line);) {
        istringstream is(line);

        string command;
        is >> command;
        if (command == "Add") {
            const auto date = ParseDate(is);
            const auto event = ParseEvent(is);
            db.Add(date, event);

        } else if (command == "Print") {
            db.Print(cout);
        } else if (command == "Del") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };
            int count = db.RemoveIf(predicate);
            cout << "Removed " << count << " entries" << endl;
        } else if (command == "Find") {
            auto condition = ParseCondition(is);
            auto predicate = [condition](const Date &date, const string &event) {
                return condition->Evaluate(date, event);
            };

            const auto entries = db.FindIf(predicate);
            for (const auto &entry : entries) {
                cout << entry << endl;
            }
            cout << "Found " << entries.size() << " entries" << endl;
        } else if (command == "Last") {
            try {
                cout << db.Last(ParseDate(is)) << endl;
            } catch (invalid_argument &) {
                cout << "No entries" << endl;
            }
        } else if (command.empty()) {
            continue;
        } else {
            throw logic_error("Unknown command: " + command);
        }
    }

    return 0;
}



