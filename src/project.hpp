//
// Created by Kevin on 5/6/2017.
//

#pragma once

#include <list>
#include "task.hpp"
#include "../include/json.hpp"

using json = nlohmann::json;

namespace project_ns {
    class project {
    private:
        std::string name;
        std::list<task_ns::task> tasks;
    public:
        project();
        project(std::string name);
        void add(task_ns::task t);
        void remove_complete();
        void remove_incomplete();
        std::string to_string();
        void remove(task_ns::task t);
        void remove(const bool (* predicate)(task_ns::task));
        const std::string &getName() const;
        void setName(const std::string &name);
        const std::list<task_ns::task> &getTasks() const;
        void set_tasks(std::list<task_ns::task> tasks);
        void set_name(std::string name);

        std::string to_fancy_string();
    };

    void to_json(json &j, const project &p);

    void from_json(const json &j, project &p);
}
