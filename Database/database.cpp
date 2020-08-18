//
// Created by Gusiatnikova Natalya on 05.08.2020.
//

#include "database.h"
#include <algorithm>

using namespace std;

Database::Database() {}

Database::~Database() {
    db_.clear();
}

void Database::Add(const Date &date, const string &event) {
    /*
    if (db_.count(date) == 0 || count(db_.at(date).begin(), db_.at(date).end(), event) == 0) {
        db_[date].push_back(event);
    }
     */
    if (db_.count(date) == 0 || db_for_find_.at(date).count(event) == 0) {
        db_[date].push_back(event);
        db_for_find_[date].insert(event);
    }
}

void Database::Print(std::ostream &os) const {
    for (const auto &pair : db_) {
        for (auto event = pair.second.begin(); event != prev(pair.second.end()); ++event) {
            os << pair.first << " " << *event << endl;
        }
        os << pair.first << " " << *(prev(pair.second.end())) << endl;
    }
}

int Database::RemoveIf(const std::function<bool(const Date &, const std::string &)> &predicate) {
    int removed_events_cnt = 0;
    for (auto it = db_.begin(); it != db_.end();) {
        const auto &date = it->first;
        auto &events = it->second;
        auto new_end = stable_partition(events.begin(), events.end(), [&date, &predicate](const string &event) {
            return !predicate(date, event);
        });

        removed_events_cnt += events.end() - new_end;
        for (auto it = new_end; it != events.end();) {
            db_for_find_.at(date).erase(*it);
            ++it;
        }
        events.erase(new_end, events.end());
        if (events.empty()) {
            it = db_.erase(it);
        } else {
            it++;
        }
    }
    return removed_events_cnt;
}


std::vector<std::string> Database::FindIf(
        const std::function<bool(const Date &, const std::string &)> &predicate) const {
    vector<string> found_dates_to_events;
    for (const auto &pair : db_) {
        const auto &date = pair.first;
        auto it = pair.second.begin();
        while (it != pair.second.end()) {
            it = find_if(it, pair.second.end(), [&date, &predicate](const string &event) {
                return predicate(date, event);
            });
            if (it != pair.second.end()) {
                found_dates_to_events.emplace_back(date.ToString() + " " + *it);
                ++it;
            }
        }
    }
    return found_dates_to_events;
}

std::string Database::Last(const Date &date) const {
    if (date < db_.begin()->first || db_.empty()) {
        return "No entries";
    } else {
        //lower_bound is O(map.size())
        auto lower_it = db_.lower_bound(date);
        return lower_it->first == date ?
               lower_it->first.ToString() + " " + lower_it->second.back() :
               prev(lower_it)->first.ToString() + " " + prev(lower_it)->second.back();
    }
}


//functions for tests
std::map<Date, std::vector<std::string>> Database::GetDb() const {
    return db_;
}

