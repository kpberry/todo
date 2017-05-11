#ifndef TASK_H
#define TASK_H

#include "../include/json.hpp"
#include "text/color.hpp"
#include <string>

namespace task_ns {
    class task {
    public:
        enum STATUS {
            unstarted, started, completed
        };

        //constructors
        task();
        task(std::string name);

        //getters
        const STATUS get_status() const;
        const std::string &get_name() const;
        const time_t get_modified() const;
        const time_t get_created() const;

        bool is_complete() const;
        bool is_started() const;
        bool is_unstarted() const;

        //setters
        void set_status(STATUS status);
        void set_name(std::string name);
        void set_created(time_t time);
        void set_modified(time_t time);

        //mutators
        void complete();
        void start();
        void undo();
        void advance();

        //string
        std::string to_string() const;
        std::string to_fancy_string() const;
        std::string to_fancy_string(unsigned long first_length) const;

        //operators
        bool operator==(const task t);
    private:
        STATUS status;
        std::string name;
        time_t modified;
        time_t created;
    };

    //json conversion for tasks
    void to_json(nlohmann::json &j, const task &t);
    void from_json(const nlohmann::json &j, task &t);
}

#endif