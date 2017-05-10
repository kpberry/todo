//
// Created by Kevin on 5/6/2017.
//

#pragma once

#include "project.hpp"

using json = nlohmann::json;

//config IO
json init_config();
json read_config();
json default_config_json();

//task and project IO
project_ns::project read_project(std::string project);
void write_project(const project_ns::project &p);
void write_task(std::string project, task_ns::task t);

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
