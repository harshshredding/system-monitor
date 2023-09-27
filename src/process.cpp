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
string Process::Ram() { return string(); }

// TODO: Return the user (name) that generated this process
string Process::User() { return string(); }

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { return 0; }

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a[[maybe_unused]]) const { return true; }

void Process::set_pid(std::string pid) {
    this->process_id = std::stoi(pid);
}
