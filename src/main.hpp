//
// Created by Kevin on 5/6/2017.
//

#ifndef MAIN_H
#define MAIN_H

#include "project.hpp"
#include "../include/json.hpp"
#include "task.hpp"


//config IO
nlohmann::json init_config();
nlohmann::json read_config();
nlohmann::json default_config_json();

//task and project IO
project_ns::project read_project(std::string project);
void write_project(const project_ns::project &p);

enum sort_type {
    alphabetical, priority, created, modified, none
};

enum sort_direction {
    forward, reversed
};

//general file IO
void print_file(std::string filename);
int mkdir_safe(std::string dir);

//argument parsing
enum flag {
    PROJECT, MESSAGE, DELETE, TASK_NUMBER,
    CLEAR, ALL, NEXT, UNDO, SET, num_flags
};
int *get_flag_indices(int argc, char **argv);

int request_task_number(std::string project_str, std::string action);
int get_task_number(char **argv, int argc, int *flag_indices,
                    std::string project_str, flag expected, std::string action);
task_ns::task::STATUS get_status_type(char **argv, int argc, int *flag_indices,
                                      flag expected);
#endif
