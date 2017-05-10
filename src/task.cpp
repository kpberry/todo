//
// Created by Kevin on 5/2/2017.
//

#include <iostream>
#include "task.hpp"
#include "text/string_formatter.hpp"

using namespace std;
using namespace task_ns;
using nlohmann::json;
using namespace color_ns;

namespace task_ns {
    void to_json(json &j, const task& t) {
        j = json{
                {"name", t.get_name()},
                {"status", t.get_status()},
                {"modified", t.get_modified()},
                {"created", t.get_created()}
        };
    }

    void from_json(const json &j, task &t) {
        t.set_name(j.at("name").get<std::string>());
        t.set_status(j.at("status").get<task::STATUS>());
        t.set_created(j.at("created").get<time_t>());
        t.set_modified(j.at("modified").get<time_t>());
    }

    static constexpr color_ns::color_t unstarted_color = {200, 0, 0};
    static constexpr color_ns::color_t started_color = {200, 200, 0};
    static constexpr color_ns::color_t completed_color = {0, 200, 0};
    static constexpr color_ns::color_t title_color = {100, 200, 150};

    static string status_strings[] = {
            "unstarted", "started", "complete"
    };
    static string color_status_strings[] = {
            rgb_string("unstarted", unstarted_color),
            rgb_string("started  ", started_color),
            rgb_string("complete ", completed_color)
    };
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
    //sets the modified time
    time(&modified);
}

void task::start() {
    this->status = started;
    //sets the modified time
    time(&modified);
}

void task::undo() {
    if (status == completed) {
        status = started;
    } else if (status == started) {
        status = unstarted;
    }
    //sets the modified time
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

string time_to_string(time_t time) {
    struct tm* local_time = localtime(&time);
    char time_string[20];
    strftime(time_string, sizeof(time_string), "%m-%d-%Y", local_time);
    return string(time_string);
}

string task::to_string() const {
    string result = name
                    + " | status: " + status_strings[status]
                    + " | created: " + time_to_string(created)
                    + " | modified: " + time_to_string(modified);
    return result;
}

string task::to_fancy_string() const {
    return to_fancy_string(name.length());
}

string task::to_fancy_string(unsigned long first_length) const {
    string spacing = std::string(first_length - name.length(), ' ');
    string result = rgb_string(name, title_color) + spacing
                      + " | status: " + color_status_strings[status]
                      + " | created: " + time_to_string(created)
                      + " | modified: " + time_to_string(modified);
    return result;
}

bool task::is_complete() const {
    return status == completed;
}

bool task::is_started() const {
    return status == started;
}

bool task::is_unstarted() const {
    return status == unstarted;
}

bool task::operator==(const task t) {
    return this->name == t.name;
}

const task::STATUS task::get_status() const {
    return status;
}

const string &task::get_name() const {
    return name;
}

const time_t task::get_modified() const {
    return modified;
}

const time_t task::get_created() const {
    return created;
}
