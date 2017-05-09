//
// Created by Kevin on 5/6/2017.
//

#include "project.hpp"
#include "text/string_formatter.h"

using namespace std;
using namespace project_ns;
using namespace task_ns;

namespace project_ns {
    void to_json(json& j, const project& p) {
        j = json{
                {"name", p.getName()},
                {"tasks", p.getTasks()}
        };
    }
    void from_json(const json& j, project& p) {
        p.set_name(j.at("name").get<std::string>());
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

string project::to_string() {
    string result = name + "\n";
    for (const task t : tasks) {
        result += "\t" + t.to_string() + "\n";
    }
    return result;
}

string project::to_fancy_string() {
    string result = rgb_string(name + "\n", 100, 160, 255);
    uint64_t length = 0;
    for (const task t : tasks) {
        if (t.getName().length() > length) {
            length = t.getName().length();
        }
    }
    int count = 0;
    for (const task t : tasks) {
        result += "\t" + std::to_string(++count) + ": " + t.to_fancy_string(length) + "\n";
    }
    return result;
}

void project::set_name(string name) {
    this->name = name;
}

const string &project::getName() const {
    return name;
}

void project::setName(const string &name) {
    this->name = name;
}

const list<task> &project::getTasks() const {
    return tasks;
}

void project::set_tasks(std::list<task_ns::task> tasks) {
    this->tasks = tasks;
}

project::project(std::string name) {
    this->name = name;
}

project::project() {
    this->name = "";
}
