#include "helper.h"
#include <fstream>

void log(std::string some_string) {
    std::ofstream logfile("log.txt", std::ios_base::app);
    logfile << some_string << std::endl;
    logfile.close();
}
