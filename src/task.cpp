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

namespace task_ns {/**
     * Serializes a task to a json object
     * @param j the object which will store the serialized task
     * @param t the task to be serialized
     */
    void to_json(json &j, const task& t) {
        j = json{
                {"name", t.get_name()},
                {"status", t.get_status()},
                {"modified", t.get_modified()},
                {"created", t.get_created()}
        };
    }

    /**
     * Initializes a task from a json object
     * @param j the serialized task data
     * @param t the task which will be initialized from the json object
     */
    void from_json(const json &j, task &t) {
        t.set_name(j.at("name").get<std::string>());
        t.set_status(j.at("status").get<task::STATUS>());
        t.set_created(j.at("created").get<time_t>());
        t.set_modified(j.at("modified").get<time_t>());
    }

    /**
     * Strings representing the possible statuses for a project
     */
    static string status_strings[] = {
            "unstarted", "started", "complete"
    };

    /**
     * Colored strings representing the possible statuses for a project
     */
    static string color_status_strings[] = {
            rgb_string("unstarted", unstarted_color),
            rgb_string("started  ", started_color),
            rgb_string("complete ", completed_color)
    };
}

/**
 * Constructs a new task with an empty name, an unstarted status, and the
 * current time as the modified and created dates
 */
task::task() {
    this->name = "";
    this->status = unstarted;
    time(&modified);
    time(&created);
}

/**
 * Creates a new task with a provided name, an unstarted status, and the
 * current time as the modified and created dates
 * @param name
 */
task::task(string name) {
    this->name = name;
    this->status = unstarted;
    time(&modified);
    time(&created);
}

/**
 * Completes this task and updates its modified date
 */
void task::complete() {
    this->status = completed;
    //sets the modified time
    time(&modified);
}

/**
 * Starts this task and updates its modified date
 */
void task::start() {
    this->status = started;
    //sets the modified time
    time(&modified);
}

/**
 * Returns this task to its previous status and updates its modified date
 */
void task::undo() {
    if (status == completed) {
        status = started;
    } else if (status == started) {
        status = unstarted;
    }
    //sets the modified time
    time(&modified);
}

/**
 * Advances this task to the next status and updates its modified date
 */
void task::advance() {
    if (status == unstarted) {
        start();
    } else if (status == started) {
        complete();
    }
}

/**
 * Sets the creation time for this task to a specified value
 * @param created the time at which the task was created
 */
void task::set_created(time_t created) {
    this->created = created;
}

/**
 * Sets the modified time for this task to a specified value
 * @param modified the tiem at which the task was modified
 */
void task::set_modified(time_t modified) {
    this->modified = modified;
};

/**
 * Sets this task's name to a specified value
 * @param name the new name of this task
 */
void task::set_name(std::string name) {
    this->name = name;
};

/**
 * Sets the status of this task to a specific value
 * @param status the new status of this task
 */
void task::set_status(task::STATUS status) {
    this->status = status;
};

/**
 * Gets a nicely formatted string from a unix timecode
 * @param time the time to be formatted
 * @return a string representing the time in month - day - year format
 */
string time_to_string(time_t time) {
    struct tm* local_time = localtime(&time);
    char time_string[20];
    strftime(time_string, sizeof(time_string), "%m-%d-%Y", local_time);
    return string(time_string);
}

/**
 * Gets a string representing this task, including its name, status, and
 * creation/modification dates
 * @return a string representing this task
 */
string task::to_string() const {
    string result = name
                    + " | status: " + status_strings[status]
                    + " | created: " + time_to_string(created)
                    + " | modified: " + time_to_string(modified);
    return result;
}

/**
 * Gets a fancy string representing this task, including its name, status, and
 * creation/modification dates. Uses the length of the name of the task to
 * determine the padding before the first pipe
 * @return a string representation of this task
 */
string task::to_fancy_string() const {
    return to_fancy_string(name.length());
}

/**
 * Gets a fancy string representing this task, including its name, status, and
 * creation/modification dates. Uses a provided length value to
 * determine the padding before the first pipe
 * @param first_length
 * @return a string representation of this task
 */
string task::to_fancy_string(unsigned long first_length) const {
    string spacing = std::string(first_length - name.length(), ' ');
    string result = rgb_string(name, title_color) + spacing
                      + " | status: " + color_status_strings[status]
                      + " | created: " + time_to_string(created)
                      + " | modified: " + time_to_string(modified);
    return result;
}

/**
 * Returns whether or not this task is complete
 * @return whether or not this task is complete
 */
bool task::is_complete() const {
    return status == completed;
}

/**
 * Returns whether or not this task is started
 * @return whether or not this task is started
 */
bool task::is_started() const {
    return status == started;
}

/**
 * Returns whether or not this task is unstarted
 * @return whether or not this task is unstarted
 */
bool task::is_unstarted() const {
    return status == unstarted;
}

/**
 * Returns whether or not the names of two tasks are equal
 * @param t the task to compare to this task
 * @return whether or not the names of both tasks are equal
 */
bool task::operator==(const task t) {
    return this->name == t.name;
}

/**
 * Returns the completion status of this task
 * @return the completion status of this task
 */
const task::STATUS task::get_status() const {
    return status;
}

/**
 * Returns a reference to the name of this task
 * @return the name of this task
 */
const string &task::get_name() const {
    return name;
}

/**
 * Returns the time at which this task was last modified
 * @return the time at which this task was last modified
 */
const time_t task::get_modified() const {
    return modified;
}

/**
 * Returns the time at which this task was created
 * @return the time at which this task was created
 */
const time_t task::get_created() const {
    return created;
}
