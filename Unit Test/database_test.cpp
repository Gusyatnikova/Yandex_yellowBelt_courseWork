#include "../Database/database.h"
#include "test_runner.h"
#include "../Condition Parser/condition_parser.h"

using namespace std;

void TestDbAdd() {
    {
        Database db;
        const map<Date, vector<string>> expectation = {{{1111, 2, 3}, {"event"}}};
        db.Add({1111, 2, 3}, "event");
        AssertEqual(db.GetDb(), expectation, "TestDbAdd 1");
    }
    {
        Database db;
        const map<Date, vector<string>> expectation = {
                {{1111, 2,  3}, {"event 1"}},
                {{1122, 12, 5}, {"event 2"}}
        };
        db.Add({1111, 2, 3}, "event 1");
        db.Add({1122, 12, 5}, "event 2");
        AssertEqual(db.GetDb(), expectation, "TestDbAdd 2");
    }
    {
        Database db;
        const map<Date, vector<string>> expectation = {
                {{1111, 2, 3}, {"event 1"}},
                {{1111, 2, 3}, {"event 1"}}
        };
        db.Add({1111, 2, 3}, "event 1");
        db.Add({1111, 2, 3}, "event 1");
        AssertEqual(db.GetDb(), expectation, "TestDbAdd 3");
    }
    {
        Database db;
        const map<Date, vector<string>> expectation = {
                {{1111, 2, 3}, {"event 1", "event 2"}}
        };
        db.Add({1111, 2, 3}, "event 1");
        db.Add({1111, 2, 3}, "event 2");
        AssertEqual(db.GetDb(), expectation, "TestDbAdd 4");
    }
    {
        Database db;
        const map<Date, vector<string>> expectation = {
                {{1111, 2, 3}, {"", " *"}}
        };
        db.Add({1111, 2, 3}, "");
        db.Add({1111, 2, 3}, " *");
        AssertEqual(db.GetDb(), expectation, "TestDbAdd 5");
    }
    {
        Database db;
        const map<Date, vector<string>> expectation = {
                {{1111, 2, 3}, {"event 1", "event 2"}},
                {{1111, 3, 3}, {"event 1", "event 2"}}
        };
        db.Add({1111, 2, 3}, "event 1");
        db.Add({1111, 2, 3}, "event 2");
        db.Add({1111, 3, 3}, "event 1");
        db.Add({1111, 3, 3}, "event 2");
        AssertEqual(db.GetDb(), expectation, "TestDbAdd 6");
    }

};

void TestDbPrint() {
    Database db;
    db.Add({111, 1, 1}, "event 3 - 1");
    db.Add({111, 1, 1}, "event 1 - 1");
    db.Add({111, 1, 1}, "event 1 - 2");
    db.Add({11, 5, 1}, "event 2 - 1");
    db.Add({2111, 2, 1}, "event 3 - 1");
    string expected = "0011-05-01 event 2 - 1\n"
                      "0111-01-01 event 3 - 1\n"
                      "0111-01-01 event 1 - 1\n"
                      "0111-01-01 event 1 - 2\n"
                      "2111-02-01 event 3 - 1";
    stringstream result;
    db.Print(result);
    for (auto i = 0; i != expected.size(); ++i) {
        AssertEqual(result.str()[i], expected[i], "TestDbPrint " + to_string(i));
    }
}

void TestDbRemoveIf() {
    {
        //empty db
        Database empty_db;
        istringstream is("date == 2010-11-1");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date &date, const string &event) {
            return condition->Evaluate(date, event);
        };
        AssertEqual(empty_db.RemoveIf(predicate), 0, "TestDbRemoveIf 1");
        AssertEqual(empty_db.GetDb(), map<Date, vector<string>>(), "TestDbRemoveIf 2");
    }
    {
        //not such date and event
        Database db;
        db.Add({111, 1, 1}, "event 3 - 1");
        db.Add({111, 1, 1}, "event 1 - 1");
        db.Add({111, 1, 1}, "event 1 - 2");
        db.Add({11, 5, 1}, "event 2 - 1");
        db.Add({2111, 2, 1}, "event 3 - 1");
        map<Date, vector<string>> initial_map = db.GetDb();
        istringstream is(R"(date == 111-1-1 AND event == "11")");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date &date, const string &event) {
            return condition->Evaluate(date, event);
        };
        AssertEqual(db.RemoveIf(predicate), 0, "TestDbRemoveIf 3");
        AssertEqual(db.GetDb(), initial_map, "TestDbRemoveIf 4");
    }
    {
        //date and event are exist in db
        Database db;
        db.Add({111, 1, 1}, "event 3 - 1");
        db.Add({111, 1, 1}, "event 1 - 1");
        db.Add({111, 1, 1}, "event 1 - 2");
        db.Add({11, 5, 1}, "event 2 - 1");
        db.Add({2111, 2, 1}, "event 3 - 1");
        istringstream is(R"(date == 111-1-1 AND event > "event 1 - 1")");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date &date, const string &event) {
            return condition->Evaluate(date, event);
        };
        map<Date, vector<string>> expected_map = {
                {{111,  1, 1}, {"event 1 - 1"}},
                {{11,   5, 1}, {"event 2 - 1"}},
                {{2111, 2, 1}, {"event 3 - 1"}}
        };
        AssertEqual(db.RemoveIf(predicate), 2, "TestDbRemoveIf 5");
        AssertEqual(db.GetDb(), expected_map, "TestDbRemoveIf 6");
    }
    {
        //only date in condition
        Database db;
        db.Add({111, 1, 1}, "event 3 - 1");
        db.Add({111, 1, 1}, "event 1 - 1");
        db.Add({111, 1, 1}, "event 1 - 2");
        db.Add({11, 5, 1}, "event 2 - 1");
        db.Add({2111, 2, 1}, "event 3 - 1");
        istringstream is(R"(date == 111-1-1)");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date &date, const string &event) {
            return condition->Evaluate(date, event);
        };
        map<Date, vector<string>> expected_map = {
                {{11,   5, 1}, {"event 2 - 1"}},
                {{2111, 2, 1}, {"event 3 - 1"}}
        };
        AssertEqual(db.RemoveIf(predicate), 3, "TestDbRemoveIf 7");
        AssertEqual(db.GetDb(), expected_map, "TestDbRemoveIf 8");
    }
    {
        //only event in condition (all date where exist this event must be deleted)
        Database db;
        db.Add({111, 1, 1}, "event 3 - 1");
        db.Add({111, 1, 1}, "event 1 - 1");
        db.Add({111, 1, 1}, "event 1 - 2");
        db.Add({11, 5, 1}, "event 2 - 1");
        db.Add({2111, 2, 1}, "event 3 - 1");
        istringstream is(R"(event == "event 3 - 1")");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date &date, const string &event) {
            return condition->Evaluate(date, event);
        };
        map<Date, vector<string>> expected_map = {
                {{111,  1, 1}, {"event 1 - 1", "event 1 - 2"}},
                {{11,   5, 1}, {"event 2 - 1"}}
        };
        AssertEqual(db.RemoveIf(predicate), 2, "TestDbRemoveIf 9");
        AssertEqual(db.GetDb(), expected_map, "TestDbRemoveIf 10");
    }
    {
        //event and date is empty (clear db)
        Database db;
        db.Add({111, 1, 1}, "event 3 - 1");
        db.Add({111, 1, 1}, "event 1 - 1");
        db.Add({111, 1, 1}, "event 1 - 2");
        db.Add({11, 5, 1}, "event 2 - 1");
        db.Add({2111, 2, 1}, "event 3 - 1");
        istringstream is(R"()");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date &date, const string &event) {
            return condition->Evaluate(date, event);
        };
        map<Date, vector<string>> expected_map = {};
        AssertEqual(db.RemoveIf(predicate), 5, "TestDbRemoveIf 11");
        AssertEqual(db.GetDb(), expected_map, "TestDbRemoveIf 12");
    }
}

void TestDbFindIf() {
    {
        //empty db
        Database db;
        istringstream is(R"(date == 111-1-1)");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date &date, const string &event) {
            return condition->Evaluate(date, event);
        };
        vector<string> result = db.FindIf(predicate);
        AssertEqual(result.size(), 0, "TestDbFindIf 1");
    }
    {
        //event is empty -> find all events per day
        Database db;
        db.Add({111, 1, 1}, "event 3 - 1");
        db.Add({111, 1, 1}, "event 1 - 1");
        db.Add({111, 1, 1}, "event 1 - 2");
        db.Add({11, 5, 1}, "event 2 - 1");
        db.Add({2111, 2, 1}, "event 3 - 1");
        istringstream is(R"(date == 111-1-1)");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date &date, const string &event) {
            return condition->Evaluate(date, event);
        };
        vector<string> found = db.FindIf(predicate);
        vector<string> expected = {
                "0111-01-01 event 3 - 1",
                "0111-01-01 event 1 - 1",
                "0111-01-01 event 1 - 2"
        };
        AssertEqual(found, expected, "TestDbFind 2");
    }
    {
        //date is empty -> find correct events from all days
        Database db;
        db.Add({111, 1, 1}, "event 3 - 1");
        db.Add({111, 1, 1}, "event 1 - 1");
        db.Add({111, 1, 1}, "event 1 - 2");
        db.Add({11, 5, 1}, "event 2 - 1");
        db.Add({2111, 2, 1}, "event 3 - 1");
        istringstream is(R"(event == "event 3 - 1")");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date &date, const string &event) {
            return condition->Evaluate(date, event);
        };
        vector<string> found = db.FindIf(predicate);
        vector<string> expected = {
                "0111-01-01 event 3 - 1",
                "2111-02-01 event 3 - 1"
        };
        AssertEqual(found, expected, "TestDbFind 3");
    }
    {
        //date and event are not empty
        Database db;
        db.Add({111, 1, 1}, "event 3 - 1");
        db.Add({111, 1, 1}, "event 1 - 1");
        db.Add({111, 1, 1}, "event 1 - 2");
        db.Add({2222, 5, 1}, "event 2 - 1");
        db.Add({2111, 2, 1}, "event 3 - 1");
        istringstream is(R"(date > 111-1-1 OR event == "event 3 - 1")");
        auto condition = ParseCondition(is);
        auto predicate = [condition](const Date &date, const string &event) {
            return condition->Evaluate(date, event);
        };
        vector<string> found = db.FindIf(predicate);
        vector<string> expected = {
                "0111-01-01 event 3 - 1",
                "2111-02-01 event 3 - 1",
                "2222-05-01 event 2 - 1"
        };
        AssertEqual(found, expected, "TestDbFind 4");
    }
}

void TestDbLast() {
    {
        //empty db
        Database db;
        AssertEqual(db.Last({1111,1,1}), "No entries", "TestDbLast 1");
    }
    {
        //date and event are not empty
        Database db;
        db.Add({111, 1, 1}, "event 3 - 1");
        db.Add({111, 1, 1}, "event 1 - 1");
        db.Add({111, 1, 1}, "event 1 - 2");
        db.Add({2222, 5, 1}, "event 2 - 1");
        db.Add({2111, 2, 1}, "event 3 - 1");
        db.Add({2111, 2, 1}, "event 3 - 2");
        AssertEqual(db.Last({111, 1, 1}), "0111-01-01 event 1 - 2", "TestDbLast 2");
        AssertEqual(db.Last({2112, 9, 9}), "2111-02-01 event 3 - 2", "TestDbLast 2");
        AssertEqual(db.Last({1, 9, 9}), "No entries", "TestDbLast 2");
    }
}
