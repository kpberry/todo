//
// Created by Kevin on 5/6/2017.
//

#include <sstream>
#include "project.hpp"
#include "text/string_formatter.hpp"

using namespace std;
using namespace project_ns;
using namespace task_ns;
using namespace color_ns;

namespace project_ns {
    void to_json(json& j, const project& p) {
        j = json{
                {"name", p.get_name()},
                {"tasks", p.get_tasks()},
                {"color", p.get_color()}
        };
    }

    void from_json(const json& j, project& p) {
        p.set_name(j.at("name").get<std::string>());
        p.set_color(j.at("color").get<color_t>());
        p.set_tasks(j.at("tasks").get<list<task>>());
    }
}

void project::add(task t) {
    this->tasks.push_back(t);
}

void project::remove(task t) {
    this->tasks.remove(t);
}

void project::remove(const bool (*predicate)(task)) {
    this->tasks.remove_if(predicate);
}

void project::remove_complete() {
    this->remove([](task t) -> const bool { return t.is_complete(); });
}

void project::remove_incomplete() {
    this->remove([](task t) -> const bool { return !t.is_complete(); });
}

void project::set_name(string name) {
    this->name = name;
}

const string &project::get_name() const {
    return name;
}

const list<task> &project::get_tasks() const {
    return tasks;
}

void project::set_tasks(std::list<task_ns::task> tasks) {
    this->tasks = tasks;
}

project::project(std::string name, color_t color) {
    this->name = name;
    this->color = color;
}

project::project(std::string name) {
    this->name = name;
    this->color = {255, 255, 255};
}

project::project() {
    this->name = "";
    this->color = {255, 255, 255};
}

void project::set_color(color_t color) {
    this->color = color;
}

const color_t &project::get_color() const {
    return this->color;
}

uint64_t project::get_longest_task_length() {
    uint64_t result = 0;
    for (const task t : tasks) {
        uint64_t length = t.get_name().length();
        if (length > result) {
            result = length;
        }
    }

    return result;
}

string project::to_string() {
    stringstream result;
    result << name << '\n';
    int count = 0;
    for (const task t : tasks) {
        result << '\t' << ++count << ": " << t.to_string() << '\n';
    }
    return result.str();
}

/**
 * @return a colored string representing this project
 */
string project::to_fancy_string() {
    stringstream result;
    result << rgb_string(name, color) << '\n';
    uint64_t length = get_longest_task_length();
    int count = 0;
    for (const task t : tasks) {
        result << '\t' << ++count << ": " << t.to_fancy_string(length) << '\n';
        cout << result.str() << '\n' << '\n';
    }
    return result.str();
}