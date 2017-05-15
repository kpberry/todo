//
// Created by Kevin on 5/6/2017.
//

#ifndef PROJECT_H
#define PROJECT_H

#include "task.hpp"
#include "../include/json.hpp"
#include "text/color.hpp"

namespace project_ns {
    class project {
    private:
        std::string name;
        std::vector<task_ns::task> tasks;
        color_ns::color_t color;
    public:
        //constructors
        project();
        project(std::string name);
        project(std::string name, color_ns::color_t color);

        //getters
        const std::string &get_name() const;
        const std::vector<task_ns::task> &get_tasks() const;
        const color_ns::color_t &get_color() const;

        //setters
        void set_tasks(std::vector<task_ns::task> tasks);
        void set_name(std::string name);
        void set_color(color_ns::color_t color);

        //mutators
        void advance_task(int i);
        void undo_task(int task_number);
        void set_status(int task_number, task_ns::task::STATUS status);

        void add(task_ns::task t);

        void remove(int task_number);
        void remove(const bool (* predicate)(task_ns::task));
        void remove_complete();
        void remove_started();
        void remove_unstarted();
        void remove_incomplete();

        void reverse_tasks();

        //strings
        std::string to_string();
        std::string to_fancy_string();
        uint64_t get_longest_task_length();

        //sorts
        void sort_tasks_alphabetically();
        void sort_tasks_by_status();
        void sort_tasks(bool (*comparator)(
                const task_ns::task &, const task_ns::task &
        ));
        void sort_tasks_by_modified();
        void sort_tasks_by_created();
    };

    //json conversion for projects
    void to_json(nlohmann::json &j, const project &p);
    void from_json(const nlohmann::json &j, project &p);
}

#endif
