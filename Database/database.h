#pragma once
//
// Created by Gusiatnikova Natalya on 05.08.2020.
//

#include "../Date/date.h"

#include <string>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <map>
#include <set>


class Database {
public:
    Database();

    void Add(const Date &date, const std::string &event);

    void Print(std::ostream &os) const;

    int RemoveIf(const std::function<bool(const Date &, const std::string &)> &predicate);

    std::vector<std::string> FindIf(
            const std::function<bool(const Date &, const std::string &)> &predicate) const;

    std::string Last(const Date &date) const;

    ~Database();

    //functions for tests
    std::map<Date, std::vector<std::string>> GetDb() const;

private:
    std::map<Date, std::vector<std::string>> db_;
    std::map<Date, std::set<std::string>> db_for_find_;
};

//declarations of tests for Database class
void TestDbAdd();

void TestDbPrint();

void TestDbRemoveIf();

void TestDbFindIf();

void TestDbLast();
