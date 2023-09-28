#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

#include "process.h"
#include "helper.h"
#include "linux_parser.h"

using std::string;
using std::to_string;
using std::vector;


vector<string> split_string(string str, char delimiter) {
    std::vector<string> ret;
    std::istringstream string_stream(str);
    string token;
    while(getline(string_stream, token, delimiter)) {
        ret.push_back(token);
    }
    return ret;
}

// TODO: Return this process's ID
int Process::Pid() { return this->process_id; }

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
    std::string stat_file_path = "/proc/" + std::to_string(this->process_id) + "/stat";
    std::ifstream file_stream(stat_file_path);
    if (file_stream.is_open()) {
        std::string line;
        if (std::getline(file_stream, line)) {
            vector<string> values = split_string(line, ' ');
            string utime = values[13];
            string stime = values[14];
            string c_utime = values[15];
            string c_stime = values[16];
            long start_time = stol(values[21]);
            long ticks_per_second = sysconf(_SC_CLK_TCK);
            long total_time_spent = stol(utime) + stol(stime) + stol(c_utime) + stol(c_stime);
            long uptime = LinuxParser::UpTime();
            long process_time = uptime - (start_time/ticks_per_second);
            float usage = 1.0*(total_time_spent/ticks_per_second)/(process_time);
            return usage;
            /* log("pid " + std::to_string(this->process_id)); */
            /* log("usage " + to_string(usage)); */
            /* log("ticks_per_second " + to_string(ticks_per_second)); */
            /* log("start_time " + to_string(start_time)); */
            /* log("c_stime " + c_stime); */
            /* log("c_utime " + c_utime); */
            /* log("stime " + stime); */
            /* log("utime " + utime); */
        }
    }
    return 0.0;
}

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


// TODO: Return this process's memory utilization
string get_user_uuid(int pid) {
    std::string status_file = "/proc/" + std::to_string(pid) + "/status";
    std::ifstream file_stream(status_file);
    if (file_stream.is_open()) {
        std::string line;
        while (std::getline(file_stream, line)) {
            std::istringstream string_stream(line);
            string key;
            string value;
            if (string_stream >> key >> value) {
                if (key == "Uid:") {
                    return value;
                }
            }
        }
    }
    return "NOT AVAILABLE";
}


string get_username(string uuid) {
    std::string passwd_file_path = "/etc/passwd";
    std::ifstream file_stream(passwd_file_path);
    if (file_stream.is_open()) {
        std::string line;
        while (std::getline(file_stream, line)) {
            vector<string> tokens = split_string(line, ':');
            string username = tokens[0];
            if (tokens[2] == uuid) {
                return username;
            }
        }
    }
    return "N/A";
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
    string user_uuid = get_user_uuid(this->process_id);
    return get_username(user_uuid);
}

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
