#include "processor.h"
#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
    std::string stat_file_path = "/proc/stat";
    std::ifstream file_stream(stat_file_path);
    if (file_stream.is_open()) {
        std::string line;
        if (std::getline(file_stream, line)) {
            std::istringstream string_stream(line);
            std::string cpu;
            int user;
            int nice;
            int system;
            int idle;
            int iowait;
            int irq;
            int softirq;
            int steal;
            int guest;
            int guest_nice;
            string_stream >> cpu >> user >> nice >> system >> idle >> iowait >> irq >> softirq >> steal >> guest >> guest_nice;
            if (cpu == "cpu") {
                int idle_total = idle + iowait;
                int non_idle_total = user + nice + system + irq + softirq + steal;
                return 1.0*(non_idle_total)/(non_idle_total + idle_total);
            }
        }
    }
    return -1.0;
}
