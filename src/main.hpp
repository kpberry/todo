//
// Created by Kevin on 5/6/2017.
//

#pragma once

#include "project.hpp"

using json = nlohmann::json;

void print_file(std::string filename);
json init_config() ;
json read_config() ;
json default_config_json() ;
void write_task(std::string project, task_ns::task t) ;
task_ns::task read_tasks(std::string project) ;
project_ns::project read_project(std::string project) ;
int mkdir_safe(std::string dir);
