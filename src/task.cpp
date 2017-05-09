//
// Created by Kevin on 5/2/2017.
//

#include <iostream>
#include "task.hpp"
#include "text/string_formatter.h"

using namespace std;
using namespace task_ns;
using nlohmann::json;

namespace task_ns {
    void to_json(json &j, const task& t) {
        j = json{
                {"name",     t.getName()},
                {"status",   t.getStatus()},
                {"modified", t.getModified()},
                {"created",  t.getCreated()}
        };
    }

    void from_json(const json &j, task &t) {
        t.set_name(j.at("name").get<std::string>());
        t.set_status(j.at("status").get<task::STATUS>());
        t.set_created(j.at("created").get<time_t>());
        t.set_modified(j.at("modified").get<time_t>());
    }
}

task::task() {
    this->name = name;
    this->status = unstarted;
    time(&modified);
    time(&created);
}

task::task(string name) {
    this->name = name;
    this->status = unstarted;
    time(&modified);
    time(&created);
}

void task::complete() {
    this->status = completed;
    time(&modified);
}

void task::start() {
    this->status = started;
    time(&modified);
}

void task::undo() {
    if (status == completed) {
        status = started;
    } else if (status == started) {
        status = unstarted;
    }
    time(&modified);
}

void task::set_created(time_t created) {
    this->created = created;
}

void task::set_modified(time_t modified) {
    this->modified = modified;
};

void task::set_name(std::string name) {
    this->name = name;
};

void task::set_status(task::STATUS status) {
    this->status = status;
};

string task::to_string() const {
    struct tm* created_time = localtime(&created);
    char created_date[20];
    strftime(created_date, sizeof(created_date), "%m-%d-%Y", created_time);

    struct tm* modified_time = localtime(&created);
    char modified_date[20];
    strftime(modified_date, sizeof(modified_date), "%m-%d-%Y", modified_time);

    string status_strings[] = {"unstarted", "started", "complete"};
    string result = name + " | status: " + status_strings[status]
                    + " | created: " + created_date + " | modified: "
                    + modified_date;
    return result;
}

string task::to_fancy_string() const {
    return to_fancy_string(name.length());
}

string task::to_fancy_string(unsigned long first_length) const {
    struct tm* created_time = localtime(&created);
    char created_date[20];
    strftime(created_date, sizeof(created_date), "%m-%d-%Y", created_time);

    struct tm* modified_time = localtime(&created);
    char modified_date[20];
    strftime(modified_date, sizeof(modified_date), "%m-%d-%Y", modified_time);

    string status_strings[] = {
            rgb_string("unstarted", 200, 0, 0),
            rgb_string("started  ", 200, 200, 0),
            rgb_string("complete ", 0, 200, 0)
    };

    string result = rgb_string(name, 100, 200, 150) + std::string(first_length - name.length(), ' ')
                    + " | status: " + status_strings[status]
                    + " | created: " + created_date + " | modified: "
                    + modified_date;
    return result;
}

task::~task() {

}

bool task::is_complete()const {
    return status == completed;
}

bool task::is_started() {
    return status == started;
}

bool task::is_unstarted() {
    return status == unstarted;
}

bool task::operator==(const task t) {
    return this->name == t.name;
}

task::STATUS task::getStatus() const {
    return status;
}

const string &task::getName() const {
    return name;
}

time_t task::getModified() const {
    return modified;
}

time_t task::getCreated() const {
    return created;
}
