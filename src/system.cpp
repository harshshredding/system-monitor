#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "process.h"
#include "processor.h"
#include "system.h"
#include "linux_parser.h"
#include "helper.h"
#include <iostream>
#include <filesystem>


using std::set;
using std::size_t;
using std::string;
using std::vector;
/*You need to complete the mentioned TODOs in order to satisfy the rubric criteria "The student will be able to extract and display basic data about the system."

You need to properly format the uptime. Refer to the comments mentioned in format. cpp for formatting the uptime.*/

// TODO: Return the system's CPU
Processor& System::Cpu() { return cpu_;}


bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

vector<string> get_process_ids() {
    std::string path = "/proc"; // specify your path here
    std::vector<string> ret;
    for (const auto& entry: std::filesystem::directory_iterator(path)) {
        if (entry.is_directory()) {
            string folder_name = entry.path().filename().string();
            if (is_number(folder_name)) {
                ret.push_back(folder_name);
            }
        }
    }
    return ret;
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
    processes_.clear();
    vector<string> process_ids = get_process_ids();
    for(auto process_id: process_ids) {
        Process new_process;
        new_process.set_pid(process_id);
        processes_.push_back(new_process);
    }
    log("num_processes: " + std::to_string(processes_.size()));
    std::sort(processes_.begin(), processes_.end());
    std::reverse(processes_.begin(), processes_.end());
    return processes_; 
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() { return LinuxParser::Kernel();}

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { return LinuxParser::MemoryUtilization(); }

// TODO: Return the operating system name
std::string System::OperatingSystem() { return LinuxParser::OperatingSystem(); }

// TODO: Return the number of processes actively running on the system
int System::RunningProcesses() { return LinuxParser::RunningProcesses(); }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { return LinuxParser::TotalProcesses(); }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
    return LinuxParser::UpTime();
}
