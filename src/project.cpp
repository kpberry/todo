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
using json = nlohmann::json;

namespace project_ns {
    /**
     * Serializes a project to a json object
     * @param j the object which will store the serialized project
     * @param p the project to be serialized
     */
    void to_json(json& j, const project& p) {
        j = json{
                {"name", p.get_name()},
                {"tasks", p.get_tasks()},
                {"color", p.get_color()}
        };
    }

    /**
     * Initializes a project from a json object
     * @param j the serialized project data
     * @param p the project which will be initialized from the json object
     */
    void from_json(const json& j, project& p) {
        p.set_name(j.at("name").get<std::string>());
        p.set_color(j.at("color").get<color_t>());
        p.set_tasks(j.at("tasks").get<vector<task>>());
    }
}

/**
 * Adds a task to this project at the top level
 * @param t the task to be added
 */
void project::add(task t) {
    this->tasks.push_back(t);
}

/**
 * Removes the task at the specified task number from this project
 * @param task_number the number of the task to be removed
 */
void project::remove(int task_number) {
    this->tasks.erase(this->tasks.begin() + task_number);
}

/**
 * Removes all tasks from this project for which a boolean predicate is met
 * @param predicate returns true for a task which should be removed
 */
void project::remove(const bool (*predicate)(task)) {
    tasks.erase(remove_if(tasks.begin(), tasks.end(), predicate), tasks.end());
}

/**
 * Removes all complete tasks from a project
 */
void project::remove_complete() {
    this->remove([](task t) -> const bool { return t.is_complete(); });
}

/**
 * Removes all non-complete tasks from a project
 */
void project::remove_incomplete() {
    this->remove([](task t) -> const bool { return !t.is_complete(); });
}

/**
 * Sets the name of this project
 * @param name the new name of the project
 */
void project::set_name(string name) {
    this->name = name;
}

/**
 * Gets the name of this project
 * @return the name of this project
 */
const string &project::get_name() const {
    return name;
}

/**
 * Gets the tasks of this project
 * @return a vector of tasks
 */
const vector<task> &project::get_tasks() const {
    return tasks;
}

/**
 * Sets the tasks of this project to a provided vector of tasks
 * @param tasks the new tasks for this project
 */
void project::set_tasks(vector<task_ns::task> tasks) {
    this->tasks = tasks;
}

/**
 * Constructs a new project with the specified name and associated color
 * @param name the name of the project
 * @param color the color to be used for labels, backgrounds, etc.
 */
project::project(std::string name, color_t color) {
    this->name = name;
    this->color = color;
}

/**
 * Constructs a new project with the specified name and the default color white
 * @param name the name of the project
 */
project::project(std::string name) {
    this->name = name;
    this->color = {255, 255, 255};
}

/**
 * Creates a new nameless project with the default color white
 */
project::project() {
    this->name = "";
    this->color = {255, 255, 255};
}

/**
 * Sets the color of a project to a provided color
 * @param color the new color of the project
 */
void project::set_color(color_t color) {
    this->color = color;
}

/**
 * Returns the color of this project
 * @return the color of this project
 */
const color_t &project::get_color() const {
    return this->color;
}

/**
 * Get the length of the name of the task with the longest name length in this
 * project. Used to properly format the fancy string.
 * @return the length of the name of the task with the longest name
 */
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

/**
 * Returns a basic string representing this project
 * @return a string representation of this project
 */
string project::to_string() {
    stringstream result;
    result << name << ":\n";

    int count = 0;
    for (const task t : tasks) {
        result << '\t' << ++count << ": " << t.to_string() << '\n';
    }

    if (count == 0) {
        result << "\tThere are currently no tasks in this project.";
    }

    return result.str();
}

/**
 * Returns a fancy string representing this project
 * @return a fancy colored string representing this project
 */
string project::to_fancy_string() {
    stringstream result;
    result << rgb_string(name, color) << ":\n";
    //get the length of the longest task to ensure that all tasks are nicely
    //aligned, e.g.,
    // 1: do task a | ... | ...
    // 2: task b    | ... | ...
    uint64_t length = get_longest_task_length();
    int count = 0;
    for (const task t : tasks) {
        result << '\t' << ++count << ": " << t.to_fancy_string(length) << '\n';
    }

    if (count == 0) {
        result << "\tThere are currently no tasks in this project.";
    }

    return result.str();
}

/**
 * Remove all of the tasks in this project with the status "started"
 */
void project::remove_started() {
    this->remove([](task t) -> const bool { return t.is_started(); });
}

/**
 * Remove all of the tasks in this project with the status "unstarted"
 */
void project::remove_unstarted() {
    this->remove([](task t) -> const bool { return t.is_unstarted(); });
}

/**
 * Advance a task in this project to the next completion stage
 * @param task_number the task to advance
 */
void project::advance_task(int task_number) {
    tasks[task_number].advance();
}

/**
 * Return a task in this project to the previous completion stage
 * @param task_number
 */
void project::undo_task(int task_number) {
    tasks[task_number].undo();
}

/**
 * Sets the status of a task in this project to a specific status value
 * @param task_number the task to modify
 * @param status the status to use as the new task status
 */
void project::set_status(int task_number, task_ns::task::STATUS status) {
    tasks[task_number].set_status(status);
}

/**
 * Sort the tasks in this project by some boolean comparator, which returns
 * true if one task is less than another by its metric
 * @param comparator a function which determines some less than criterion for
 * tasks
 */
void project::sort_tasks(bool (*comparator) (const task&, const task&)) {
    sort(tasks.begin(), tasks.end(), comparator);
}

/**
 * Sorts all of the tasks in this project alphabetically (lower letters on top)
 */
void project::sort_tasks_alphabetically() {
    sort_tasks([](const task& a, const task& b) -> bool {
        return a.get_name() < b.get_name();
    });
}

/**
 * Sorts all of the tasks in this project by their statuses (less complete tasks
 * on top)
 */
void project::sort_tasks_by_status() {
    sort_tasks([](const task& a, const task& b) -> bool {
        return a.get_status() < b.get_status();
    });
}

/**
 * Sort the tasks in this project by their creation dates (less recently created
 * tasks on top)
 */
void project::sort_tasks_by_created() {
    sort_tasks([](const task& a, const task& b) -> bool {
        return a.get_created() < b.get_created();
    });
}

/**
 * Sort the tasks in this project by their modification dates (less recently
 * created tasks on top)
 */
void project::sort_tasks_by_modified() {
    sort_tasks([](const task& a, const task& b) -> bool {
        return a.get_modified() < b.get_modified();
    });
}

/**
 * Reverse the order of tasks in this project
 */
void project::reverse_tasks() {
    reverse(tasks.begin(), tasks.end());
}