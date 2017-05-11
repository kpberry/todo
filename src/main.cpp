#include <iostream>
#include <fstream>
#include <iomanip>
#include "../include/json.hpp"
#include "main.hpp"
#include "text/string_formatter.hpp"

#if defined(_WIN32)
    #include <io.h>
#else
    #include <sys/stat.h>
#include <regex>

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


static constexpr color_ns::color_t unstarted_color = {200, 0, 0};
static constexpr color_ns::color_t started_color = {200, 200, 0};
static constexpr color_ns::color_t completed_color = {0, 200, 0};
static constexpr color_ns::color_t title_color = {100, 200, 150};

int main(int argc, char** argv) {
    //initialize the environment; not much sane can happen before this
    config = read_config();

    projects_loc = config["projects"];
    home = config["home"];

    mkdir_safe(home.c_str());
    mkdir_safe(projects_loc.c_str());

    //get the indices of command line flags
    int* flag_indices = get_flag_indices(argc, argv);

    string project_str = "misc";
    if (flag_indices[PROJECT] > 0) {
        project_str = argv[flag_indices[PROJECT]];
    }
    project_ns::project project = read_project(project_str);
    string project_loc = projects_loc + project_str + ".json";

    if (flag_indices[DELETE] > 0) {
        if (flag_indices[TASK_NUMBER] > 0) {
            project.remove(stoi(argv[flag_indices[TASK_NUMBER]]));
            write_project(project);
        } else {
            //project_loc = regex_replace(project_loc, regex(" "), "\\ ");
            if (remove(project_loc.c_str())) {
                string error = "Error deleting project: " + project_str
                               + " at " + project_loc;
                perror(error.c_str());
            } else {
                cout << "Successfully deleted " << project_str << '\n';
            }

            return 0;
        }
    }

    if (flag_indices[CLEAR] > 0) {
        task::STATUS status = get_status_type(argv, argc, flag_indices, CLEAR);
        switch (status) {
            case task::unstarted:
                project.remove_unstarted();
                break;
            case task::started:
                project.remove_started();
                break;
            case task::completed:
                project.remove_complete();
                break;
        }

        write_project(project);
    } else if (flag_indices[MESSAGE] > 0) {
        write_task(project_str, task(argv[flag_indices[MESSAGE]]));
    } else if (flag_indices[NEXT] > 0) {
        int task_number = get_task_number(
                argv, argc, flag_indices, project_str, NEXT, "advance"
        );

        project.advance_task(task_number);
        write_project(project);
    } else if (flag_indices[UNDO] > 0) {
        int task_number = get_task_number(
                argv, argc, flag_indices, project_str, UNDO, "undo"
        );

        project.undo_task(task_number);
        write_project(project);
    } else if (flag_indices[SET] > 0) {
        int task_number = get_task_number(
                argv, argc, flag_indices, project_str, SET, "set"
        );
        task_ns::task::STATUS status = get_status_type(
                argv, argc, flag_indices, SET
        );

        project.set_status(task_number, status);
        write_project(project);
    }

    cout << read_project(project_str).to_fancy_string() << '\n';

    return 0;
}

int* get_flag_indices(int argc, char** argv) {
    int* flag_indices = (int*) calloc(num_flags, sizeof(int));

    for (int i = 1; i < argc; i++) {
        if (argv[i] == string("-p")) {
            flag_indices[PROJECT] = i + 1;
        } else if (argv[i] == string("-m")) {
            flag_indices[MESSAGE] = i + 1;
        } else if (argv[i] == string("-d")) {
            flag_indices[DELETE] = i;
        } else if (argv[i] == string("-t")) {
            flag_indices[TASK_NUMBER] = i + 1;
        } else if (argv[i] == string("-c")) {
            flag_indices[CLEAR] = i + 1;
        } else if (argv[i] == string("-a")) {
            //TODO make it so that actions execute for all projects
            flag_indices[ALL] = i + 1;
        } else if (argv[i] == string("-n")) {
            flag_indices[NEXT] = i + 1;
        } else if (argv[i] == string("-u")) {
            flag_indices[UNDO] = i + 1;
        } else if (argv[i] == string("-s")) {
            flag_indices[SET] = i + 1;
        }
    }

    return flag_indices;
}

inline bool is_int(const std::string & s) {
    if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) {
        return false;
    }

    char * p;
    strtol(s.c_str(), &p, 10);

    return ((int) *p == 0 || (int) *p == s.size());
}

int get_task_number(char **argv, int argc, int *flag_indices,
                    string project_str, flag expected, string action) {
    int task_number = 0;
    if (flag_indices[TASK_NUMBER] < argc && flag_indices[TASK_NUMBER] > 0
            && is_int(argv[flag_indices[TASK_NUMBER]])) {
        task_number = stoi(argv[flag_indices[TASK_NUMBER]]);
    }

    if (task_number <= 0 && flag_indices[expected] < argc
        && flag_indices[expected] > 0
        && is_int(argv[flag_indices[expected]])) {
        task_number = stoi(argv[flag_indices[expected]]);
    }

    if (task_number <= 0) {
        task_number = request_task_number(project_str, action);
    }

    return task_number;
}

int request_task_number(string project_str, string action) {
    project p = read_project(project_str);
    unsigned long size = p.get_tasks().size();
    int task_number = -1;
    string task_number_str;

    while (task_number <= 0 || task_number > size) {
        cout << read_project(project_str).to_fancy_string()
             << "Please specify a task number to " << action << ": ";
        cin >> task_number_str;
        if (is_int(task_number_str)) {
            task_number = stoi(task_number_str);
        }
    }

    return task_number - 1;
}

task_ns::task::STATUS get_status_type(char** argv, int argc, int* flag_indices,
                                      flag expected) {
    char status_char;
    if (flag_indices[expected] < argc && flag_indices[expected] >= 0) {
        status_char = argv[flag_indices[expected]][0];
    } else {
        status_char = '0';
    }
    bool valid = false;
    task::STATUS status = task::unstarted;
    while (!valid) {
        valid = true;
        switch (status_char) {
            case 'u':
                status = task_ns::task::unstarted;
                break;
            case 's':
                status = task_ns::task::started;
                break;
            case 'c':
                status = task_ns::task::completed;
                break;
            default:
                cout << "Please specify a status type."
                     << "\nValid statuses are "
                     << rgb_string("(u)nstarted", unstarted_color) << ", "
                     << rgb_string("(s)tarted", started_color) << ", "
                     << "and "
                     << rgb_string("(c)omplete", completed_color) << '\n';
                string status_string;
                cin >> status_string;
                status_char = status_string[0];
                valid = false;
        }
    }

    return status;
}

void write_project(const project& p) {
    ofstream output(projects_loc + p.get_name() + ".json");
    output << json(p);
}

void write_task(string project_string, const task t) {
    project p = read_project(project_string);
    p.add(t);
    write_project(p);
}

project read_project(string project_string) {
    string project_loc = projects_loc + project_string + ".json";

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
            {"projects", home + "projects/"},
            {"misc", home + "misc/"}
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

    return error;
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
