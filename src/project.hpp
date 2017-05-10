//
// Created by Kevin on 5/6/2017.
//

#ifndef PROJECT_H
#define PROJECT_H

#include <list>
#include "task.hpp"
#include "../include/json.hpp"
#include "text/color.h"

using json = nlohmann::json;

namespace project_ns {
    class project {
    private:
        std::string name;
        std::list<task_ns::task> tasks;
        color_ns::color_t color;
    public:
        //constructors
        project();
        project(std::string name);
        project(std::string name, color_ns::color_t color);

        //getters
        const std::string &get_name() const;
        const std::list<task_ns::task> &get_tasks() const;
        const color_ns::color_t &get_color() const;

        //setters
        void set_tasks(std::list<task_ns::task> tasks);
        void set_name(std::string name);
        void set_color(color_ns::color_t color);

        //mutators
        void add(task_ns::task t);

        void remove(task_ns::task t);
        void remove(const bool (* predicate)(task_ns::task));
        void remove_complete();
        void remove_incomplete();

        //strings
        std::string to_string();
        std::string to_fancy_string();
    };

    //json conversion for projects
    void to_json(json &j, const project &p);
    void from_json(const json &j, project &p);
}

#endif
