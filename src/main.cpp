#include <iostream>
#include <fstream>
#include <iomanip>
#include "../include/json.hpp"
#include "project.hpp"
#include "main.hpp"

#if defined(_WIN32)
    #include <io.h>
#else
    #include <sys/stat.h>
#endif

using namespace std;
using json = nlohmann::json;
using namespace task_ns;
using namespace project_ns;

#if defined(_WIN32)
    string home = string(getenv("SystemDrive"))
                  + string(getenv("HOMEPATH"))
                  + "/.todo/";
#else
    string home = string(getenv("HOME")) + "/.todo/";
#endif

json config;
string projects_loc;

int main(int argc, char** argv) {
    config = read_config();

    projects_loc = config["projects"];
    home = config["home"];

    mkdir_safe(home.c_str());
    mkdir_safe(projects_loc.c_str());

    string project = "misc";
    string message = "";
    for (int i = 1; i < argc; i++) {
        if (argv[i] == string("-p")) {
            project = argv[i + 1];
        } else if (argv[i] == string("-m")) {
            message = argv[i + 1];
        } else if (argv[i] == string("-d")) {

        }
    }

    write_task(project, task(message));
#if defined(_WIN32)
    cout << read_project(project).to_string();
#else
    cout << read_project(project).to_fancy_string();
#endif

    return 0;
}

void write_project(project p) {
    ofstream output(projects_loc + "/" + p.getName() + ".json");
    output << json(p);
}

void write_task(string project_string, const task t) {
    project p = read_project(project_string);
    p.add(t);
    write_project(p);
}

project read_project(string project_string) {
    string project_loc = projects_loc + "/" + project_string + ".json";

    //read into a json object the project to which the task will be added
    ifstream input(project_loc);
    json j;
    project p;
    if (input.good()) {
        input >> j;

        //convert the json project to a c++ object
        //TODO fix this (doesn't work for some reason)
        try {
            from_json(j, p);
        } catch (exception& e) {
            p = project(project_string);
        }
    } else {
        p = project(project_string);
    }
    return p;
}

json read_config() {
    ifstream config(home + "config.json");
    json result;
    if (config.good()) {
        config >> result;
    } else {
        cout << "No configuration file found. Generating initial config.\n";
        result = init_config();
    }
    return result;
}

json init_config() {
    ofstream config(home + "config.json");
    cout << "Generating config file at: " << home + "config.json\n";
    json result = default_config_json();
    config << setw(4) << result << endl;
    return result;
}

json default_config_json() {
    json config = {
            {"home", home},
            {"projects", home + "projects"},
            {"misc", home + "misc"}
    };

    return config;
}

int mkdir_safe(string dir) {
    int error = 0;

#if defined(_WIN32)
    error = _mkdir(dir.c_str());
#else
    error = mkdir(dir.c_str(), 0733);
#endif

    if (error != 0 && error != -1) {
        cout << "Error: " << error << "\n";
    }
}

void print_file(string filename) {
    string line;
    ifstream file;
    file.open(filename);
    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << '\n';
        }
        file.close();
    } else {
        cout << "Unable to open file";
    }
}
