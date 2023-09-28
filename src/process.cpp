#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include "process.h"

using std::string;
using std::to_string;
using std::vector;

// TODO: Return this process's ID
int Process::Pid() { return this->process_id; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { return 0; }

// TODO: Return the command that generated this process
string Process::Command() {
    std::string cmdline_file_path = "/proc/" + std::to_string(this->process_id) + "/cmdline";
    std::ifstream file_stream(cmdline_file_path);
    if (file_stream.is_open()) {
        std::string cmd;
        if (std::getline(file_stream, cmd)) {
            return cmd;
        }
    }
    return "ERROR";
}

// TODO: Return this process's memory utilization
string Process::Ram() const {
    std::string status_file = "/proc/" + std::to_string(this->process_id) + "/status";
    std::ifstream file_stream(status_file);
    if (file_stream.is_open()) {
        std::string line;
        while (std::getline(file_stream, line)) {
            std::istringstream string_stream(line);
            string key;
            string value;
            if (string_stream >> key >> value) {
                if (key == "VmSize:") {
                    int value_in_bytes = std::stoi(value);
                    int value_in_megabytes = value_in_bytes/1000;
                    return std::to_string(value_in_megabytes);
                }
            }
        }
    }
    return "0";
}

// TODO: Return the user (name) that generated this process
string Process::User() { return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
    int curr_ram = std::stoi(this->Ram());
    int other_ram = std::stoi(a.Ram());
    return curr_ram < other_ram;
}

void Process::set_pid(std::string pid) {
    this->process_id = std::stoi(pid);
}
