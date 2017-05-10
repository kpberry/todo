#ifndef TASK_H
#define TASK_H

#include "../include/json.hpp"
#include "text/color.h"
#include <string>

using json = nlohmann::json;


namespace task_ns {
    class task {
    public:
        task();
        ~task();
        task(std::string name);
        void complete();
        void start();
        void undo();
        void set_name(std::string name);
        void set_created(time_t);
        void set_modified(time_t);
        enum STATUS {
            unstarted, started, completed
        };
        STATUS getStatus() const;
        const std::string &getName() const;
        time_t getModified() const;
        time_t getCreated() const;
        bool is_complete() const;
        bool is_started();
        bool is_unstarted();
        bool operator==(const task t);
        std::string to_string() const;
        void set_status(STATUS status);
        std::string to_fancy_string() const;
        std::string to_fancy_string(unsigned long first_length) const;
    private:
        STATUS status;
        std::string name;
        time_t modified;
        time_t created;
    };

    void to_json(json &j, const task &t);
    void from_json(const json &j, task &t);
}

#endif